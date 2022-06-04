/**
 * @file wconio.c
 * @author lighteverthing (wanxinnb@outlook.com)
 * @brief 这是wconio的定义
 * @date 2022-06-04
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include "wconio.h"

#ifdef _WIN32
HANDLE g_hOut = NULL;
#else
#endif

/**
 * @brief 全局变量.g_height表示控制台的长，g_width表示控制台的宽
 * 
 */
int g_height = WCON_DEFAULT_HEIGHT;
int g_width  = WCON_DEFAULT_WIDTH;

/**
 * @brief 根据不同的系统初始化控制台
 * 
 */
void initwcon()
{
#ifdef _WIN32
    g_hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD dwMode = 0;
    GetConsoleMode(g_hOut, &dwMode);

    dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
    SetConsoleMode(g_hOut, dwMode);
    setConSize(WCON_DEFAULT_WIDTH, WCON_DEFAULT_HEIGHT);
#else
    initscr();
#endif
}

// 更改窗口大小
void setConSize(int width, int height)
{

    char command[128];

    if (width < 0 && height < 0)
        sprintf(command, "mode con cols=%d lines=%d", WCON_DEFAULT_WIDTH, WCON_DEFAULT_HEIGHT);
    else if (width >= 0 && height < 0)
        sprintf(command, "mode con cols=%d lines=%d", width, WCON_DEFAULT_HEIGHT);
    else
        sprintf(command, "mode con cols=%d lines=%d", width, height);

    g_width = width;
    g_height = height;
    system(command);
}

// 多用途输出
char whatKey(int mode)
{
    // 如果是0则非阻塞式输入
    if (mode == 0)
    {
        if (_kbhit())
        {
            char c = getch();
            return c;
        }
        else
            return WCON_NOHIT;
    }
    // 如果是1则阻塞式回显输入
    else if (mode == 2)
    {
        char c = getchar();
        return c;
    }
    // 否则就阻塞式非回显输入
    else
    {
        char c= getch();
        return c;
    }
}

// 不移动光标输出内容
int  routputString(int y, int x, const char* str)
{
    printf(WCON_SAVE_CURSOR);
    printf(WCON_ESC_CODE"[%d;%dH%s", x, y, str);
    printf(WCON_RE_CURSOR);
    return 1;
}

int outputString(int y, int x, const char* str)
{
    printf(WCON_ESC_CODE"[%d;%dH%s", x, y, str);
    return 1;
}


// 设置各种颜色
int setFontColor(WCON_COLOR color)
{
    printf(WCON_SET_FCOLOR "%s", color);
    return 1;
}

int setBackgroundColor(WCON_COLOR color)
{
    printf(WCON_SET_BCOLOR"%s", color);
    return 1;
}

int setBackgroundRGB(int r, int g, int b)
{
    printf(WCON_SET_BCOLOR"%d;%d;%dm", r, g, b);
    return 1;

}

int setFontRGB(int r, int g, int b)
{
    printf(WCON_SET_FCOLOR"%d;%d;%dm", r, g, b);
    return 1;
}

// 设置标题
int setTitle(const char* title)
{
    printf(WCON_SET_TITLE "%s\x07", title);
    return 1;
}

void cleanAll()
{
    printf(WCON_CLEARN);
}

void cleanline()
{
    printf(WCON_SAVE_CURSOR);
    for (int i = 0; i < g_width; i++)
        printf(" ");
    printf(WCON_RE_CURSOR);
}

// 移动控制台光标
int moveCursor(int y, int x)
{
    printf(WCON_ESC_CODE"[%d;%dH", x, y);
    return 1;
}

void hideCursor()
{
    printf(WCON_HIDE_CURSOR);
}

void showCursor()
{
    printf(WCON_SHOW_CURSOR);
}

void saveCursor()
{
    printf(WCON_SAVE_CURSOR);
}

void reCursor()
{
    printf(WCON_RE_CURSOR);
}

// 根据样式绘制矩形
void drawRect(int posX, int posY, int width, int height, WCON_RECT_SYTLE style)
{
    printf(WCON_DEC);
    switch (style)
    {
        case WCON_SNORMAL:
            routputString(posX, posY, "l");
            routputString(posX + width, posY, "k");
            routputString(posX + width, posY + height, "j");
            routputString(posX, posY + height, "m");
            break;
        case WCON_SCROSS:
            routputString(posX, posY, "n");
            routputString(posX + width, posY, "n");
            routputString(posX + width, posY + width, "n");
            routputString(posX, posY + width, "n");
    }
    printf(WCON_ASCII);
}

void drawFrameRect(int posX, int posY, int width, int height, WCON_RECT_SYTLE style)
{
    drawRect(posX, posY, width, height, style);
    printf(WCON_DEC);

    // 绘制边框
    for (int i = 1; i < height; i ++)
    {
        routputString(posX, posY + i, "x");
        routputString(posX + width, posY + i, "x");
    }

    // 绘制顶部
    for (int i = 1; i < height; i ++)
    {
        routputString(posX + i, posY, "q");
        routputString(posX + i, posY + height, "q");
    }

    printf(WCON_ASCII);
}


int  outputStringC(int x, int y, const char* str, WCON_COLOR fontColor, WCON_COLOR backColor)
{
    setFontColor(fontColor);
    setBackgroundColor(backColor);
    outputString(x, y, str);
}

void cleanCharxy(int x, int y)
{
    printf(WCON_ESC_CODE"[%d;%dH%s", x, y, " ");
}

void rcleanCharxy(int x, int y)
{
    printf(WCON_SAVE_CURSOR);
    printf(WCON_ESC_CODE"[1X");
    printf(WCON_RE_CURSOR);
}

void cleanChar()
{
    printf(WCON_ESC_CODE"[1X");
}
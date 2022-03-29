//
// Created by Wanxi on 2022/3/29.
//

#include "wconio.h"

HANDLE hOut = NULL;

void initwcon()
{
    hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD dwMode = 0;
    GetConsoleMode(hOut, &dwMode);

    dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
    SetConsoleMode(hOut, dwMode);
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
    system(command);
}

// 多用途输出
char whatKey(int mode)
{
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
    else
    {
        char c = getchar();
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

void cleanline(int n)
{
    printf(WCON_CLEARN_LINE "%dM", n);
}

// 移动控制台光标
int moveCursor(int y, int x)
{
    printf(WCON_ESC_CODE"[%d;%dH\n", x, y);
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

// 根据样式绘制矩形
void drawRect(int posX, int posY, int width, int height, WCON_RECT_SYTLE style)
{
    printf(WCON_DEC);
    switch (style)
    {
        case WCON_SNORMAL:
            routputString(posX, posY, "l");
            routputString(posX + width, posY, "k");
            routputString(posX + width, posY + width, "j");
            routputString(posX, posY + width, "m");
            break;
        case WCON_SCROSS:
            routputString(posX, posY, "n");
            routputString(posX + width, posY, "n");
            routputString(posX + width, posY + width, "n");
            routputString(posX, posY + width, "n");
    }
    printf(WCON_ASCII);
}
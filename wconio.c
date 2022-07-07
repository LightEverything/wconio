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
HANDLE g_hIn = NULL;

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
    g_hIn = GetStdHandle(STD_INPUT_HANDLE);
    setConSize(WCON_DEFAULT_WIDTH, WCON_DEFAULT_HEIGHT);

    DWORD dwMode = 0;
    DWORD oldmode = 0;

    GetConsoleMode(g_hIn,&oldmode);
    SetConsoleMode(g_hIn,oldmode| ENABLE_MOUSE_INPUT);

    GetConsoleMode(g_hOut, &dwMode);
    dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
    SetConsoleMode(g_hOut, dwMode);
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

void setConMode(int mode)
{
    COORD new_screen;

    if( 0 == SetConsoleDisplayMode(g_hOut, mode, &new_screen))
        printf("this system cant use this fuction");

    g_height = new_screen.X;
    g_width = new_screen.Y;
}

int getConwidth()
{
    return g_width;
}

int getConheight()
{
    return g_height;
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
    printf(WCON_ESC_CODE"[%d;%dH%s", x + 1, y + 1, str);
    printf(WCON_RE_CURSOR);
    return 1;
}

int outputString(int y, int x, const char* str)
{
    printf(WCON_ESC_CODE"[%d;%dH%s", x + 1, y + 1, str);
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

// 设置固定边框
void setScrollRegion(int top, int bottom)
{
    saveCursor();
    printf(WCON_ESC_CODE"[%d;%dr", top + 1, bottom + 1);
    reCursor();
}

// 设置前景色和背景色反转
int setColorReveral()
{
    CONSOLE_SCREEN_BUFFER_INFO now;
    GetConsoleScreenBufferInfo(g_hOut, &now);
    return SetConsoleTextAttribute(g_hOut, now.wAttributes ^ COMMON_LVB_REVERSE_VIDEO);
}

// 获取xy位置的字符
char getxyChar(int x, int y)
{
    char c;
    long unsigned int num;
    COORD dwCoord = {x, y};

    ReadConsoleOutputCharacter(g_hOut, &c, 1, dwCoord, &num);
    return c;
}

char getCursorChar()
{
    Wspos pos = getConcursorPos();

    return getxyChar(pos.x, pos.y);
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

Wspos getConcursorPos()
{
    CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
    GetConsoleScreenBufferInfo(g_hOut, &consoleInfo);
    Wspos reValue;
    reValue.x = consoleInfo.dwCursorPosition.X;
    reValue.y = consoleInfo.dwCursorPosition.Y;

    return reValue;
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
            routputString(posX + width, posY + height, "n");
            routputString(posX, posY + height, "n");
            break;
        case WCON_SSTAR:
            routputString(posX, posY, "*");
            routputString(posX + width, posY, "*");
            routputString(posX + width, posY + height, "*");
            routputString(posX, posY + height, "*");
    }
    printf(WCON_ASCII);
}

void drawFrameRect(int posX, int posY, int width, int height, WCON_RECT_SYTLE style)
{
    drawRect(posX, posY, width, height, style);
    printf(WCON_DEC);

    switch(style)
    {
    case WCON_SNORMAL:
    case WCON_SCROSS:
        // 绘制边框
        for (int i = 1; i < height; i ++)
        {
            routputString(posX, posY + i, "x");
            routputString(posX + width, posY + i, "x");
        }

        // 绘制顶部
        for (int i = 1; i < width; i ++)
        {
            routputString(posX + i, posY, "q");
            routputString(posX + i, posY + height, "q");
        }
        break;
    case WCON_SSTAR:
        // 绘制边框
        for (int i = 1; i < height; i ++)
        {
            routputString(posX, posY + i, "*");
            routputString(posX + width, posY + i, "*");
        }

        // 绘制顶部
        for (int i = 1; i < width; i ++)
        {
            routputString(posX + i, posY, "*");
            routputString(posX + i, posY + height, "*");
        }
        break;
    }

    printf(WCON_ASCII);
}

int  outputStringC(int x, int y, const char* str, WCON_COLOR fontColor, WCON_COLOR backColor)
{
    setFontColor(fontColor);
    setBackgroundColor(backColor);
    return outputString(x, y, str);
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

static void dealEvent(WsmouseEvent* mouseEvent, INPUT_RECORD* r, DWORD* res)
{
    if (r->EventType == MOUSE_EVENT)
    {
        switch(r->Event.MouseEvent.dwEventFlags)
        {
        // 鼠标双击
        case DOUBLE_CLICK:
            if (r->Event.MouseEvent.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED)
                mouseEvent->state = WCON_MOUSE_DOUBLELEFT;
            else if (r->Event.MouseEvent.dwButtonState == RIGHTMOST_BUTTON_PRESSED)
                mouseEvent->state = WCON_MOUSE_DOUBLERIGHT;
            break;

        // 0 的时候是普通按下或者是松开
        case 0:
            if (r->Event.MouseEvent.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED)
                mouseEvent->state = WCON_MOUSE_CLICKLEFT;
            else if (r->Event.MouseEvent.dwButtonState == RIGHTMOST_BUTTON_PRESSED)
                mouseEvent->state = WCON_MOUSE_CLICKRIGHT;
            break;

        // 移动
        case MOUSE_MOVED:
            mouseEvent->state = WCON_MOUSE_MOVE;
            break;

        // 鼠标滚轮
        case MOUSE_WHEELED:
            mouseEvent->state = WCON_MOUSE_WHEELED;
            break;
        }

        // 赋值坐标
        mouseEvent->pos.x = r->Event.MouseEvent.dwMousePosition.X;
        mouseEvent->pos.y = r->Event.MouseEvent.dwMousePosition.Y;
        // 将此消息过滤
        ReadConsoleInput(g_hIn, r, 1, res);
    }
    else 
    {
        // 如果不是
        mouseEvent->state = WCON_MOUSE_NOCLICK;
        mouseEvent->pos.x = -1;
        mouseEvent->pos.y = -1;

        // 如果不是键盘消息，则刷新
        if (r->EventType != KEY_EVENT)
            ReadConsoleInput(g_hIn, r, 1, res);

        return ;
    }
}

void getMouseEvent(WsmouseEvent* mouseEvent)
{
    // 获取输入的消息
    INPUT_RECORD r;
    DWORD        res;

    PeekConsoleInput(g_hIn, &r, 1, &res);

    if (mouseEvent == NULL)
        return ;

    // 如果没有读取到消息
    if (res != 0)
        dealEvent(mouseEvent, &r, &res);
    else 
    {
        mouseEvent->state = WCON_MOUSE_NOCLICK;
        mouseEvent->pos.x = -1;
        mouseEvent->pos.y = -1;

        return ;
    }
}
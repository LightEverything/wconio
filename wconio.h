/**
 * @file wconio.h
 * @author lighteverthing (wanxinnb@outlook.com)
 * @brief wconio的头文件
 * @date 2022-06-04
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#ifndef WCONIO_H_WCONIO_H
#define WCONIO_H_WCONIO_H

#define WCON_COLOR          const char*
#define WCON_RECT_SYTLE     short

#define WCON_DEFAULT_WIDTH  70
#define WCON_DEFAULT_HEIGHT 30
#define WCON_NOHIT          -1

// 矩形样式
#define WCON_SNORMAL         0
#define WCON_SCROSS          1
#define WCON_SSTAR           2

#ifdef _WIN32

// 常用命令
#define WCON_ESC_CODE       "\x1b"
#define WCON_SAVE_CURSOR    "\x1b[s"
#define WCON_RE_CURSOR      "\x1b[u"
#define WCON_HIDE_CURSOR    "\x1b[?25l"
#define WCON_SHOW_CURSOR    "\x1b[?25h"
#define WCON_SET_FCOLOR     "\x1b[38;2;"
#define WCON_SET_BCOLOR     "\x1b[48;2;"
#define WCON_SET_TITLE      "\x1b]0;"
#define WCON_CLEARN         "\x1b[2J"
#define WCON_CLEARN_LINE    "\x1b["
#define WCON_DEC            "\x1b(0"
#define WCON_ASCII          "\x1b(B"

// 控制台模式
#define WCON_MODE_FULLSCREEN CONSOLE_FULLSCREEN_MODE
#define WCON_MODE_WINDOW     CONSOLE_WINDOWED_MODE

// 常用颜色
#define WCON_RED            "255;0;0m"
#define WCON_BLUE           "0;0;255m"
#define WCON_GREEN          "0;255;0m"
#define WCON_WHITE          "255;255;255m"
#define WCON_BLACK          "0;0;0m"

// 鼠标行为
#define WCON_MOUSE_NOCLICK     0
#define WCON_MOUSE_DOUBLELEFT  1
#define WCON_MOUSE_DOUBLERIGHT 2
#define WCON_MOUSE_CLICKLEFT   3
#define WCON_MOUSE_CLICKRIGHT  4
#define WCON_MOUSE_MOVE        5
#define WCON_MOUSE_WHEELED     6

// 按键行为
#define WCON_KEY_ENTER         13 ///< window的换行是用cr结尾的

#else 

#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 如果定义了window
#ifdef _WIN32
#include <conio.h>
#include <windows.h>
#else
#include <curses.h>
#endif

// 如果是c++,此处调用c的编译
#ifdef __cplusplus
extern "C"
{
#endif

/**
 * @brief 
 * 
 */
struct Wcombination
{
    char** map;              ///< 图像指针
    int lines;               ///< 图像的行数字
    int border_height;       ///< 碰撞边框的高(当为-1的时候，不启用碰撞)
    int border_width;        ///< 碰撞边框的宽
};

/**
 * @brief w是wconio的前缀, s表示的是结构体,pos是代表的是位置
 * 
 */
struct Wspos
{
    int x;
    int y;
};

/**
 * @brief w是wconio的前缀, s表示的是结构体,mouseEvent是代表的是鼠标事件
 * 
 */
struct WsmouseEvent
{
    struct Wspos pos; ///< 鼠标位置
    int state; ///< 鼠标的状态
};

typedef struct Wcombination Wcombination;
typedef struct Wspos Wspos;
typedef struct WsmouseEvent WsmouseEvent;

void initwcon();
void setConSize(int width, int height);

/**
 * @brief 设置控制台输出模式
 * 
 * @param mode 
 * -- WCON_MODE_FULLSCREEN 全屏
 * -- WCON_MODE_WINDOW     窗口显示
 */
void setConMode(int mode);

int getConwidth();
int getConheigh();

/**
 * @brief 这个函数是对输入的封装，根据mode不同采取不同的输入方式
 * 
 * @param mode 是whatkey的输入模式
 * -- 0 如果是0则非阻塞式输入
 * -- 1 如果是1则阻塞式回显输入
 * -- 2 否则就阻塞式非回显输入
 * 
 * @return char 如果mode = 0时，程序将会进入非阻塞式输入，每次调用将会返回一个值，如果没有按键，就返回WCON_NOHIT
 */
char whatKey(int mode);
int  routputString(int x, int y, const char* str);
int  outputString(int x, int y, const char* str);
// 快速带颜色输出
int  outputStringC(int x, int y, const char* str, WCON_COLOR fontColor, WCON_COLOR backColor);

/**
 * @brief 获取光标位置的char
 * 
 * @return char 
 */
char getCursorChar();

/**
 * @brief 获取(x，y)位置的字符
 * 
 * @param x x坐标
 * @param y y坐标
 * @return char 对应位置的字符
 */
char getxyChar(int x, int y);

// 设置控制台标题
int setTitle(const char* title);

/**
 * @brief 设置固定的边距，在滚动终端时，边距不会滚动
 * 
 * @param top 滚动边框的顶部
 * @param bottom 滚动边框的底部
 */
void setScrollRegion(int top, int bottom);

// 文字设置
int  setFontColor(WCON_COLOR color);
int  setBackgroundColor(WCON_COLOR color);
int  setFontRGB(int r, int g, int b);
int  setBackgroundRGB(int r, int g, int b);
int  setColorReveral();

// 光标控制
void   hideCursor();
void   showCursor();
void   saveCursor();
void   reCursor();
int    moveCursor(int x, int y);

/**
 * @brief 获取光标位置 
 * 
 * @return wspos 结构体
 */
Wspos  getConcursorPos();

/**
 * @brief 用font的颜色绘制出不带边框的矩形
 * 
 * @param posX 矩形左上角的x坐标
 * @param posY 矩形左上角的y坐标
 * @param width 矩形的宽
 * @param height 矩形的高
 * @param style 矩形的样式
 * -- WCON_SNORMAL 常规矩形样式
 * -- WCON_SCROSS  实际矩形样式
 */
void drawRect(int posX, int posY, int width, int height, WCON_RECT_SYTLE style);

/**
 * @brief 用font的颜色绘制出带边框的矩形
 * 
 * @param posX 矩形左上角的x坐标
 * @param posY 矩形左上角的y坐标
 * @param width 矩形的宽
 * @param height 矩形的高
 * @param style 矩形的样式
 * -- WCON_SNORMAL 常规矩形样式
 * -- WCON_SCROSS  实际矩形样式
 */
void drawFrameRect(int posX, int posY, int width, int height, WCON_RECT_SYTLE style);

//清除函数
void cleanAll();
void cleanline();
void cleanCharxy(int x, int y);
void rcleanCharxy(int x, int y);
void cleanChar();

// 鼠标事件
/**
 * @brief 获取鼠标事件(在window10中，要想此事件有效，需要在控制窗口界面右键 - 默认值 - 取消"快速编辑模式")
 * , 这个函数的双击和单击不太好分辨, 尽量别一起用
 * 
 * @param mouseEvent 是鼠标事件的指针，详细请看MouseEvent这个结构体
 */
void getMouseEvent(WsmouseEvent* mouseEvent);

#ifdef __cplusplus
}
#endif

#endif //WCONIO_H_WCONIO_H
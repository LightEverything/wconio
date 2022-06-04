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

#define WCON_DEFAULT_WIDTH  300
#define WCON_DEFAULT_HEIGHT 400
#define WCON_NOHIT          1

// 矩形样式
#define WCON_SNORMAL         0
#define WCON_SCROSS          1

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

// 常用颜色
#define WCON_RED            "255;0;0m"
#define WCON_BLUE           "0;0;255m"
#define WCON_GREEN          "0;255;0m"
#define WCON_WHITE          "255;255;255m"
#define WCON_BLACK          "0;0;0m"

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

struct combination
{
    char* map;
    int width;
    int height;
};
typedef struct combination combination;

void initwcon();
void setConSize(int width, int height);

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

// 设置控制台标题
int setTitle(const char* title);

// 文字设置
int  setFontColor(WCON_COLOR color);
int  setBackgroundColor(WCON_COLOR color);
int  setFontRGB(int r, int g, int b);
int  setBackgroundRGB(int r, int g, int b);

// 光标控制
void hideCursor();
void showCursor();
void saveCursor();
void reCursor();
int  moveCursor(int x, int y);

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

//清除所有
void cleanAll();
void cleanline();
void cleanCharxy(int x, int y);
void rcleanCharxy(int x, int y);
void cleanChar();

#endif //WCONIO_H_WCONIO_H
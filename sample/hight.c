#include <stdio.h>
#include "windows.h"
#include "../wconio.h"

char* title = "图书管理系统";  // 标题
char* xuanxiang[3] = {
        "这是A选项",
        "这是B选项",
        "这是C选项"
};                  // 选项

typedef struct node
{
    int x, y;
};              // 坐标节点

struct node pos[3] = {
        {40, 23},
        {40, 26},
        {40, 29}
};          // 坐标位置

void hight(int hl)     // 高亮s
{
    int pre = hl == 0 ? 2 : hl - 1;

    moveCursor(pos[pre].x, 0);
    cleanline(1);
    outputString(pos[pre].x, pos[pre].y, xuanxiang[pre]);
    outputStringC(pos[hl].x, pos[hl].y, xuanxiang[hl], WCON_BLACK, WCON_WHITE);
    setBackgroundColor(WCON_BLACK);
    setFontColor(WCON_WHITE);
}
void hightw(int hl)            // 高亮w
{
    int pre = hl == 2 ? 0 : hl + 1;

    moveCursor(pos[pre].x, 0);
    cleanline(1);
    outputString(pos[pre].x, pos[pre].y, xuanxiang[pre]);
    outputStringC(pos[hl].x, pos[hl].y, xuanxiang[hl], WCON_BLACK, WCON_WHITE);
    setBackgroundColor(WCON_BLACK);
    setFontColor(WCON_WHITE);
}

int main()
{
    initwcon();     // 初始化
    setConSize(100, 50);    // 控制台大小
    setTitle("这是一个测试");            // 设置标题

    drawRect(30, 15, 40, 20, WCON_SNORMAL);     // 绘制矩形
    outputString(40, 20, title);
    outputString(40, 23, xuanxiang[0]);
    outputString(40, 26, xuanxiang[1]);
    outputString(40, 29, xuanxiang[2]);

    char c;
    int hl = 0;
    while (c = whatKey(1))   // 获取输入
    {
        if (c == 'w')
        {
            if (hl == 0)
                hl = 2;
            else
                hl --;
            hightw(hl);
        }
        else if (c == 's')
        {
            hl ++;
            hl %= 3;
            hight(hl);
        }
    }

    return 0;
}
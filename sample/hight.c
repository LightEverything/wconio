#include <stdio.h>
#include "windows.h"
#include "../wconio.h"

char* title = "ͼ�����ϵͳ";  // ����
char* xuanxiang[3] = {
        "����Aѡ��",
        "����Bѡ��",
        "����Cѡ��"
};                  // ѡ��

typedef struct node
{
    int x, y;
};              // ����ڵ�

struct node pos[3] = {
        {40, 23},
        {40, 26},
        {40, 29}
};          // ����λ��

void hight(int hl)     // ����s
{
    int pre = hl == 0 ? 2 : hl - 1;

    moveCursor(pos[pre].x, 0);
    cleanline(1);
    outputString(pos[pre].x, pos[pre].y, xuanxiang[pre]);
    outputStringC(pos[hl].x, pos[hl].y, xuanxiang[hl], WCON_BLACK, WCON_WHITE);
    setBackgroundColor(WCON_BLACK);
    setFontColor(WCON_WHITE);
}
void hightw(int hl)            // ����w
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
    initwcon();     // ��ʼ��
    setConSize(100, 50);    // ����̨��С
    setTitle("����һ������");            // ���ñ���

    drawRect(30, 15, 40, 20, WCON_SNORMAL);     // ���ƾ���
    outputString(40, 20, title);
    outputString(40, 23, xuanxiang[0]);
    outputString(40, 26, xuanxiang[1]);
    outputString(40, 29, xuanxiang[2]);

    char c;
    int hl = 0;
    while (c = whatKey(1))   // ��ȡ����
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
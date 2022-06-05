#include <stdio.h>
#include "../wconio.h"

int main(int argc, char** argv)
{
    initwcon();

    // 如果没有任何一次保存试试会发生什么
    reCursor();
    getchar();

    moveCursor(10, 10);

    // 保存Cursor
    saveCursor();
    moveCursor(0, 0);
    printf("111");

    // 暂停
    getchar();
    reCursor();
    getchar();
    // 试试不保存直接使用会发生什么
    reCursor();
    getchar();
    return 0;
}
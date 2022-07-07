#include"../wconio.h"

int main() {
    initwcon();
    printf("Hello, world!\n");
    setFontColor(WCON_BLUE);
    setColorReveral();
    printf("Hello, world!");
    cleanline();
    printf("Hello, world");
    cleanChar();
    getchar();
    getchar();
    return 0;
}
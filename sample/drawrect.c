#include <stdio.h>
#include "../wconio.h"

int main(int argc, char** argv)
{ 
    initwcon();
    setFontColor(WCON_RED);
    drawRect(1, 1, 10, 10, WCON_SCROSS);
    getchar();
    return 0;
}
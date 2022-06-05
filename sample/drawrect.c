#include <stdio.h>
#include "../wconio.h"

int main(int argc, char** argv)
{ 
    initwcon();
    drawFrameRect(1, 1, 10, 10, WCON_SNORMAL);
    getchar();
    return 0;
}
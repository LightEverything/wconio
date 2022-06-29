#include <stdio.h>

#include "../wconio.h"

int main()  
{  
    initwcon();
    char* test = "123123123123";
    setFontColor(WCON_BLUE);
    printf("%s", test);
    setColorReveral();
    printf("%s", test);
    getchar();
    return 0;
}
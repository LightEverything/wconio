#include <stdio.h>

#include "../wconio.h"

int main(int argc, char** argv)
{
    initwcon();
    printf("%c", getxyChar(0,0));
    getchar();
}
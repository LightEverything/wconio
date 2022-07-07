#include<stdio.h>
#include<conio.h>
#include<windows.h>
int main()
{
    char ch = getche();        /*读取字符*/
    char ch2 = getche();    /*读取字符*/
    printf("You put char is %c\n",ch);
    printf("\x1b[37;40mYou put char is %c\n",ch2);
    getchar();
    return 0;
}
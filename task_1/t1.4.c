#include <stdio.h>
#include <stdlib.h>
//ядюмн 29.09
// task 1.4
int main()
{
    char c = '0';
    for(int i = 0; i <= (int)('9' - '0'); i++)
    {
        printf("%d %c\n", (int) c + i, c + i);
    }
    c = 'a';
    for(int i = 0; i <= (int)('z' - 'a'); i++)
    {
        printf("%d %c\n", (int) c + i, c + i);
    }
    c = 'A';
    for(int i = 0; i <= (int)('Z' - 'A'); i++)
    {
        printf("%d %c\n", (int) c + i, c + i);
    }
    c = ' ';
    printf("%d %c\n", (int) c, c);
    printf("Range between 'a' and '9' is %d\n",(int) ('a' - '9'));
    printf("Range between 'A' and 'z' is %d\n",(int) abs('A' - 'z'));  
    printf("\n");
    return 0;
}

#include <stdio.h>
#include <stdlib.h>
//СДАНО 29.09
// task 1.1
/*int count(char c)
{
    int n = 1;
    while (c != 0)
    {
        c << 1;
        n++;
    }
    return n / 8;
}*/
int main()
{
    char c = 1;
    int n = 1; // если хотим вывести в битах
    //n = count(c);
    printf("Short: %d\n", n * sizeof(short));
    printf("Int: %d\n", n * sizeof(int));
    printf("Long: %d\n", n * sizeof(long));
    printf("Float: %d\n", n * sizeof(float));
    printf("Double: %d\n", n * sizeof(double));
    printf("Long double: %d\n", n * sizeof(long double));
    return 0;
}


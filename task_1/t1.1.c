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
    printf("Short: %ld\n", n * sizeof(short));
    printf("Int: %ld\n", n * sizeof(int));
    printf("Long: %ld\n", n * sizeof(long));
    printf("Float: %ld\n", n * sizeof(float));
    printf("Double: %ld\n", n * sizeof(double));
    printf("Long double: %ld\n", n * sizeof(long double));
    return 0;
}


#include <stdio.h>
#include <stdlib.h>
int main()
{
    double e, x, x_i, x_j; //x_i - текущий элемент, x_j = x_i+1 - следующий элемент
    printf("Enter accurancy: ");
    scanf("%lf\n", &e);
    while(scanf("%lf", &x) != EOF)
    {
        x_i = 1;
        x_j = (x_i + (x / x_i)) / 2.0;
        while(1)
        {
            x_i = x_j;
            x_j = (x_i + (x / x_i)) / 2.0;
            if (x_i - x_j <= e) break;
        }
        printf("Square of %lf is %.10g\n", x, x_j);
    }
    return 0;
}

#include <stdio.h>
#include <stdlib.h>

int main()
{
    printf("Enter x, then a_0, a_1,...\n");
    printf("End with ENTER and CTRL + Z\n");
    double x, a, s, p;
    s = 0.0;
    p = 0.0;
    scanf("%lf", &x);
    while(scanf("%lf", &a) != EOF)
    {
        p = p * x + s;
        s = s * x + a;
    }
    printf("Sum = %lf,\tDerivative = %lf\n", s, p);
    return 0;
}

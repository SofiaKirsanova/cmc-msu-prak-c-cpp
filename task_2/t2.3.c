#include <stdio.h>
#include <stdlib.h>

// Рекурсия работает медленнее итеративной функции(это легко проверять на пример 39,40)
int Feb(int n)
{
    if(n == 0 || n == 1)
        return n;
    else
        return Feb(n - 1) + Feb(n - 2);
}
int main()
{
    int sum, f0, f1; /// текущее число, sum == текущая сумма, f0, f1 == текущие две предыдущие суммы
    char n;
    while(scanf("%d", &n) != EOF)
    {
        f0 = 0;
        f1 = 1;
        sum = 0;
        if(n == 0)
        {
            printf("%d\t", n);
        }
        else if(n == 1)
        {
            printf("%d\t", n);
        }
        else
        {
            for(int i = 0; i <= n - 1; i++)
            {

                if(i == (n - 1))
                {
                    printf("%d\t", sum);
                    break;
                }
                sum = f0 + f1;
                f0 = f1;
                f1 = sum;
            }
        }
        for(int i = 0; i <= n; i++)
        {
            if(i == n)
            {
                printf("%d\n", Feb(i));
            }
        }
    }
    return 0;
}

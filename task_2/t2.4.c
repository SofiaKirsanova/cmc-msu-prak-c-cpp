#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

double str2double(char *str, int n)
{
    int i = 0; // текущий индекс при проходе строки
    double integer = 0.0, fraction = 0.0;
    int div = 1; // помогает записать дробную часть
    int flag = 0; // нужен,чтобы понимать в дроби мы или нет
    int flag_e = 0; // если встретили e
    int flag_f = 0;
    int sign = 1; //знак после e/E
    int p = 0; // степень
    int j = 0; // счетчик
    int k = 1; // счетчик
    double s = 0.0; // результат
    while(i < n)
    {
        if(flag_e != 1)
        {
            if((str[i] >= '0') && (str[i] <= '9'))
            {
                if(flag == 1)
                {
                    fraction = fraction * 10 + (str[i] - '0');
                    div = div * 10;
                }
                else
                {
                    integer = integer * 10 + (str[i] - '0');
                }
            }
        }
        if(str[i] == '.') // встретили точку - ставим флаг дроби
        {
            flag = 1;
        }
        if(str[i] == 'e' || str[i] == 'E')
        {
            flag_e = 1;
            if(str[i + 1] == '-') // знак после e
            {
                sign = -1; // минус
            }
            else
                sign = 1;// плюс
        }
        if(str[i] == 'F' || str[i] == 'f')
        {
            flag_f = 1;
        }
        if((str[i] == '+') || (str[i] == '-'))
        {
            flag_e = 1;
            p = p * 10 + (str[i + 1]  - '0'); //степень, в которую надо возводить e
        }
        i++;
    }
    if(flag_e == 1)
    {
        if(flag == 0)
        {
            s = integer;
        }
        else
        {
            s = integer + (fraction / div);
        }
        s = s * pow(10, p * sign);
    }
    else if(flag == 0)
    {
        s = integer;
    }
    else if(flag_f == 1)
    {
        s = (float) s;
    }
    else
    {
        s = integer + (fraction / div);
    }
    return s;
}

int main()
{
    char s[1024] = {};
    while (!feof(stdin))
    {
        if (scanf ("%s", s) == 1)
        {
            printf ("%.10g \n", str2double(s, strlen(s)));
        }
    }
    return 0;
}

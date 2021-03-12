#include <stdio.h>
#include<setjmp.h>

jmp_buf begin;
char curlex;
void getlex(void);
int expr(void);
int add(void);
int mult(void);
int power(void);
void error();

int main()
{
    int result;
    setjmp(begin);
    printf("==>");
    getlex();
    result = expr();
    if (curlex != '\n') error();
    printf("\n%d\n", result);
    return 0;
}
void getlex()
{
    while ((curlex = getchar()) == ' ');
}
void error(void)
{
    printf("\nERROR!\n");
    while(getchar() != '\n');
    longjmp(begin, 1);
}
int expr()
{
    int e = add();
    while (curlex == '+' || curlex == '-')
    {
        char sign = curlex;
        getlex();
        if (sign == '+')
        {
            e += add();
        }
        else
        {
            e -= add();
        }
    }
    return e;
}
int add()
{
    int a = mult();
    while (curlex == '*' || curlex == '/')
    {
        char sign = curlex;
        getlex();
        if (sign == '*')
        {
            a *= mult();
        }
        else
        {
            int ml = mult();
            if (ml == 0) //деление на 0
            {
                error();
            }
            else
            {
                a /= ml;
            }
        }
    }
    return a;
}
int mult()
{
    int m = power();
    if (curlex == '^')
    {
        getlex();
        int count = mult();
        if (count < 0)
        {
            error();
        }
        int tmp = m;
        m = 1;
        for(int i = 0; i < count; i++)
        {
            m *= tmp;
        }
    }
    return m;
}
int power()
{
    int p;
    switch(curlex)
    {
        case '0':
        case '1':
        case '2':
        case '3':
        case '4':
        case '5':
        case '6':
        case '7':
        case '8':
        case '9':
            p = curlex - '0';
            break;
        case '(':
            getlex();
            p = expr();
            if (curlex == ')')
            {
                break;
            }
        default : error();
    }
    getlex();
    return p;
}

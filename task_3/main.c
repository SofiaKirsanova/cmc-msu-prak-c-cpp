#include <stdio.h>
#include <stdlib.h>
#include "functions.h"

int main()
{
    typedef enum {Start, Word, Greater, Greater2, Underthan, Ampersent, Ampersent2, Or, Or2, Newline, Stop, Comma, Left, Right, Sslash, Dot, Dollar} vertex;
    vertex V = Start;
    c = getchar();
    null_list();
    while(1 == 1)
        switch(V)
        {
        case Start:
            if (c == '{' || c == '}' || c == ':' || c == '?' || c == '!' || c == '@' || c == '"' || c == '#' || c == '%' || c == '[' || c == ']')
            {
                printf("\nERROR\n");
                clearlist();
                while(getchar() != '\n')
                {
                }
                vertex V = Start;
                c = getchar();
                null_list();
            }
            if(c == ' '|| c == '\t')
                c = getchar();
            else if (c == EOF)
            {
                termlist();
                printlist();
                clearlist();
                V = Stop;
            }
            else if (c == '\n')
            {
                termlist();
                printlist();
                V = Newline;
                c = getchar();
            }
            else
            {
                nullbuf();
                addsym();
                if (c == '>')
                    V = Greater;
                else if (c == '<')
                    V = Underthan;
                else if (c == '&')
                    V = Ampersent;
                else if (c == '|')
                    V = Or;
                else if (c == ';')
                    V = Comma;
                else if (c == ')')
                    V = Right;
                else if (c == '(')
                    V = Left;
                else if (c == '$')
                    V = Dollar;
                else if (c == '/')
                    V = Sslash;
                else if (c == '.')
                    V = Dot;
                else
                    V = Word;
                c = getchar();
            }
            break;

        case Word:
            if (symset(c))
            {
                addsym();
                c = getchar();
            }
            else
            {
                V = Start;
                addword();
            }
            break;

        case Comma:
            if (symset(c) && (c == ';'))
            {
                addsym();
                c = getchar();
            }
            else
            {
                V = Start;
                addword();
            }
            break;

        case Dollar:
            if (symset(c) && (c == '$'))
            {
                addsym();
                c = getchar();
            }
            else
            {
                V = Start;
                addword();
            }
            break;

        case Sslash:
            if (symset(c) && (c == '/'))
            {
                addsym();
                c = getchar();
            }
            else
            {
                V = Start;
                addword();
            }
            break;

        case Dot:
            if (symset(c) && (c == '.'))
            {
                addsym();
                c = getchar();
            }
            else
            {
                V = Start;
                addword();
            }
            break;

        case Left:
            if (symset(c) && (c == '('))
            {
                addsym();
                c = getchar();
            }
            else
            {
                V = Start;
                addword();
            }
            break;

        case Right:
            if (symset(c) && (c == ')'))
            {
                addsym();
                c = getchar();
            }
            else
            {
                V = Start;
                addword();
            }
            break;

        case Underthan:
            if (symset(c) && (c == '<'))
            {
                addsym();
                c = getchar();
            }
            else
            {
                V = Start;
                addword();
            }
            break;

        case Ampersent:
            if (c == '&')
            {
                addsym();
                c = getchar();
                V = Ampersent2;
            }
            else
            {
                V = Start;
                addword();
            }
            break;

        case Ampersent2:
            V = Start;
            addword();
            break;

        case Or:
            if (c == '|')
            {
                addsym();
                c = getchar();
                V = Or2;
            }
            else
            {
                V = Start;
                addword();
            }
            break;

        case Or2:
            V = Start;
            addword();
            break;

        case Greater:
            if (c == '>')
            {
                addsym();
                c = getchar();
                V = Greater2;
            }
            else
            {
                V = Start;
                addword();
            }
            break;

        case Greater2:
            V = Start;
            addword();
            break;

        case Newline:
            clearlist();
            V = Start;
            break;

        case Stop:
            exit(0);
            break;
        }
}

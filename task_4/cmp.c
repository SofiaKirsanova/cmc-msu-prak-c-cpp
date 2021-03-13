#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>

int main(int argc, char *argv[])
{
    FILE *f1,*f2;
    char linei[BUFSIZ], linej[BUFSIZ];
    char eof1, eof2;
    int line = 0, flagsim = 1, flag = 0, x = 0, i;
    char *prog = argv[0]; 
    
    if (argc < 3)
    {
        fprintf(stderr, "%s : there is no second file \n", prog);
        exit(1);
    }
    f1 = fopen(argv[1], "r");
    f2 = fopen(argv[2], "r");
    if (!f1 || !f2)
        fprintf(stderr, "%s : ERROR\n", prog);
    while(1)
    {
        fgets(linei, BUFSIZ, f1);
        fgets(linej, BUFSIZ, f2);
        eof1 = feof(f1);
        eof2 = feof(f2);
        flag = 0;
        line++;
        flagsim = 1; //зараннее примем, что строки равны
        /* сравнение */
        if (strlen(linei) == strlen(linej)) //длины текущих строк равны
        {
            if (!strcmp(linei, linej)) // если строки не равны (лекс, но равны по длине), то прибавляем всю строку к счетчику
                x += strlen(linei);
            else
                for (i = 0; i < strlen(linei); i++)
                {
                    if (linei[i] == linej[i]) //пока равны, крутим счетчик
                        x++;
                    else
                    {
                        flagsim = 0;
                        break;
                    }
                }
        }
        else //длины текущих строк не совпадают
        {
            if (strcmp(linei, linej) < 0) //то есть в linei на одном и том же месте символ с меньшим кодом
                for (i = 0; i < strlen(linei); i++)
                {
                    if (linei[i] == linej[i])
                        x++;
                    else
                    {
                        flagsim = 0; //строки не равны
                        break;
                    }
                }
            else //тоже самое, только для linej
                for (i = 0; i < strlen(linej); i++)
                {
                    if (linei[i] == linej[i])
                        x++;
                    else
                    {
                        flagsim = 0; //строки не равны
                        break;
                    }
                }
        }
        if (eof1 || eof2) // кончился один из файлов
        {
            if (eof1 && eof2) // кончились оба файла
                flag = 1;
            else
            {
                if (eof1) // кончился первый
                    fprintf(stderr, "cmp: EOF on %s\n", argv[1]);
                else // кончился второй
                    fprintf(stderr, "cmp: EOF on %s\n", argv[2]);
                flag = 1;
            }
        }
        if (!flagsim) // то есть зайдем в этот if, если !flagism == 1 <=> flagism == 0 (есть различия)
        {
            printf("%s differs from %s: line %d, char %d\n", argv[1], argv[2], line, x + 1);
            flag = 1;
            break;
        }
        if (flag)
            break;
    }
}
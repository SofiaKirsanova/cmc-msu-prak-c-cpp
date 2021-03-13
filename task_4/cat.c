#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>

void filecopys(FILE *ifp, FILE *ofp)
{
    int c;
    while ((c = getc(ifp)) != EOF)
        putc(c, ofp);
}

void filecopyq(FILE *ifp1, FILE *ofp1, int flag_1, int flag_2)
{
    int cq;
    while ((cq = getc(ofp1)) != EOF)
        putc(cq, ifp1);
}

int filecopy(FILE *ifp, FILE *ofp, int flag_n, int q)
{
    int c;
    int was = 0;
    if(flag_n)
    {
        printf("     %d  ", q);
        q++;
    }
    c = getc(ifp);
    while (c != EOF)
    {
        putc(c, ofp);
        if ((flag_n) && (c == '\n'))
        {
            if ((c = getc(ifp)) != EOF)
            {
                printf("     %d  ", q);
                q++;
                was = 1;
            }
        }
        if (!was)
            c = getc(ifp);
        was = 0;
    }
    printf("\n");
    return q;
}

void filecopye(FILE *ifp, FILE *ofp, int flag_e)
{
    int c;
    int q = 1;
    int was = 0;
    c = getc(ifp);
    if (c != '\n')
        putc(c, ofp);
    while (c != EOF)
    {
        if ((c = getc(ifp)) == '\n')
        {
            printf("$");
            was = 1;
        }
        if (c != EOF)
            putc(c, ofp);
        if (!was)
            was = 0;
    }
}

int main(int argc, char *argv[])
{
    FILE *fp;
    int flagn = 0;
    int flag1 = 0;
    int flag2 = 0;
    int flage = 0;
    int flags = 0;
    int i = 1, j = 0, q = 1; // q - параметр сквозной нумерации
    char eof1;
    char line[BUFSIZ];

    void filecopys(FILE *, FILE *);
    int filecopy(FILE *, FILE *, int flag_n, int q); //печать содержимого файла
    void filecopyq(FILE *, FILE *, int flag_1, int flag_2); // копирование из одного файла в другой

    char *prog = argv[0];
    if (argc == 1)
    {
        filecopys(stdin, stdout);
    }
    else
    {
        if (!strcmp(argv[1], "-n")) //вывод номера каждой строки
        {
            flagn = 1;
            i++;
        }
        if (!strcmp(argv[1], ">")) //копирование из input в output
        {
            flag1 = 1;
            i++;
        }
        if (!strcmp(argv[1], ">>")) //присоединение к концу файла
        {
            flag2 = 1;
            i++;
        }
        if (!strcmp(argv[1], "-e")) //печать игнорируемых символов
        {
            flage = 1;
            i++;
        }
       /* if (!strcmp(argv[1], "-s"))
        {
            flags = 1;
            i++;
        }*/
        if (!flag1 && !flag2 && !flage)
        {
            while (--argc > 0)
            {
                if ((fp = fopen(argv[i], "r")) == NULL)
                {
                    /*if (!flags)
                        fprintf(stderr, "%s: can't open!!!! %s\n", prog, *++argv);*/
                    exit(1);
                    break;
                }
                else
                {
                    q = filecopy(fp, stdout, flagn, q);
                    fclose(fp);
                    i++;
                }
            }
        }
        if(flag1)
        {
            fp = fopen(argv[2], "w+");
            filecopyq(stdin, fp, flag1, flag2);
            fclose(fp);
        }
        if(flag1)
        {
            fp = fopen(argv[2], "a+");
            filecopyq(stdin, fp, flag1, flag2);
            fclose(fp);
        }
        if (flage)
        {
            while (--argc > 0)
            {
                if ((fp = fopen(argv[i], "r")) == NULL)
                {
                    /*if (!flags)
                        fprintf(stderr, "%s: can't open@@@@@ %s\n", prog, *++argv);*/
                    exit(1);
                    break;
                }
                else
                {
                    filecopye(fp, stdout, flagn);
                    fclose(fp);
                    i++;
                }
            }
        }
    }
}

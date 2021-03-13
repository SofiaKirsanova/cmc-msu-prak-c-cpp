#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>

#define MAX_PATH 1024

void dirwalk(char *dir, void (*fcn)(char *)) //рекурсивная функция обхода каталога
{
    char name[MAX_PATH]; //имя текущего каталога
    struct dirent *dp;
    DIR *dfd;

    if(!(dfd = opendir(dir)))
    {
        fprintf(stderr, "dirwalk: can't open %s\n", dir);
        return;
    }
    while ((dp = readdir(dfd)))
    {
        if(!strcmp(dp->d_name, ".") || !strcmp(dp->d_name, ".."))
            continue;
        if(strlen(dir) + strlen(dp->d_name) + 2 > sizeof(name))
            fprintf(stderr, "dirwalk: name %s %s too long\n", dir, dp->d_name);
        else
        {
            sprintf(name, "%s/%s", dir, dp->d_name);
            (*fcn)(name);
        }
    }
    closedir(dfd);
}

void lsg(char *name)
{
    struct stat stbuf;
    if (stat(name, &stbuf) == -1)
    {
        fprintf(stderr, "ls: can't access %s\n", name);
        return;
    }
    printf("Group owner - %d\n", stbuf.st_gid);
}

void lsl(char *name)
{
    struct stat stbuf;

    if (stat(name, &stbuf) == -1)
    {
        fprintf(stderr, "ls: can't access %s\n", name);
        return;
    }
    if((stbuf.st_mode & S_IFMT) == S_IFDIR)
        printf("Type: Directory, ");
    if((stbuf.st_mode & S_IFMT) == S_IFCHR)
        printf("Type: Symbol-oriented, ");
    if((stbuf.st_mode & S_IFMT) == S_IFBLK)
        printf("Type: Block-oriented, ");
    if((stbuf.st_mode & S_IFMT) == S_IFREG)
        printf("Type: File, ");
    printf(" Size - %ld, Access mode - %d, Owner - %d\n", stbuf.st_size, stbuf.st_mode, stbuf.st_uid);
}

void ls(char *name)
{
    struct stat stbuf;

    if (stat(name, &stbuf) == -1)
    {
        fprintf(stderr, "ls: can't access %s\n", name);
        return;
    }
    if ((stbuf.st_mode & S_IFMT) == S_IFDIR)
        dirwalk(name, ls);
    printf("%s\n", name);
}

/*void lsr(char *name)
{

}*/

int main(int argc, char *argv[])
{
    if (argc == 1)
        ls(".");
    else
    {
        int flagR = 0, flagl = 0, flagg = 0;
        /* -R Включить рекурсивную выдачу списка каталогов.
           -l Выдавать (в одноколоночном формате) тип файла, права доступа к файлу,
              количество ссылок на файл, имя владельца, имя группы, размер файла (в байтах),
              временной штамп и имя файла.
          */
        for (int i = 1; i < argc; i++)
        {
            //printf("%");
            if (flagR || flagg || flagl)
            {
                printf("@");
                ls(argv[i]);
                if (flagg)
                {
                    printf("!");
                    lsg(argv[i]);
                }
                if (flagl)
                    lsl(argv[i]);
            }
            else
            {
                printf("#");
                if (!strcmp(argv[i], "-R"))
                    flagR = 1;
                if (!strcmp(argv[i], "-l"))
                {
                    flagl = 1;
                    ls(argv[i]);
                    lsl(argv[i]);
                }
                if (!strcmp(argv[i], "-g"))
                {
                    printf("$");
                    flagg = 1;
                    ls(argv[i]);
                    lsg(argv[i]);
                }
            }
        }
    }
    return 0;
}

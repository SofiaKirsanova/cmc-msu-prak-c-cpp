#include <stdio.h>
#include <dirent.h>
#include <sys/types.h>
#include <unistd.h>

int main(){
    char buf[FILENAME_MAX]; //константа FILENAME_MAX хранится в stdio.h
    // char *getcwd(char *buf, size_t size);  -- определение функции в библиотеке dirent.h
    getcwd(buf, FILENAME_MAX);
    printf("ИМЯ ТЕКУЩЕГО КАТАЛОГА: %s\n", buf);
}

#include <stdio.h>
#include <stdlib.h>
#define SIZE 16

int c; /*текущий символ */
char **lst; /* список слов (в виде массива)*/
char *buf; /* буфер для накопления текущего слова*/ 
int sizebuf; /* размер буфера текущего слова*/
int sizelist; /* размер списка слов*/
int curbuf; /* индекс текущего символа в буфере*/ 
int curlist; /* индекс текущего слова в списке*/

void clearlist();
void null_list();
void termlist();
void nullbuf();
void addsym();
void addword();
int mystrcmp();
void bubble_list_sort();
void printlist();
int symset(int c);
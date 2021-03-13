#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>

int main(int argc,char *argv[]) {
	FILE *f1,*f2;
	char linei[BUFSIZ],linej[BUFSIZ];
	char eof1, eof2;
	int line = 0;
	int flagsim = 1;
	int flag = 0;
	int x = 0;
	int i;
	char *prog = argv[0];


	/* flag =1 печать */

	if (argc < 3) {
		fprintf(stderr, "%s : WHERE'S SECOND FILE ?\n", prog);
	}

	f1 = fopen(argv[1],"r");
    f2 = fopen(argv[2],"r");


    if (!f1 || !f2) 
    	fprintf(stderr, "%s : ERROR\n", prog);

    while(1) {
    	fgets(linei, BUFSIZ, f1);
    	fgets(linej, BUFSIZ, f2);
    	eof1 = feof(f1);
        eof2 = feof(f2);
        flag = 0;


            line++;
            flagsim = 1;
            /* сравнение */
            if (strlen(linei) == strlen(linej)){
                if (!strcmp(linei,linej)) {
               		x += strlen(linei);
               	}
               	else {
               		for (i = 0; i < strlen(linei); i++) {
              			if (linei[i] == linej[i])
                			x++;
                		else {
                			flagsim = 0;
               				break;
               			}
               		}
               	}
            }
            else {
                if (strcmp(linei,linej) < 0) {
               		for (i = 0; i < strlen(linei); i++) {
               			if (linei[i] == linej[i]) {
               				x++;
               			}
               			else {
               				flagsim = 0;
               				break;
               			}
               		}
               	}
               	else {
                	for (i = 0; i < strlen(linej); i++) {
                		if (linei[i] == linej[i]) {
               				x++;
               			}
               			else {
               				flagsim = 0;
               				break;
               			}
               		}
               	}
            }

 			if (eof1 || eof2) {
             /*В КАКОМ-ТО ИЗ ФАЙЛОВ ДОСТИГНУТ КОНЕЦ */
           	if (eof1 && eof2) {
           		 /*В ОБОИХ ФАЙЛАХ ДОСТИГНУТ КОНЕЦ*/ 
               	flag = 1;
          	}
            else {
                if (eof1) {
                	/* В ПЕРВОМ ФАЙЛЕ ДОСТИГНУТ КОНЕЦ */
                    fprintf(stderr, "cmp: EOF on %s\n", argv[1]);
                }
                else {
         			/* ВO ВТОРОМ ФАЙЛЕ ДОСТИГНУТ КОНЕЦ */
           		    fprintf(stderr, "cmp: EOF on %s\n", argv[2]);
                }
                flag = 1;
             }
            }


            if (!flagsim) { 
                	printf("%s %s differ: char %d, line %d\n", argv[1], argv[2], x+1, line);
                    flag = 1;
                    break; 
                }
            
            if (flag) {
            	break;
            }

		}


}
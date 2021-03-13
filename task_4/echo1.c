#include <stdio.h>
#include <string.h>


int main(int argc, char *argv[]) {
    int i;
	argc--;
	int j = 0;
	int lenght;
    int t;
    int p;
    int flag = 0;

	    if (!strcmp(argv[1],"-n") || !strcmp(argv[1],"-E") || !strcmp(argv[1],"-e")) {
	        if (!strcmp(argv[1],"-e")) {
				/* ÷» À œŒ —ÀŒ¬¿Ã */
                p = 0;
                t = 0;
            	for (i = 2; i <= argc; i++) {
            		lenght = strlen(argv[i]);
                    j = 0;
            		/* ÷» À œŒ —»Ã¬ŒÀ¿Ã */
            		while (j < lenght) {
            			if (argv[i][j] == '\\') {
            				j++;
            				/* —À”◊¿… \n */
            				if (argv[i][j] == 'n') {
                                for (t = p; t < j-1; t++) {
                                        printf("%c", argv[i][t]);
                                }
            					printf("\n");
                            }
            				if (argv[i][j] == 't') {
                                for (t = p; t < j-1; t++)
                                    printf("%c", argv[i][t]);
            					printf("%s"," ");
            					printf("%s"," ");
            					printf("%s"," ");
            					printf("%s"," ");
            				}

                            if (argv[i][j] == 'r') {
                                p = p + j;
                                t = j-1;
                            }

                            p = j+1;
                            j++;
            			}
                        j++;
            		}
                    for (p = t+2; p < lenght; p++)
                        printf("%c", argv[i][p]);
                }
    			printf("\n");
            }
            if (!strcmp(argv[1],"-n")) {
                for (i = 2; i <= argc; i++) {
                    if (i == argc)
                        printf("%s", argv[i]);
                    else
                        printf("%s ",argv[i]);
                }
            }
            if (!strcmp(argv[1],"-E")) {
                for (i = 2; i <= argc; i++) {
                if (i == argc)
                    printf("%s\n", argv[i]);
                else
                    printf("%s ",argv[i]);
                }
            }
        }
        else {
            for (i = 1; i <= argc; i++) {
                if (i == argc)
                    printf("%s\n", argv[i]);
                else
                    printf("%s ",argv[i]);
            }
        }
}

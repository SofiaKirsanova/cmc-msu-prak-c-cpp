# Task1

##Chosen task

Case 1 * - calculator 1

##Make

make client - сборка клиента
make server - сброка сервера


##Assembly process

gcc server.c -o sv

gcc client.c -o cl

##Startup process

./sv

./cl

##Libraries

#include <stdio.h>
#include <unistd.h> 
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include<sys/wait.h> 

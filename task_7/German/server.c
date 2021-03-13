#include <stdio.h>
#include <unistd.h> /* для работы с read, write and close*/
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h> /* 73-75*/
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include<sys/wait.h> 

#define SIZE 255
#define MAX_QUEUE 5

int strtoi(char *s) /* char -> int */
{
    int m, n, i;
    m = n = 0;
    for (i = 0; s[i] != '\0'; i++)
    {
        m = s[i] - '0';
        n = n * 10 + m;
    }
    return n;
}

int Socket(int domain, int type, int protocol)
{
    int res = socket(domain, type, protocol);
    if(res < 0)
    {
        perror("Socket is failed\n");
        exit(EXIT_FAILURE); /* неудачное выполнение программы */
    }
    return res;
}

void Handler1(int s) 
{
	printf("\n###Server is shutting down. Thank you for using it.\n");
	signal(SIGINT,SIG_DFL);
	sleep(1);
	kill(getpid(), SIGINT);
}


void Handler2(int s) 
{
	sleep(1);
	kill(getpid(), SIGINT);
}

int main(int argc, char *argv[])
{
    int bbind, llisten, serv_fd, portnum, client_fd;
    struct sockaddr_in serv_adr, client_adr; /* для домена PF_INET описали структуру*/
    socklen_t client_len;
    char buf[SIZE];

    signal(SIGINT, Handler1); /* для ctrlC */
    signal(SIGTSTP, Handler2); /* SIGnal Terminal SToP для ctrlZ*/

    if (argc != 2){
        printf("Problems with arguments, try again\n");
        return 0; 
    }

    serv_fd = Socket(PF_INET, SOCK_STREAM, 0); /* создали сокет и в переменную serv_fd положили файловый дескриптор сокета */
    memset(&serv_adr, 0, sizeof(serv_adr));
    
    portnum = strtoi(argv[1]); /* задаем номер порта */

    serv_adr.sin_family = PF_INET;
    serv_adr.sin_port = htons(portnum); /* host to network short. Изменяет порядок байт от хоста к сети*/
    serv_adr.sin_addr.s_addr = htonl(INADDR_ANY);

    bbind = bind(serv_fd, (struct sockaddr *) &serv_adr, sizeof(serv_adr));
    if (bbind < 0){
        perror("Bind is failed\n");
        exit(EXIT_FAILURE); 
    }

    llisten = listen(serv_fd, MAX_QUEUE); 
    if(llisten < 0)
    {
        perror("Listen is failed\n");
        exit(EXIT_FAILURE); 
    }
    
    int pid;
    int n, fix_num, num, ans, choice;
    fix_num = 1;

    while(1)
    {
    	memset(&client_adr, 0, sizeof(client_adr));
        client_len = sizeof(client_adr);
        
        if((client_fd = accept(serv_fd, (struct sockaddr*) &client_adr, &client_len)) < 0)
		{
        	perror("Accept is failed\n");
        	exit(EXIT_FAILURE);
    	}

    	pid = fork();
		if(pid == 0) /* это сын, он обрабатывает запрос и посылает ответ*/
		{
			signal(SIGINT, SIG_DFL);
			close(serv_fd); /* этот сокет не нужен сыну*/
			
			while(1)
			{
				memset(buf, 0, SIZE);
				n = write(client_fd, "Enter number your choice: \n1.\\+ and <number>\n2.<number>\n3.\\?\n4.\\-\nYour number: ", 
					strlen("Enter number your choice: \n1.\\+ and <number>\n2.<number>\n3.\\?\n4.\\-\nYour number: "));
				if(n < 0)
				{
					perror("Writing is failed\n");
				}

				n = read(client_fd, &choice, sizeof(int));
				if(n < 0)
				{
					perror("Reading is failed\n");
				}

				printf("\nClient - Choice is: %d\n", choice);

				if(choice == 1)
				{
					write(client_fd,"Enter a new fixed number: ", strlen("Enter a new fixed number: "));
					n = read(client_fd, &fix_num, sizeof(int));
					if(n < 0)
					{
						perror("Reading is failed\n");
					}
					write(client_fd, "Ok\n", strlen("Ok\n"));
				}

				if(choice == 2)
				{
					write(client_fd,"Enter a number: ", strlen("Enter a number: "));
					n = read(client_fd, &num, sizeof(int));
					if(n < 0)
					{
						perror("Reading is failed\n");
					}
					ans = num + fix_num;
					n = write(client_fd, &ans, sizeof(int));
					if(n < 0)
					{
						perror("Writing is failed\n");
					}
				}

				if(choice == 3)
				{
					write(client_fd,"Fixed number: ",strlen("Fixed number: "));
					n = read(client_fd, &num, sizeof(int));
					if(n < 0)
					{
						perror("Reading is failed\n");
					}
					n = write(client_fd, &fix_num, sizeof(int));
					if(n < 0)
					{
						perror("Writing is failed\n");
					}
				}

				if(choice == 4)
				{
					shutdown(client_fd, 2); /* процесс закончил прием и передачу данных */
		 			close(client_fd);
					return (0);
				}

			}
		}   
		close(client_fd);
    }  
}
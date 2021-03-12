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
#include<netdb.h> 

#define SIZE 255

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

int strtoi_3(char *s) /* char -> int */
{
    int m, n, i;
    m = n = 0;
    for (i = 3; s[i] != '\0'; i++)
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

int Check_number(char *s)
{
	for (int i = 3; i < strlen(s); i++) 
	{
		if (!(s[i] >= '0' && s[i] <= '9')) 
		{
			return 1;
		}
	}
	return 0;
}

int Check_number_1(char *s)
{
	for (int i = 0; i < strlen(s); i++) 
	{
		if (!(s[i] >= '0' && s[i] <= '9')) 
		{
			return 1;
		}
	}
	return 0;
}

int main(int argc, char *argv[])
{
	const int backlog = 5; /*максимальный размер очереди запросов на соединение*/
	struct addrinfo hints;
	struct addrinfo *results; 
	struct addrinfo *record;

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

	memset(&hints, 0, sizeof(struct addrinfo));
	hints.ai_family = PF_INET;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = 0;
	hints.ai_canonname = NULL;
    hints.ai_addr = NULL;
    hints.ai_next = NULL;
	/* Первый аргумент NULL, так это сервер и у него нет IP */ 
	if((getaddrinfo(NULL, argv[1], &hints, &results)) < 0) /*эта функция записывает все, что входит в hints в сязанный список, который называется results */
	{
		perror("Failed to translate client socket.");
		exit(EXIT_FAILURE);
	}

	for(record = results; record != NULL; record = record -> ai_next)
	{
		serv_fd = socket(record -> ai_family, record -> ai_socktype, record -> ai_protocol);
		if(serv_fd < 0)
	    {
	        continue; 
	    }
	    //int enable = 1;
	    //setsockopt(serv_fd, SOL_SOCKET, SO_REUSEADDR, &enable, sizeof(int));
	    if((bind(serv_fd, record -> ai_addr, record -> ai_addrlen)) == 0)
	    {
	    	break;
	    }
	    close(serv_fd);
	}

	if(record == NULL)
	{
		perror("Failed to create or connect client socket.");
		exit(EXIT_FAILURE);
	}
	/*Чтобы не было утечки памяти, мы должны освободить результаты связанного списка*/
	freeaddrinfo(results);
	printf("Client socket created and bound.\n");

    /*serv_fd = Socket(PF_INET, SOCK_STREAM, 0); /* создали сокет и в переменную serv_fd положили файловый дескриптор сокета */
    //memset(&serv_adr, 0, sizeof(serv_adr));
    
    //portnum = strtoi(argv[1]); /* задаем номер порта */

    /*serv_adr.sin_family = PF_INET;
    serv_adr.sin_port = htons(portnum); /* host to network short. Изменяет порядок байт от хоста к сети*/
    /*serv_adr.sin_addr.s_addr = htonl(INADDR_ANY);

    bbind = bind(serv_fd, (struct sockaddr *) &serv_adr, sizeof(serv_adr));
    if (bbind < 0){
        perror("Bind is failed\n");
        exit(EXIT_FAILURE); 
    }*/

    llisten = listen(serv_fd, backlog); 
    if(llisten < 0)
    {
        perror("Failed to start server socket listen.\n");
        exit(EXIT_FAILURE); 
    }
    
    int pid, len;
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
				len = recv(client_fd, &buf, SIZE, 0);
				if(len < 0)
				{
					perror("Recieve is failed\n");
        			exit(EXIT_FAILURE);
				}
				if(buf[0] == '\\')
				{
					if(buf[1] == '+')
					{
						if(buf[2] == ' ')
						{
							if(Check_number(buf) == 0)
							{
								write(client_fd, "Ok\n", strlen("Ok\n"));
								fix_num = strtoi_3(buf);
							}
							else
							{
								n = write(client_fd, "Command entered incorrectly. Try again\n", strlen("Command entered incorrectly. Try again\n"));
								if(n < 0)
								{
									perror("Writing is failed\n");
									exit(EXIT_FAILURE);
								}
							}
						}
						else
						{
							n = write(client_fd, "Command entered incorrectly. Try again\n", strlen("Command entered incorrectly. Try again\n"));
							if(n < 0)
							{
								perror("Writing is failed\n");
								exit(EXIT_FAILURE);
							}
						}
					}
					else if(buf[1] == '?')
					{
						if((buf[2] == '\n') || (buf[2] == '\0'))
						{
							n = write(client_fd, &fix_num, sizeof(int));
							if(n < 0)
							{
								perror("Writing is failed\n");
								exit(EXIT_FAILURE);
							}
						}
						else
						{
							n = write(client_fd, "Command entered incorrectly. Try again\n", strlen("Command entered incorrectly. Try again\n"));
							if(n < 0)
							{
								perror("Writing is failed\n");
								exit(EXIT_FAILURE);
							}
						}
					}
					else if(buf[1] == '-')
					{
						if((buf[2] == '\n') || (buf[2] == '\0'))
						{
							shutdown(client_fd, 2); /* процесс закончил прием и передачу данных */
		 					close(client_fd);
							return 0;
						}
						else
						{
							n = write(client_fd, "Command entered incorrectly. Try again\n", strlen("Command entered incorrectly. Try again\n"));
							if(n < 0)
							{
								perror("Writing is failed\n");
								exit(EXIT_FAILURE);
							}
						}
					}
					else
					{
						n = write(client_fd, "Command entered incorrectly. Try again\n", strlen("Command entered incorrectly. Try again\n"));
						if(n < 0)
						{
							perror("Writing is failed\n");
							exit(EXIT_FAILURE);
						}
					}
				}
				else if(Check_number_1(buf) == 0)
				{
						num = strtoi(buf); /* введенное число клиентом */
						ans = fix_num + num;
						n = write(client_fd, &ans, sizeof(int));
						if(n < 0)
						{
							perror("Writing is failed\n");
							exit(EXIT_FAILURE);
						}
				}
				else
				{
					n = write(client_fd, "Command entered incorrectly. Try again\n", strlen("Command entered incorrectly. Try again\n"));
					if(n < 0)
					{
						perror("Writing is failed\n");
						exit(EXIT_FAILURE);
					}
				}

			}
		}   
		close(client_fd);
    }  
}
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include<sys/wait.h>
#include<netdb.h> 

#define SIZE 255

int strtoi(char *s, int index) /* char -> int */
{
    int m, n, i;
    m = n = 0;
    for (i = index; s[i] != '\0'; i++)
    {
        m = s[i] - '0';
        n = n * 10 + m;
    }
    return n;
}

void HandlerC(int s) 
{
	printf("\nEnd of work of server\n");
	signal(SIGINT, SIG_DFL);
	sleep(1);
	kill(getpid(), SIGINT);
}

void HandlerZ(int s) 
{
	sleep(1);
	kill(getpid(), SIGINT);
}

int if_number(char *s, int index)
{
	for (int i = index; i < strlen(s); i++) 
		if (!(s[i] >= '0' && s[i] <= '9')) 
			return 1;
	return 0;
}

int main(int argc, char *argv[])
{
	const int backlog = 7;
	struct addrinfo hints;
	struct addrinfo *results; 
	struct addrinfo *record;

    int bbind, llisten, serv_fd, portnum, client_fd, pid, len, n, number = 1, num, ans, choice;
    struct sockaddr_in serv_adr, client_adr; 
    socklen_t client_len;
    char str[SIZE];

    signal(SIGINT, HandlerC); 
    signal(SIGTSTP, HandlerZ); 

    if (argc != 2)
    {
        printf("ERROR: Too few arguments\n");
        return 0; 
    }

	memset(&hints, 0, sizeof(struct addrinfo));
	hints.ai_family = PF_INET;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = 0;
	hints.ai_canonname = NULL;
    hints.ai_addr = NULL;
    hints.ai_next = NULL;
	if((getaddrinfo(NULL, argv[1], &hints, &results)) < 0)
	{
		perror("ERROR: Failed to translate client socket.");
		exit(EXIT_FAILURE);
	}
	for(record = results; record != NULL; record = record -> ai_next)
	{
		serv_fd = socket(record -> ai_family, record -> ai_socktype, record -> ai_protocol);
		if(serv_fd < 0)
	        continue; 
	    if((bind(serv_fd, record -> ai_addr, record -> ai_addrlen)) == 0)
	    	break;
	    close(serv_fd);
	}

	if (record == NULL)
	{
		perror("ERROR: Failed to create or connect client socket.");
		exit(EXIT_FAILURE);
	}
	freeaddrinfo(results);
	printf("Client socket created and bound.\n");

    llisten = listen(serv_fd, backlog); 
    if (llisten < 0)
    {
        perror("ERROR: Failed to start server socket listen.\n");
        exit(EXIT_FAILURE); 
    }
    while(1)
    {
    	memset(&client_adr, 0, sizeof(client_adr));
        client_len = sizeof(client_adr);
        if((client_fd = accept(serv_fd, (struct sockaddr*) &client_adr, &client_len)) < 0)
		{
        	perror("ERROR: Acception failure\n");
        	exit(EXIT_FAILURE);
    	}
    	pid = fork();
		if(pid == 0)
		{
			signal(SIGINT, SIG_DFL);
			close(serv_fd);
			while(1)
			{
				len = recv(client_fd, &str, SIZE, 0);
				if(len < 0)
				{
					perror("ERROR: Recieve is failed\n");
        			exit(EXIT_FAILURE);
				}
				if(str[0] == '\\')
				{
					if(str[1] == '+')
					{
						if(str[2] == ' ')
						{
							if(if_number(str, 3) == 0)
							{
								write(client_fd, "Ok\n", strlen("Ok\n"));
								number = strtoi(str, 3);
							}
							else
							{
								n = write(client_fd, "ERROR: Incorrect command. Try again\n", strlen("ERROR: Incorrect commandn\n"));
								if(n < 0)
								{
									perror("ERROR: Failure writing\n");
									exit(EXIT_FAILURE);
								}
							}
						}
						else
						{
							n = write(client_fd, "ERROR: Incorrect command. Try again\n", strlen("ERROR: Incorrect commandn\n"));
							if(n < 0)
							{
								perror("ERROR: Failure writing\n");
								exit(EXIT_FAILURE);
							}
						}
					}
					else if(str[1] == '?')
					{
						if((str[2] == '\n') || (str[2] == '\0'))
						{
							n = write(client_fd, &number, sizeof(int));
							if(n < 0)
							{
								perror("ERROR: Failure writing\n");
								exit(EXIT_FAILURE);
							}
						}
						else
						{
							n = write(client_fd, "ERROR: Incorrect command. Try again\n", strlen("ERROR: Incorrect commandn\n"));
							if(n < 0)
							{
								perror("ERROR: Failure writing\n");
								exit(EXIT_FAILURE);
							}
						}
					}
					else if(str[1] == '-')
					{
						if((str[2] == '\n') || (str[2] == '\0'))
						{
							shutdown(client_fd, 2);
		 					close(client_fd);
							return 0;
						}
						else
						{
							n = write(client_fd, "ERROR: Incorrect command. Try again\n", strlen("ERROR: Incorrect commandn\n"));
							if(n < 0)
							{
								perror("ERROR: Failure writing\n");
								exit(EXIT_FAILURE);
							}
						}
					}
					else
					{
						n = write(client_fd, "ERROR: Incorrect command. Try again\n", strlen("ERROR: Incorrect commandn\n"));
						if(n < 0)
						{
							perror("ERROR: Failure writing\n");
							exit(EXIT_FAILURE);
						}
					}
				}
				else if(if_number(str, 0) == 0)
				{
						num = strtoi(str, 0); 
						ans = number + num;
						n = write(client_fd, &ans, sizeof(int));
						if(n < 0)
						{
							perror("ERROR: Failure writing\n");
							exit(EXIT_FAILURE);
						}
				}
				else
				{
					n = write(client_fd, "ERROR: Incorrect command. Try again\n", strlen("ERROR: Incorrect commandn\n"));
					if(n < 0)
					{
						perror("ERROR: Failure writing\n");
						exit(EXIT_FAILURE);
					}
				}

			}
		}   
		close(client_fd);
    }  
}
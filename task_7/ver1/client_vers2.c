#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<sys/socket.h>
#include<sys/wait.h> 
#include<netdb.h> // для getaddrinfo

#define SIZE 255

int strtoi(char *s) // str -> number
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

int if_number(char *s)
{
	for (int i = 0; i < strlen(s); i++) 
		if (!(s[i] >= '0' && s[i] <= '9')) 
			return 1;
	return 0;
}

int main(int argc, char *argv[])
{
//---------------------------------VARIABLES PART
	int sock_fd, n, number, ans;
	struct sockaddr_in dest_addr;
	char str[256];

	struct addrinfo hints;
	struct addrinfo *results; /* указатель на связанный список куда запишется результат функции getaddrinfo*/
	struct addrinfo *record; /* указатель на одну запись в результатах связанного списка*/
 	
 	signal(SIGINT, SIG_IGN); 
    signal(SIGTSTP, SIG_IGN);

 	if (argc != 3)
 	{
        printf("ERROR: Too few arguments\n");
        return 0; 
    }
//--------------------------------- GETARRDINFO PART
	memset(&hints, 0, sizeof(struct addrinfo));
	hints.ai_family = PF_INET;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_flags = 0;
	hints.ai_protocol = 0;
	if((getaddrinfo(argv[1], argv[2], &hints, &results)) < 0)
	{
		perror("ERROR: Failed to translate client socket.");
		exit(EXIT_FAILURE);
	}
	for(record = results; record != NULL; record = record -> ai_next)
	{
		sock_fd = socket(record -> ai_family, record -> ai_socktype, record -> ai_protocol);
		if(sock_fd < 0)
	        continue; 
	    if(connect(sock_fd, record -> ai_addr , record -> ai_addrlen) != -1)
	    	break;
	    close(sock_fd);
	}

	if (record == NULL)
	{
		perror("ERROR: Failed to create or connect client socket");
		exit(EXIT_FAILURE);
	}
	freeaddrinfo(results);
	printf("Client socket is created and connected\n");
//------------------------------CYCLE PART 
	for(;;)
	{
		printf("Choose one command: \n1.\\+ and <number>\n2.<number>\n3.\\?\n4.\\-\nYour command: ");
		scanf("%s", str);
		if(str[0] == '\\')
			if(str[1] == '+')
			{
				str[2] = ' ';
				scanf("%s", str + 3);
			}
		n = send(sock_fd, str, strlen(str) + 1, 0);
		if (n < 0)
		{
			perror("ERORR: Reading\n");
			exit(EXIT_FAILURE);
		}
		else if (n == 0)
			printf("\nEnd of work of server\n");
		if (str[0] == '\\') // проверка на команды
		{
			if(str[1] == '+')
			{
				n = read(sock_fd, str, strlen(str));
				if(n < 0)
				{
					perror("ERORR: Failure in reading\n");
					exit(EXIT_FAILURE);
				}
				printf("%c%c\n", str[0], str[1]);
			}
			else if(str[1] == '?')
				if((str[2] == '\n') || (str[2] == '\0'))
				{
					n = read(sock_fd, &number, sizeof(number));
					if(n < 0)
					{
						perror("ERROR: Failure in reading\n");
						exit(EXIT_FAILURE);
					}
					printf("Your number: %d\n", number);
				}
			else if(str[1] == '-')
				if((str[2] == '\n') || (str[2] == '\0'))
				{
					printf("Exit\n");
					shutdown(sock_fd, 2);
					close(sock_fd);
					return 0;
				}
			else
			{
				n = read(sock_fd, str, SIZE);
				if(n < 0)
				{
					perror("ERROR: Failure in reading\n");
					exit(EXIT_FAILURE);
				}
				printf("%s\n", str);
			}
		}
		else if(if_number(str) == 0)
		{
			n = read(sock_fd, &ans, sizeof(ans));
			if(n < 0)
			{
				perror("ERROR: Failure in reading\n");
				exit(EXIT_FAILURE);
			}
			printf("Result: %d\n", ans);
		}
		else 
		{
			n = read(sock_fd, str, SIZE);
			if(n < 0)
			{
				perror("ERROR: Failure in reading\n");
				exit(EXIT_FAILURE);
			}
			printf("%s\n", str);
		}
	}
}
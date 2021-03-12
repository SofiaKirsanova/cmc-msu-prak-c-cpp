#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<sys/socket.h>
#include<sys/wait.h> 
#include<netdb.h>

#define SIZE 255

int strtoi(char *s)
{
    int m,n,i;
    m = n = 0;
    for (i = 0; s[i] != '\0'; i++){
        m = s[i] - '0';
        n = n * 10 + m;
    }
    return n;
}
 /*
	argv[0] - filename
	argv[1] - server_IP_address
	argv[2] - port
 */

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
	struct addrinfo hints;
	struct addrinfo *results; /* указатель на связанный список куда запишется результат функции getaddrinfo*/
	struct addrinfo *record; /* указатель на одну запись в результатах связанного списка*/

	int sock_fd;
	struct sockaddr_in dest_addr;
	char buf[256];
 	
 	signal(SIGINT, SIG_IGN); 
    signal(SIGTSTP, SIG_IGN);

 	if (argc != 3){
        printf("Problems with arguments, try again\n");
        return 0; 
    }

	
	memset(&hints, 0, sizeof(struct addrinfo));
	/*Структура hints содержит ряд настроек, которые необходимо указать*/
	hints.ai_family = PF_INET;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_flags = 0;
	hints.ai_protocol = 0;
	//hints.ai_addr = htons(portnum);

	if((getaddrinfo(argv[1], argv[2], &hints, &results)) < 0) /*эта функция записывает все, что входит в hints в сязанный список, который называется results */
	{
		perror("Failed to translate client socket.");
		exit(EXIT_FAILURE);
	}
	/* getaddrinfo() возвращает список структур адресов. Идет проверка каждого адреса до успешного connect.
		Если socket (или connect терпит неудачу, мы (закрываем сокет и) пробуем следующий. */
	for(record = results; record != NULL; record = record -> ai_next)
	{
		sock_fd = socket(record -> ai_family, record -> ai_socktype, record -> ai_protocol);
		if(sock_fd < 0)
	    {
	        continue; 
	    }
	    if(connect(sock_fd, record -> ai_addr , record -> ai_addrlen) != -1)
	    {
	    	break;
	    }
	    close(sock_fd); /*Это может произойти в случае, если сокет успешно создался, а соединение - нет
	    				  Если создание сокета и соединение успешны, то эта строка никогда не запускается*/
	}

	if(record == NULL)
	{
		perror("Failed to create or connect client socket.");
		exit(EXIT_FAILURE);
	}
	/*Чтобы не было утечки памяти, мы должны освободить результаты связанного списка*/
	freeaddrinfo(results);
	printf("Client socket created and connected.\n");

	/*sock_fd = socket(PF_INET, SOCK_STREAM, 0);
	if(sock_fd < 0)
    {
        perror("Socket is failed\n");
        exit(EXIT_FAILURE); 
    }*/
	
	/*int portnum = strtoi(argv[2]);
	memset(&(dest_addr), 0, sizeof(dest_addr));
	dest_addr.sin_family = PF_INET;
 	dest_addr.sin_port = htons(portnum);
	dest_addr.sin_addr.s_addr = htonl(INADDR_LOOPBACK);

	if(connect(sock_fd,(struct sockaddr*)&dest_addr,sizeof(struct sockaddr)) < 0)
	{
		perror("Connection is failed\n");
		exit(EXIT_FAILURE); 
	}
	printf("Connect is successful\n");*/

	int n, fix_num, ans;

	while(1)
	{
		printf("Enter one of the following commands: \n1.\\+ and <number>\n2.<number>\n3.\\?\n4.\\-\nYour command: ");

		scanf("%s", buf);

		if(buf[0] == '\\')
		{
			if(buf[1] == '+')
			{
				buf[2] = ' ';
				scanf("%s", buf + 3);
			}
		}

		n = send(sock_fd, buf, strlen(buf) + 1, 0);
		if(n < 0)
		{
			perror("Reading is failed\n");
			exit(EXIT_FAILURE);
		}
		else if(n == 0)
		{
			printf("\n###Server is shutting down. Thank you for using it.\n");
		}

		if(buf[0] == '\\')
		{
			if(buf[1] == '+')
			{
				n = read(sock_fd, buf, strlen(buf));
				if(n < 0)
				{
					perror("Reading is failed\n");
					exit(EXIT_FAILURE);
				}
				printf("%c%c\n", buf[0], buf[1]);
			}
			else if(buf[1] == '?')
			{
				if((buf[2] == '\n') || (buf[2] == '\0'))
				{
					n = read(sock_fd, &fix_num, sizeof(fix_num));
					if(n < 0)
					{
						perror("Reading is failed\n");
						exit(EXIT_FAILURE);
					}
					printf("Fixed Number: %d\n", fix_num);
				}
			}
			else if(buf[1] == '-')
			{
				if((buf[2] == '\n') || (buf[2] == '\0'))
				{
					printf("You have selected to exit. Exit is successful.\n");
					shutdown(sock_fd, 2); // процесс закончил прием и передачу данных
					close(sock_fd);
					return 0;
				}
			}
			else
			{
				n = read(sock_fd, buf, SIZE);
				if(n < 0)
				{
					perror("Reading is failed\n");
					exit(EXIT_FAILURE);
				}
				printf("%s\n", buf);
			}
		}
		else if(Check_number_1(buf) == 0)
		{
			n = read(sock_fd, &ans, sizeof(ans));
			if(n < 0)
			{
				perror("Reading is failed\n");
				exit(EXIT_FAILURE);
			}

			printf("Answer: %d\n", ans);
		}
		else 
		{
			n = read(sock_fd, buf, SIZE);
			if(n < 0)
			{
				perror("Reading is failed\n");
				exit(EXIT_FAILURE);
			}
			printf("%s\n", buf);
		}
	}
}
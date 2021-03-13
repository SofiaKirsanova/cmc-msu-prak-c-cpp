#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<sys/socket.h>
#include<sys/wait.h> 

#define SIZE 255

int strtoi(char *s)
{
    int m,n,i;
    m = n = 0;
    for (i=0; s[i]!='\0'; i++){
        m=s[i]-'0';
        n=n*10+m;
    }
    return n;
}
 /*
	argv[0] - filename
	argv[1] - server_IP_address
	argv[2] - port
 */

int trance(int i)
{
	if(i > 4 || i < 1)
	{
		return 0;
	}


}
int main(int argc, char *argv[])
{
	int sock_fd;
	struct sockaddr_in dest_addr;
	char buf[256];
 	
 	signal(SIGINT, SIG_IGN); 
    signal(SIGTSTP, SIG_IGN);

 	if (argc < 3){
        printf("Problems with arguments, try again\n");
        return 0; 
    }

	sock_fd = socket(PF_INET, SOCK_STREAM, 0);
	if(sock_fd < 0)
    {
        perror("Socket is failed\n");
        exit(EXIT_FAILURE); 
    }
	
	int portnum = strtoi(argv[2]);
	memset(&(dest_addr), 0, sizeof(dest_addr));
	dest_addr.sin_family = PF_INET;
 	dest_addr.sin_port = htons(portnum);
	dest_addr.sin_addr.s_addr = htonl(INADDR_LOOPBACK);

	if(connect(sock_fd,(struct sockaddr*)&dest_addr,sizeof(struct sockaddr)) < 0)
	{
		perror("Connection is failed\n");
		exit(EXIT_FAILURE); 
	}
	printf("Connect is successful\n");

	int n, fix_num, num, ans, choice, len;
	while(1)
	{			
		memset(buf, 0, SIZE);
		n = read(sock_fd, buf, SIZE);
		if(n < 0)
		{
			perror("Reading is failed\n");
    		exit(EXIT_FAILURE);
		}

		printf("Server - %s", buf);
		scanf("%d", &choice);
		write(sock_fd, &choice, sizeof(int));

		if(choice == 1)
		{
			memset(buf, 0, SIZE);
			if((n = read(sock_fd, buf, SIZE)) < 0)
			{
				perror("Reading is failed\n");
	    		exit(EXIT_FAILURE);
			}
			else if(n == 0)
			{
				printf("\n###Server is shutting down. Thank you for using it.\n");
				return 0;
			}
			printf("Server - %s", buf);
			scanf("%d", &fix_num);
			write(sock_fd, &fix_num, sizeof(int));
		}
		if(choice == 2)
		{
			memset(buf, 0, SIZE);
			if((n = read(sock_fd, buf, SIZE)) < 0)
			{
				perror("Reading is failed\n");
	    		exit(EXIT_FAILURE);
			}
			else if(n == 0)
			{
				printf("\n###Server is shutting down. Thank you for using it.\n");
				return 0;
			}
			printf("Server - %s", buf);
			scanf("%d", &num);
			write(sock_fd, &num, sizeof(int));

			read(sock_fd, &ans, sizeof(int));
			printf("Server - The answer is: %d\n", ans);
		}

		if(choice == 3)
		{
			memset(buf, 0, SIZE);
			if((n = read(sock_fd, buf, SIZE)) < 0)
			{
				perror("Reading is failed\n");
	    		exit(EXIT_FAILURE);
			}
			else if(n == 0)
			{
				printf("\n###Server is shutting down. Thank you for using it.\n");
				return 0;
			}
			printf("Server - %s", buf);
			write(sock_fd, &num, sizeof(int));

			read(sock_fd, &fix_num, sizeof(int));
			printf("%d\n", fix_num);
		}

		if(choice == 4)
		{
			printf("You have selected to exit. Exit is successful.\n");
			shutdown(sock_fd, 2);
			close(sock_fd);
			exit(0);
		}

		if(choice > 4 || choice < 1)
		{
			printf("\nProblems with choice, try again.\n");
		}

	}
}

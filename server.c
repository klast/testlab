#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

int main(int argc, char **argv)
{
	int sock, listener;
	struct sockaddr_in addr;
	char buf[1024];
	int bytes_read;
	int port = 3425;
	listener = socket(AF_INET, SOCK_STREAM, 0);

	if(listener < 0)
	{
		perror("socket");
		exit(1);
	}

	addr.sin_family = AF_INET;
	addr.sin_port = htons(port);
	addr.sin_addr.s_addr = htonl(INADDR_ANY);

	if(bind(listener, (struct sockaddr *)&addr, sizeof(addr)) < 0)
	{
		perror("bind");
		exit(2);
	}

	listen(listener, 1);

	while(1)
	{
		sock = accept(listener, NULL, NULL);
		if(sock < 0)
		{
			perror("accept");
			exit(3);
		}

		while(1)
		{
			char passwd[] = "YODA";
			char passwd_buf[1024];
			bytes_read = recv(sock, passwd_buf, 1024, 0);
			if(bytes_read <= 0) break;
			printf("%s %i\n",passwd_buf, strlen(passwd_buf));
			int passwd_size = strlen(passwd_buf);
			for(int i = 0; i < passwd_size; i++)
			{
				printf("%d\n", (int)passwd_buf[i]);
			}
			passwd_buf[passwd_size-2] = '\0';
			printf("%s %i\n",passwd_buf, strlen(passwd_buf));
			printf("passwd = %s %i\n", passwd, strlen(passwd));
			if(strcmp(passwd_buf, passwd)==0)
			{
				send(sock, "GOOD", 4*sizeof(char), 0);
			}
			else
			{
				send(sock, "BAD", 3*sizeof(char), 0);
				break;
			}
			bytes_read = recv(sock, passwd_buf, 1024, 0);
			if(bytes_read <= 0) break;
			int max=sizeof(buf);
			char* first=(char*)malloc(max);
			first=strtok(buf," ");
			double num_first = atof(first);
			char* second=(char*)malloc(max);
			second=strtok(NULL," ");
			double num_second = atof(second);
			double num_result = Process(num_first,num_second);
			char * result = (char*)malloc(max);
			snprintf(result,sizeof(result),"%i",(int)num_result);
			send(sock, result, sizeof(result), 0);
		}
		close(sock);
	}

	return 0;

} 

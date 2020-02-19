#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdlib.h>
/*Количество цифр в числе t*/
int getn(int t)
{
	if(t<=9)
		return 1;
	else
	{
		int res = 1;
		int tmp = t;
		while(t>9)
		{
			t/=10;
			res++;
		}
		return res;

	}
}

/*Сделать из двух чисел одну строку*/
char * msg(int m, int n)
{
	int num_first=getn(m);
	char * first = (char*)malloc(num_first+1);
	/*itoa только для c++, а у меня c */
	//itoa(m,first,num_first);
	snprintf(first,sizeof(first),"%i",m);
	//printf("%s\n",first);
	int num_second=getn(n);
	char * second = (char*)malloc(num_second+1);
	//itoa(n,second,num_second);
	snprintf(second,sizeof(second),"%i",n);
	//printf("%s\n",second);
	int max=num_first+num_second+2;
	char * result = (char*)malloc(max);
	int i=0;
	for(i;i<num_first;i++)
	{
		result[i]=first[i];
	}
	result[i]=' ';
	for(int j=0;j<num_second;j++)
	{
		i++;
		result[i]=second[j];
	}
	return result;
}

int main(int argc, char **argv)
{
	int sock;
	struct sockaddr_in addr;
	int port = 3425;
	char passwd[1024];
	printf("Print your password: ");
	scanf("%s", passwd);
	sock = socket(AF_INET, SOCK_STREAM, 0);
	if(sock < 0)
	{
		perror("socket");
		exit(1);
	}
	addr.sin_family = AF_INET;
	addr.sin_port = htons(port);
	addr.sin_addr.s_addr = htonl(INADDR_LOOPBACK);
	if(connect(sock, (struct sockaddr *)&addr, sizeof(addr)) < 0)
	{
		perror("connect");
		exit(2);
	}
	char passwd_buf[1024];
	send(sock, passwd, strlen(passwd)*sizeof(char), 0);
	recv(sock, passwd_buf, 1024, 0);
	//printf("%s\n",passwd_buf);
	if(strcmp(passwd_buf, "GOOD") != 0)
	{
		printf("Access denied! Wrong password!\n");
		close(sock);
		return -1;
	}
	else
	{
		printf("Access granted!\n");
		int a=0;
		int b=0;
		printf("Print m = ");
		scanf("%i",&a);
		printf("Print n = ");
		scanf("%i",&b);
		if(a<0 && b<0)
		{
			printf("There is no total square's between your values\n");
			return 0;
		}
		char * message = msg(a,b);
		char buf[1024];
		send(sock, message, sizeof(message), 0);
		recv(sock, buf, 1024, 0);
		printf(buf);
		printf("\n");
		close(sock);
		return 0;
	}
}

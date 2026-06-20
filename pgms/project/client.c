#include"header.h"
void main(int argc,char **argv)
{
	if(argc!=3)
	{
		printf("./a.out usage	ex:pass args : 4000 0.0.0.0");
		return;
	}

	int sfd,nsfd,len;
	struct sockaddr_in server_id ,client_id;
	
	sfd = socket(AF_INET, SOCK_STREAM, 0);
        if (sfd<0)
	{
		perror("socket");
		return;
	}
	perror("socket");
	
	server_id.sin_family=AF_INET;
	server_id.sin_port=htons(atoi(argv[1]));
	server_id.sin_addr.s_addr=inet_addr(argv[2]);	
	len=sizeof(server_id);

	
	nsfd =connect(sfd, (struct sockaddr *) &server_id,len);
        if (nsfd<0)
	{
		perror("connect");
		return;
	}
        perror("connect");
	char s[20];
while(1)
{
	printf("client : ");
	scanf("%s",s);
	write(sfd,s,strlen(s)+1);
	if(strcmp(s,"exit")==0)
	{
		printf("connection lost,......");
		break;
	}	
	read(sfd,s,sizeof(s));
	printf("%s\n",s);
}
	close(nsfd);
	close(sfd);
}

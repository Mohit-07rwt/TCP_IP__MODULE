#include"header.h"
void main(int argc,char **argv)
{
	struct sockaddr_in serverid,clientid;
	int len,sfd,cfd;
	
	sfd=socket(AF_INET,SOCK_STREAM,0);
	if(sfd<0)
	{
		perror("socket");
		return;
	}
	perror("socket");

	serverid.sin_family=AF_INET;
	serverid.sin_port=htons(atoi(argv[1]));
	serverid.sin_addr.s_addr=inet_addr(argv[2]);
		
	len=sizeof(serverid);

	if((connect(sfd,(struct sockaddr *)&serverid,len)<0))
	{
		perror("connect");
		return;
	}
	perror("connect");
while(1)
{
	char s[20];
	printf("you :");
	scanf("%s",s);
	write(sfd,s,strlen(s)+1);

	if(strcmp(s,"exit")==0)
		break;

	read(sfd,s,sizeof(s));
	printf("server :");
	printf("%s\n",s);
}
}

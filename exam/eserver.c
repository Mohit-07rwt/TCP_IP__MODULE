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
	if(bind(sfd,(struct sockaddr *)&serverid,len)<0)
	{
		perror("bind");
		return;
	}
	perror("bind");

	if((listen(sfd ,5)<0))
	{
		perror("listen");
		return;
	}
	perror("listen");


while(1)
{
	cfd=accept(sfd,(struct sockaddr *)&clientid,&len);
	if(cfd<0)
	{
		perror("accept");
		return;
	}
	perror("accept");
	printf("client port  %d\n",htons(clientid.sin_port));
	printf("client id    %s\n",inet_ntoa(clientid.sin_addr));

while(1)
{
	char s[20];
	printf("client : ");
	read(cfd,s,sizeof(s));

	if(strcmp(s,"exit")==0)
		break;

	printf("%s\n",s);
	printf("you : ");
	scanf("%s",s);
	write(cfd,s,sizeof(s));
	
}}

	close(sfd);
	close(cfd);	
}

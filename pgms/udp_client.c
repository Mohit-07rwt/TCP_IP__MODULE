#include"header.h"
int main(int argc,char **argv)
{
	if(argc!=3)
	{
		printf("INVALID..");
		return 0;	
	}
	int sfd,len;
	struct sockaddr_in serverId,clientId;
	sfd=socket(AF_INET,SOCK_DGRAM,0);
	if(sfd<0)
	{
		perror("socket");
		return 0;
	}
	perror("socket");

	serverId.sin_family=AF_INET;
	serverId.sin_port=htons(atoi(argv[1]));
	serverId.sin_addr.s_addr=inet_addr(argv[2]);
	len=sizeof(serverId);

	while(1)
	{
	char s[20];
	printf("enter string\n");
	scanf("%s",s);
	
	sendto(sfd,s,sizeof(s),0,(struct sockaddr*)&serverId,len);

	if(strcmp(s,"exit")==0)
		break;
	else
	{	
		char buf[20];
		len = sizeof(serverId);
		recvfrom(sfd,buf,sizeof(buf),0,(struct sockaddr *)&serverId,&len);
		printf("modified data=  %s\n",buf);
	}
	}	
	close(sfd);
}

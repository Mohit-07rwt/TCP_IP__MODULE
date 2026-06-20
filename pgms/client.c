#include"header.h"
int main(int argc,char **argv)
{
	if(argc!=3)
	{
		printf("INVALID..");
		return 0;	
	}
	int sfd,len,nsfd;
	struct sockaddr_in serverId,clientId;
	sfd=socket(AF_INET,SOCK_STREAM,0);
	if(sfd<0)
	{
		perror("socket");
		return 0;
	}
	perror("socket");

	
	//connect
	serverId.sin_family=AF_INET;
	serverId.sin_port=htons(atoi(argv[1]));
	serverId.sin_addr.s_addr=inet_addr(argv[2]);


	len=sizeof(serverId);	
	if(connect(sfd,(struct sockaddr *)&serverId,len)<0)
	{
		perror("connect");
		return 0;
	}
	perror("connect");
	
	char s[20];

	while(1)
	{
		printf("you :");
		scanf("%s",s);
		write(sfd,s,strlen(s)+1);
		
		if(strcmp(s,"exit")==0)
			break;

		read(sfd,s,sizeof(s));
		printf("server : %s\n",s);
	}
}

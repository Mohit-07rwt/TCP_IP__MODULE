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
	sfd=socket(AF_INET,SOCK_DGRAM,0);

	if(sfd<0)
	{
		perror("socket");
		return 0;
	}
	perror("socket");
	
	//bind
	serverId.sin_family=AF_INET;
	serverId.sin_port=htons(atoi(argv[1]));
	serverId.sin_addr.s_addr=inet_addr(argv[2]);

	len=sizeof(serverId);
	if(bind(sfd,(struct sockaddr *)&serverId,len)<0)
	{
		perror("bind");
		return 0;
	}
	perror("bind");
	
	printf("UPD \n");
	while(1)
	{	
		char s[20];
		recvfrom(sfd,s,sizeof(s),0,(struct sockaddr *)&clientId,&len);
		if(strcmp(s,"exit")==0)
				break;
		else
		{
			printf("Client data :  %s\n",s);	
			
			for(int i;s[i];i++)
			{
				if(s[i]>'a' && s[i]<'z')
					s[i]=s[i]-32;
			}
				printf("Server data :  %s\n",s);
			sendto(sfd,s,sizeof(s),0,(struct sockaddr *)&serverId,len);
		}	
	}
	close(sfd);	
}

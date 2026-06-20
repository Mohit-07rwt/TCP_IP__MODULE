#include"header.h"
int main(int argc,char **argv)
{
	
	if(argc!=3)
	{
		printf("INVALID..");
		return 0;	
	}
	
	//socket
	int sfd,len,nsfd;
	struct sockaddr_in serverId,clientId;
	sfd=socket(AF_INET,SOCK_STREAM,0);

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
	
	
	//listen
	if(listen(sfd,5)<0)
	{
		perror("listen");
		return 0;
	}
	perror("listen");
	
	
	while(1)
	{
		printf("waiting...\n");
		//accept
		nsfd=accept(sfd,(struct sockaddr *)&clientId,&len);
		if(nsfd<0)
		{
			perror("accept");
			return 0;
		}	
		printf("client req accepted...\n");
		printf("client port:%d\n",ntohs(clientId.sin_port));
		printf("client ip:%s\n",inet_ntoa(clientId.sin_addr));
		
		
		char s[20];
		while(1)
		{
			read(nsfd,s,sizeof(s));
			
			if(strcmp(s,"exit")==0)
				break;
			printf("client : %s\nyou : ",s);
			scanf("%s",s);
			write(nsfd,s,strlen(s)+1);
						
				
		
	/*
		for(int i;s[i];i++)
		{
			if(s[i]>'a' && s[i]<'z')
				s[i]=s[i]-32;
		}
			printf("Server data :  %s\n",s);
		*/
		}
	}
	close(nsfd);
	close(sfd);	
}

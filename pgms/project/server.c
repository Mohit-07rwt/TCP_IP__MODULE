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
 	
	if (bind(sfd, (struct sockaddr *) &server_id,len)<0)
	{
		perror("bind");
		return;
	}
	
	perror("bind");

	if (listen(sfd,5)<0)
	{
		perror("listen");
		return;
	}
	

while(1)
{
	nsfd = accept(sfd, (struct sockaddr *) &client_id,&len);
        if (nsfd<0)
	{
		perror("accept");
		return;
	}
        perror("accept");

	printf("client port : %d\n",ntohs(client_id.sin_port));
	printf("client ip : %s\n",inet_ntoa(client_id.sin_addr));

	char s[20];
	while(1)
	{
		read(nsfd,s,sizeof(s));
		if(strcmp(s,"exit")==0)
		{
			printf("connection lost.........\n");
			return;
		}
		printf("client : %s\n",s);

		for(int i=0;s[i];i++)
		{
			if(s[i]>='a' && s[i]<='z')
				s[i]=s[i]-32;	
		}
		write(nsfd,s,sizeof(s));	
	}
}
close(nsfd);
close(sfd);
}

#include"header.h" 
void main(int argc, char *argv[])
{
	int sfd, cfd,len;
	struct sockaddr_in serverid,clientid;

	sfd = socket(AF_INET,SOCK_STREAM,0);
	if (sfd<0)
	{
		perror("socket");
		return;
	}
	perror("socket");

	serverid.sin_family = AF_INET;
	serverid.sin_port=htons(atoi(argv[1]));
	serverid.sin_addr.s_addr=inet_addr(argv[2]);
	

	len=sizeof(serverid);
	if(bind(sfd, (struct sockaddr *)&serverid,len)<0)
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
		perror("listen");

	while(1)
{
	cfd = accept(sfd, (struct sockaddr *)&clientid,&len);
	if (cfd <0)
	{
		perror("accept");
		return;
	}
	printf("client req accepted\n");
	printf("client port %d",ntohs(clientid.sin_port));
	printf("client ip %s",inet_ntoa(clientid.sin_addr));

	char s[20];

while(1)
{
/*	read(cfd,s,sizeof(s));
	if(strcmp(s,"exit")==0)
			break;
	printf("\nclient : %s\n",s);
	
	printf("you: ");
	scanf("%s",s);
	write(cfd,s,strlen(s)+1);
*/
	int a[5];
	read(cfd,a,sizeof(a));
	
	for(int i=0;i<5;i++)
		printf("%d ",a[i]);
	printf("\n");

	for(int i=0;i<5;i++)
	{
		for(int j=0;j<5-i-1;j++)
		{
			if(a[j]<a[j+1])
			{
				int temp=a[j];
				a[j]=a[j+1];
				a[j+1]=temp;
			}
		}

	}
	write(cfd,a,sizeof(a));

}	
}

	close(cfd);
	close(sfd);
}



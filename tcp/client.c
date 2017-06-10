#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>

int main()
{
	int sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if(sockfd < 0)
	{
		perror("socket");
		return -1;
	}
	struct sockaddr_in addr;
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = inet_addr("127.0.0.1");
	addr.sin_port = htons(7777);
	int ret = connect(sockfd, (struct sockaddr*)&addr,
			sizeof(addr));
	if(ret < 0)
	{
		perror("connect");
		return -1;
	}
	while(1)
	{
	char buf[128]={0};
	printf("Input:");
	scanf("%s",buf);
	ret = send(sockfd, buf, strlen(buf), 0);
	if(ret < 0)
	{
		perror("send");
		return -1;
	}
	}
	close(sockfd);
	return 0;
}

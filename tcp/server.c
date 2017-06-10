#include <stdio.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

void* task(void* arg)
{
	int *p = NULL;
	p = (int*)arg;
	while (1)
	{
		char buf[128] = {0};
		int rlen = recv(*p,buf,sizeof(buf),0);
		if (rlen < 0)
		{
			printf("error recv\n");
		}
		else 
			printf("%s\n",buf);
	}
	return NULL;
}

int main()
{
	//1. 获取socket描述符
	int sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if(sockfd < 0)
	{
		printf("error socket\n");
		//exit(-1);
		return -1;
	}
	// 2.准备通信地址
	struct sockaddr_in addr;
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = inet_addr("127.0.0.1");
	addr.sin_port = htons(7777);
	// 3. 绑定socket描述符和通信地址
	int ret = bind(sockfd, (struct sockaddr*)&addr, sizeof(struct sockaddr_in));
	if(ret < 0)
	{
		printf("error bind\n");
		return -1;
	}
	// 4.监听
	listen(sockfd, 100);
	// 5.accept()建立和客户端的连接
	int accfd;
	while(1)
	{
	struct sockaddr_in clientAddr;
	socklen_t len = sizeof(clientAddr);
	accfd = accept(sockfd, (struct sockaddr*)&clientAddr, &len);
	if(accfd < 0)
	{
		printf("error accept\n");
		return -1;
	}
	pthread_t tid;
	int ret = pthread_create(&tid,NULL,task,&accfd);
	if(ret < 0){
		printf("failed to create thread!\n");
		return -1;
	}
	else if (ret == 0)
		printf("create thread successfully!\n");

	int *pi = NULL;
    //pthread_join(tid,NULL);
	}
	// 7.关闭socket描述符
	close(accfd);
	close(sockfd);
	return 0;
}

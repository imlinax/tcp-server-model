#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/socket.h>
#include <sys/wait.h>
#include <arpa/inet.h>

void sigchld_handle(int sig)
{
	int status;
	while(waitpid(-1,&status,WNOHANG) > 0)
	{
	}
}
int main(int argc,char **argv)
{
	int listenfd = 0; // 监听socket fd
	int clifd = 0; // accepted socket fd
	struct sockaddr_in serveraddr; // 服务器地址
	struct sockaddr_in cliaddr; // 客户端地址
	const int port = 8888; // 监听端口
	//	创建socket 
	listenfd = socket(PF_INET,SOCK_STREAM,0);
	if(listenfd < 0)
	{
		perror("create socket error");
		exit(EXIT_FAILURE);
	}

	serveraddr.sin_family = AF_INET;
	serveraddr.sin_port = htons(port);
	serveraddr.sin_addr.s_addr = htonl(INADDR_ANY);
	//	绑定地址及端口
	if(bind(listenfd,(struct sockaddr*)&serveraddr,sizeof(serveraddr)) < 0)
	{
		perror("bind error");
		exit(EXIT_FAILURE);
	}
	
	// 开始监听
	if(listen(listenfd,1024) < 0)
	{
		perror("listen error");
		exit(EXIT_FAILURE);
	}

	// 处理子进程退出信号,回收资源
	signal(SIGCHLD,sigchld_handle);

	socklen_t cliaddrlen = sizeof(cliaddr);
	const int BUFFERSIZE = 1024;
	char buffer[BUFFERSIZE];
	while(1)
	{
		clifd = accept(listenfd,(struct sockaddr *)&cliaddr,&cliaddrlen);
		if(clifd <= 0)
		{
			perror("accept error");
			continue;
		}
		pid_t pid ;
		if((pid = fork()) == 0)
		{
			int readlen = 0;
			while((readlen = read(clifd,buffer,BUFFERSIZE)) > 0)
			{
				// echo
				write(clifd,buffer,readlen);	
			}
		}
		else if(pid > 0)
		{
			close(clifd);
		}
		else
		{
			perror("fork error");
		}
	}

	return 0;
}

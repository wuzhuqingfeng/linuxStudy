#include <sys/types.h>
#include <unistd.h>

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <signal.h>
#include <errno.h>
#include <signal.h>


int main(void )
{
	pid_t pid;
	signal(SIGCHLD, SIG_IGN);
	printf("befor fork pid:%d \n", getpid());
	int abc = 10;
	pid = fork(); //errno
	if (pid == -1)	
	{
		//printf("pid < 0 err.\n");
		perror("tile");
		return -1;
	}
	if (pid > 0)
	{
		abc ++;
		printf("parent: pid:%d \n", getpid());
		printf("abc: %d \n", abc);
		sleep(20);
	}
	else if (pid == 0)
	{
		abc ++;
		printf("child: %d, parent: %d \n", getpid(), getppid());
		printf("abc: %d \n", abc);
		//sleep(100);
	}

	printf("fork after....\n");
	return 0;
}



int main02(void )
{
	fork(); //会产生2个分支
	
	
	fork();  //2个分支，运行fork函数，会产生4个分支。。4个进程
	fork();  //4个进程运行fork调用，会产生8个分支。。。。
	
	printf("hello...\n");
	return 0;
}

int procnum = 10;
int loopnum = 100;
	

void TestFunc(int loopnum)
{
	printf("loopnum:%d\n", loopnum);	
}

int main04(void )
{

	int i = 0, j = 0;
	printf("please enter you procNum : \n");
	scanf("%d", &procnum);
	
	printf("please enter you loopnum :\n");
	scanf("%d", &loopnum);
	
	pid_t pid;
	
	for (i=0; i<procnum; i++)
	{
		pid = fork();
		if (pid == 0)
		{
			for (j=0; j<loopnum; j ++)
			{
				TestFunc(j);
			}
			exit(0);
		}
	}
	
	//wait(NULL);
	
	printf("hello...\n");
	return 0;
}








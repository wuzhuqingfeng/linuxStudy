#include <sys/types.h>
#include <unistd.h>

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <signal.h>
#include <errno.h>
#include <signal.h>

#if  0

int procnum = 10;
int loopnum = 100;
void TestFunc(int loopnum)
{
	printf("loopnum:%d\n", loopnum);	
}

//连续创建n个进程
void test()
{
	int i = 0, j = 0;
	printf("please enter you procNum : \n");
	scanf("%d", &procnum);
	
	printf("please enter you loopnum :\n");
	scanf("%d", &loopnum);
	
	pid_t pid;
	//连续创建procnum个进程
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
}
#endif

//会打印多少个hello?  答案8个
#if 0
void test(void )
{
	fork(); //会产生2个分支
	fork();  //2个分支，运行fork函数，会产生4个分支。。4个进程
	fork();  //4个进程运行fork调用，会产生8个分支。。。。
	
	printf("hello...\n");
}
#endif

/*
孤儿进程和僵尸进程
?	如果父进程先退出，子进程还没退出那么子进程的父进程将变为init进程。（注：任何一个进程都必须有父进程）
?	如果子进程先退出，父进程还没退出，那么子进程必须等到父进程捕获到了子进程的退出状态才真正结束，
    否则这个时候子进程就成为僵尸进程。
	
孤儿进程
如果父亲进程先结束，子进程会托孤给1号进程


*/

//测试孤儿进程
#if  0
int test(void )
{
	pid_t pid;
	printf("befor fork pid:%d \n", getpid());
	int abc = 10;
	pid = fork(); //errno
	if (pid == -1)	
	{
		perror("tile");
		return -1;
	}
	if (pid > 0)
	{
		abc ++;
		printf("parent: pid:%d \n", getpid());
		printf("abc: %d \n", abc);
		//sleep(20);
	}
	else if (pid == 0)
	{
		abc ++;
		printf("child: %d, parent: %d \n", getpid(), getppid());
		printf("abc: %d \n", abc);
		sleep(100);
	}

	printf("fork after....\n");
	return 0;
}
#endif

//避免僵尸进程
#if 1
int test(void )
{
	pid_t pid;
	signal(SIGCHLD, SIG_IGN);//避免僵尸进程
	
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
	}

	printf("fork after....\n");
	return 0;
}
#endif



int main()
{
	test();
	return 0;
	
}







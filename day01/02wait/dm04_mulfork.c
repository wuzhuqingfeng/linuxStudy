#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <signal.h>
#include <errno.h>
#include <signal.h>
#include <errno.h>
#include <sys/wait.h>

/*
	wait()函数的使用
*/

void TestFunc(int loopnum)
{
	printf("loopnum:%d\n", loopnum);	
}

int main(void )
{
	
	int procnum = 10;
	int loopnum = 100;
	int ret;

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
			sleep(2000);
			//exit(0);//使子进程退出,非常重要
			exit(10);
		}
	}
	//wait系统调用会使父进程暂停执行，直到它的一个子进程结束为止
	while(1){
		/*
		使wait()函数返回不一定是子进程结束造成的,也有可能是信号中断造成
		*/
		ret = wait(NULL);//让父进程阻塞的过程中有可能被别的信号中断 ,传NULL的妙用
		if(ret == -1){
			//判断wait()函数返回的真正原因是什么
			if(errno == EINTR){//EINTR错误(被中断的系统调用)。
					perror("信号中断");
					continue;
				}
			}
			break;
	}
	
	//wait(NULL);
	
	printf("hello...\n");
	return 0;
}








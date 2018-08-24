#include <sys/types.h>
#include <unistd.h>

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <signal.h>
#include <errno.h>
#include <signal.h>


void TestFunc(int loopnum)
{
	printf("loopnum:%d\n", loopnum);	
}

int main(void )
{
	
	int procnum = 10;
	int loopnum = 100;
	

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
			exit(0);//使子进程退出,非常重要
		}
	}
	
	//wait(NULL);
	
	printf("hello...\n");
	return 0;
}








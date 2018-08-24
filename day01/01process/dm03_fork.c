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

//��������n������
void test()
{
	int i = 0, j = 0;
	printf("please enter you procNum : \n");
	scanf("%d", &procnum);
	
	printf("please enter you loopnum :\n");
	scanf("%d", &loopnum);
	
	pid_t pid;
	//��������procnum������
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

//���ӡ���ٸ�hello?  ��8��
#if 0
void test(void )
{
	fork(); //�����2����֧
	fork();  //2����֧������fork�����������4����֧����4������
	fork();  //4����������fork���ã������8����֧��������
	
	printf("hello...\n");
}
#endif

/*
�¶����̺ͽ�ʬ����
?	������������˳����ӽ��̻�û�˳���ô�ӽ��̵ĸ����̽���Ϊinit���̡���ע���κ�һ�����̶������и����̣�
?	����ӽ������˳��������̻�û�˳�����ô�ӽ��̱���ȵ������̲������ӽ��̵��˳�״̬������������
    �������ʱ���ӽ��̾ͳ�Ϊ��ʬ���̡�
	
�¶�����
������׽����Ƚ������ӽ��̻��й¸�1�Ž���


*/

//���Թ¶�����
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

//���⽩ʬ����
#if 1
int test(void )
{
	pid_t pid;
	signal(SIGCHLD, SIG_IGN);//���⽩ʬ����
	
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







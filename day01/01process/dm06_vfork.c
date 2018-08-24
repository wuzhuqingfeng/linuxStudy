#include <sys/types.h>
#include <unistd.h>

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <signal.h>
#include <errno.h>
#include <signal.h>

/*
1、对于数组,必须有能够自己结束的标志
2、数组作为函数参数退化为指针
{
	"aaaa",
	"bbbb"
	 null 0 \0  是一样的
	}
*/

/*
	1）在fork还没实现copy on write之前。Unix设计者很关心fork之后立刻执行exec所造成的
		地址空间浪费，所以引入了vfork系统调用。
	2）vfork有个限制，子进程必须立刻执行_exit或者exec函数。
		即使fork实现了copy on write，效率也没有vfork高，但是我们不推荐使用vfork，因为
		几乎每一个vfork的实现，都或多或少存在一定的问题。
	
	结论：
	1：fork子进程 拷贝 父进程的数据段
	      Vfork子进程与父进程 共享 数据段；
	2：fork父、子进程的执行次序不确定
		 Vfork：子进程先运行，父进程后运行；
	
	3、Vfork和exec函数族在一起
	execve替换进程映像（加载程序）注意execve是一个系统调用;
	替换意味着：代码段、数据段、堆栈段、进程控制块PCB全部替换。


	vfork 一个子进程，将另外一个应用加载起来,这个应用替换这个子进程的
	代码段、数据段、堆栈段、 进程控制块.
*/

/*
	vfork有个限制，子进程必须立刻执行_exit或者exec函数,否则会出现段错误
*/
#if 0
int test(void )
{
	pid_t pid;
	int ret = 0;
	
	printf("befor fork pid:%d \n", getpid());
	int abc = 10;
	pid = vfork(); //errno
	if (pid == -1)	
	{
		perror("tile");
		return -1;
	}
	if (pid > 0)
	{	
		printf("parent: pid:%d \n", getpid());
	}
	else if (pid == 0)
	{
		printf("child: %d, parent: %d \n", getpid(), getppid());		
		//exit(0);// 注释掉会导致段错误
	}

	printf("fork after....\n");
	return 0;
}
/*
	结果
	hzmct@U-64:/study/linuxtest/day01/01process$ ./dm06_vfork
	befor fork pid:4534 
	child: 4535, parent: 4534   //说明使用vfork,子进程与父进程的pid不同
	fork after....
	parent: pid:4534 
	fork after....
	dm06_vfork: cxa_atexit.c:100: __new_exitfn: Assertion `l != NULL' failed.
	Aborted (core dumped)
*/
#endif

#if 0
int test(void )
{
	pid_t pid;
	int ret = 0;
	
	printf("befor fork pid:%d \n", getpid());
	pid = vfork(); //errno
	if (pid == -1)	
	{
		perror("tile");
		return -1;
	}
	if (pid > 0)
	{	
		printf("parent: pid:%d \n", getpid());
	}
	else if (pid == 0)
	{
		printf("child: %d, parent: %d \n", getpid(), getppid());	
		//把自己写应用程序启动起来
	   	ret =  execve("./hello", NULL, NULL);//必须以NULL结束 vim查看函数的使用 shift + k
	   	if (ret == -1)
		  {
				perror("execve:");
		  }
	    printf("execve 测试有没有执行\n");	
			exit(0);//一旦execve()函数执行错误,也要正确退出,否则会引起段错误
		}

	printf("fork after....\n");
	return 0;
}
#endif


#if 1
int test(void )
{
	pid_t pid;
	int ret = 0;
	
	printf("befor fork pid:%d \n", getpid());
	int abc = 10;
	//共享 父进程的数据段
	pid = vfork(); //errno
	if (pid == -1)	
	{
		//printf("pid < 0 err.\n");
		perror("tile");
		return -1;
	}
	if (pid > 0)
	{
		printf("parent: pid:%d \n", getpid());
	
	}
	else if (pid == 0)
	{
		printf("child: %d, parent: %d \n", getpid(), getppid());
		//printf("abc:%d\n", abc);
		//通过一个应用程序执行命令
		char *const argv[] = {"ls", "-l", NULL};
	  ret =  execve("/bin/ls", argv, NULL);
	  if (ret == -1)
		{
			perror("execve");
		}
		
	  printf("execve 测试有没有执行\n");
			
		exit(0);
	}

	//printf("fork after....\n");
	return 0;
}
#endif

int  main()
{
	test();
	return 0;	
}
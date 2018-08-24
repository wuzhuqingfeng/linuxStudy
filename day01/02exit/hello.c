#include <sys/types.h>
#include <unistd.h>

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <signal.h>
#include <errno.h>
#include <signal.h>

/*
	exit可以清空IO缓存区,
	_exit(0)不会清空缓冲区
*/
#if 0
void test()
{
	printf("hello....");//没有\n
	exit(0); //是c库函数 =======其他操作。。。。在调用_exit
}
#endif

/*
	不会打印出hello....
*/
#if 0
void test()
{
	printf("hello....");
	_exit(0);//系统调用
}
#endif


/*
	\n能启动刷新缓冲区的作用
*/
#if 0
void test()
{
	printf("hello....\n");//带有\n
	_exit(0);//系统调用
}
#endif

/*
	fflush刷新缓冲区
*/

#if 0
void test()
{
		printf("hello....  fddddddddd1111");
		fflush(stdout);
		_exit(0); //系统调用
}
#endif

/*
	exit 与 _exit
	区别1：清空缓冲区的操作
	区别2：exit会调用终止处理程序
	
	有关终止处理程序
		atexit可以注册终止处理程序，ANSI C规定最多可以注册32个终止处理程序。
		终止处理程序的调用与注册次序相反
		man atexit
*/
#if 0
void bye1(void)
{
	printf("bye1...do\n");
}

void bye2(void)
{
	printf("bye2...do\n");
}
   
void test()
{
	//注册回调函数  先注册的函数后执行
	atexit(bye1);
	atexit(bye2);
	printf("hello....dddddd\n");
	exit(0); //exit会调用终止处理程序
}
#endif

/*
	abort()是使异常程序终止，同时发送SIGABRT信号给调用进程。 

*/
#if 0
void test()
{
	printf("hello....  fddddddddd1111\n");
	abort();//第一种方法
}
#endif

/*
	使进程强行退出 ctrl+ c -》
	SIGINT
		程序终止(interrupt)信号, 在用户键入INTR字符(通常是Ctrl-C)时发出，
		用于通知前台进程组终止进程。

	SIGQUIT
		和SIGINT类似, 但由QUIT字符(通常是Ctrl-\)来控制. 进程在因收到SIGQUIT退出时
		会产生core文件, 在这个意义上类似于一个程序错误信号。
*/
#if 1
void test()
{
	printf("hello....  fddddddddd1111\n");
	sleep(100);//可中断的睡眠状态
}
#endif
hzmct@U-64:/study/linuxtest/day01/02exit$ ulimit -c
0
hzmct@U-64:/study/linuxtest/day01/02exit$ ./hello
hello....  fddddddddd1111
^\Quit (core dumped)
hzmct@U-64:/study/linuxtest/day01/02exit$ ls
core  dm03_fork.c  hello  hello.c  makefile

 
 
int main()
{
	test();
	return 0;
	
}







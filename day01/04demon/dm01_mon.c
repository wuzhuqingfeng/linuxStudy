#include <sys/types.h>
#include <unistd.h>

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <signal.h>
#include <errno.h>
#include <signal.h>
#include <sys/stat.h>
#include <fcntl.h>
//#define S_IRUSR 00400//用户读
//#define S_IWUSR 00200//用户写
//#define S_IRGRP 00040//用户组读
//#define S_IWGRP 00020//用户组写
//#define S_IROTH 00004//其他读
//#define S_IWOTH 00002//其他写

//umask的使用
#if  0
#define RWRWRW (S_IRUSR|S_IWUSR|S_IRGRP|S_IWGRP|S_IROTH|S_IWOTH)
int test()
{
		printf("%x\n", RWRWRW);
		
		if(open("rwall", O_CREAT, RWRWRW) < 0) //enable read and write for all users
		{
			fprintf(stderr, "rwrwrw open error: %s!\n", strerror(errno));  //open error
			exit(-1);
		}
		//#define S_IRGRP 00040 define S_IWGRP 00020
		umask(S_IRGRP|S_IWGRP); //disable group for read and write
		if(open("nogrp", O_CREAT, RWRWRW) < 0)
		{
			fprintf(stderr, "nogrp open error: %s!\n", strerror(errno));   //open error
			exit(-1);
		}	
}
//-rw-rw-r-- 1 hzmct hzmct     0 8月  15 20:42 rwall
//-rw----rw- 1 hzmct hzmct     0 8月  15 20:42 nogrp

#endif

//调用官方api
#if 0
 int test()
 {
	 	//man daemon 可以看到
		//0表示改变重定向   1表示不改变
		daemon(1, 1);
		printf("test ...\n");
		for (;;) ;
		return 0;

 }
 /*
hzmct@U-64:/study/linuxtest/day01/04demon$ ./dm01_mon
test ...
hzmct@U-64:/study/linuxtest/day01/04demon$ ps -efj
UID        PID  PPID  PGID   SID  C STIME TTY          TIME CMD
hzmct     3597     1  3597  3597 99 21:36 ?        00:00:25 ./dm01_mon
hzmct@U-64:/study/linuxtest/day01/04demon$ kill -9 3597
*/
#endif

//手动实现daemon的功能
#if  1
   //int daemon(int nochdir, int noclose);
int my_daemon(int nochdir, int noclose)
{
	int i = 0;
	int fd0, fd1, fd2;
	pid_t pid;
	
	
	//如果守护进程要创建文件,则可能需要设置特定的权限
	//对于后面继承的文件模式会用到上面的屏蔽权限
	printf("%d\n", umask(0));
	
    
	pid = fork();
	if (pid == -1)
	{
		perror("fork err");
		exit(0);
	}
	
//1、使父进程退出
	if (pid > 0)
	{
		exit(0);
	}
	printf("pid:%d \n", getpid());
	
	/*
		setsid()建立一个新会话
		如果调用此函数的进程不是一个进程组组长,则此函数创建一个新会话
		1、该进程变成新会话的会话首进程(会话首进程是创建该会话的进程)
			此时该进程是会话的唯一进程。
		2、该进程成为一个新进程组的组长进程。新进程组id是该调用进程的进程id
		3、该进程没有控制终端
		
		
	*/
	//2创建一个新会话
	pid = setsid();
	if (pid == -1)
	{
		perror("fork err");
		exit(0);
	}
	//3将当前目录改成根目录
	if (nochdir == 0)
		chdir("/");
	
	//4关闭0、1、2文件描述符
	if (noclose == 0)
	{
		for (i=0; i<3; i++)
		{
			close(i);
		}
	}
	
  //相当于把0号文件描述符之下/dev/null
	fd0 = open("/dev/null", O_RDWR); //fd文件描述符fd-0的文件描述符指向/dev/null 
	fd1 = dup(0);//把0号文件描述符 赋值给空闲的文件描述符 1
	fd2 = dup(0);//把0号文件描述符 赋值给空闲的文件描述符 2
	
	if(fd0 != 0 || fd1 != 1 || fd2 != 2)
	{
		//一定不会打印的
		printf("fd0 = %d  fd1 = %d  fd2 = %d\n", fd0, fd1, fd2);
	}
	
	
	while(1)
	{
		sleep(1);
	}
	
	printf("hello\n");
	return 0;
}


void test()
{
	my_daemon(0, 0);	
}
#endif

int main()
{
	  test();
		return 0;
}





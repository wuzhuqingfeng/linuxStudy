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

/*
	父子进程共享文件描述符
	当然 还需要考虑文件锁等。
	
	perror和strerror区别和联系：
	（1）perror和strerror都是根据errno的值打印错误信息的。 
	（2）perror是将errno对应的错误消息的字符串打印到标准错误输出上，即stderr或2上，
		若你的程序将标准错误输出重定向到/dev/null，那就看不到了，就不能用perror了。 
		而 strerror的作用只是将errno对应的错误消息字符串返回.你可以自己决定咋样
		处理字符串，比如可以存到日志，也可以直接printf出来。
*/

#if 1
int test(void )
{
	pid_t pid;
	int fd; 
	signal(SIGCHLD, SIG_IGN);
	printf("befor fork pid:%d \n", getpid());
		
	fd  = open("./1.txt", O_RDWR);
	if (fd == -1)
	{
		
		perror("myopen");
		printf("%s\n",strerror(errno));
		return -1;
	}

	pid = fork(); //errno
	if (pid == -1)	
	{
		perror("tile");
		return -1;
	}
	
	if (pid > 0)
	{
		printf("parent: pid:%d \n", getpid());
		write(fd, "parent", 6);
		close(fd);//父进程需要关闭fd
		//sleep(20);
	}
	else if (pid == 0)
	{
		printf("child: %d, parent: %d \n", getpid(), getppid());
		write(fd, "child\n", 5);
		//sleep(100);
		close(fd);//子进程也要关闭fd
		exit(0);
	}

	printf("fork after....\n");
	return 0;
}
#endif



int  main()
{
	test();
	return 0;
}








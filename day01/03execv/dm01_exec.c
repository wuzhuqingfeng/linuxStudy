#include <sys/types.h>
#include <unistd.h>

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <signal.h>
#include <errno.h>
#include <signal.h>
/*
	int execl(const char *path, const char *arg, ..., (char  *) NULL );
	int execlp(const char *file, const char *arg, ..., (char  *) NULL);
	int execle(const char *path, const char *arg, ..., (char *) NULL, char * const envp[]);
	
	---------------------------------------------------------
	
	int execv(const char *path, char *const argv[]);
	int execvp(const char *file, char *const argv[]);
	int execvpe(const char *file, char *const argv[],char *const envp[]);
	
	//只有execvpe是系统调用

*/

//使用exec函数族替换进程印象，替换进程的代码段、数据段
//堆栈段,PCB(进程控制块),pid不变
#if 0
int  test()
{
		pid_t pid;	
		printf("getpid():%d\n", getpid());
		execle("./hello", NULL, NULL);
		printf("end.....\n");//这句话不会打印的
		return 0;
}
#endif

#if 0
int  test()
{
		pid_t pid;
		//替换以后，pid不会发生变化
		//注意 printf后的\n不能忘记，不然main函数打印不出来
		printf("getpid():%d\n", getpid());
		char * const envp[] = {"aaa=111", "bbb=2222", NULL};//必须是key=value
		//ret =execl("./hello", "hello", NULL);
		int ret =  execle("./hello", "hello", NULL, envp);	
		if (ret == -1)
		{
				perror("main:");
		}
		printf("main end...\n");
		return 0;
}

#endif

/*
   execlp要执行的可执行程序，必须能够在环境变量中找到
   带 p 的exec函数：execlp,execvp，表示第一个参数path不用输入完整路径，
   只有给出命令名即可，它会在环境变量PATH当中查找命令
*/
#if 0
int  test()
{
		pid_t pid;
		printf("主进程getpid():%d\n", getpid());
		//执行命令  echo $PATH     which ls
		//int execlp(const char *file, const char *arg, ..., (char  *) NULL);
		//execlp("/bin/ls", "ls", "-al", NULL);
		execlp("ls", "ls", "-al", NULL);
		
		printf("hello\n");
		return 0;
}

#endif

/*

1、带 p 的exec函数：execlp,execvp，表示第一个参数path不用输入完整路径，
   只有给出命令名即可，它会在环境变量PATH当中查找命令
2、不带 l 的exec函数：execv,execvp表示命令所需的参数以char *arg[]形式
		给出且arg最后一个元素必须是NULL
3、带e的exec函数：execle表示，将环境变量传递给需要替换的进程
*/
#if 1
int  test()
{
		printf("entering main process---\n");
    int ret;
    char *argv[] = {"ls","-l",NULL};
    ret = execvp("ls",argv);
    if(ret == -1)
        perror("execl error");
    printf("exiting main process ----\n");
    return 0;
}

#endif


int main()
{
	test();
	return 0;
}

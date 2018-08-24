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
	system()函数的使用
	int system(const char *command);
RETURN VALUE
       The return value of system() is one of the following:

       *  If command is NULL, then a nonzero value if a shell is available, or 0 if  no
          shell is available.

       *  If  a  child  process  could  not  be  created,  or  its  status could not be
          retrieved, the return value is -1.

       *  If a shell could not be executed in the child process, then the return  value
          is  as  though the child shell terminated by calling _exit(2) with the status
          127.

       *  If all system calls succeed, then the return value is the termination  status
          of  the  child  shell  used to execute command.  (The termination status of a
          shell is the termination status of the last command it executes.)

       In the last two cases, the return value is a "wait status" that can be  examined
       using  the macros described in waitpid(2).  (i.e., WIFEXITED() WEXITSTATUS() and
       so on).

       system() does not affect the wait status of any other children.

	
*/
#define ERR_EXIT(m) \
	do \
	{ \
		perror(m); \
		exit(-1); \
	}while(0)
	
	
	void pr_exit(int status)
{
	if(	WIFEXITED(status)){
			printf("子进程正常终止，退出码 exit status= %d\n",  WEXITSTATUS(status));
	}else if(	WIFSIGNALED(status)){
			printf("子进程异常终止，退出码 signal number= %d%s\n",  WTERMSIG(status),
			#ifdef WCOREDUMP
				WCOREDUMP(status) ? "(core file generated)" : "");
			#else
				"");
			#endif
			
		}else if(	WIFSTOPPED(status)){
			printf("子进程 stopped，退出码 signal number= %d\n",  WSTOPSIG(status));
		}
}
	
	//实现system的原理 
	//暂时先忽略信号处理 posix1.1要求system()忽略SIGINT和SIGQUIT,阻塞SIGCHLD
	int my_system(const char * command){
		pid_t pid;
		int status;
		
		if(command == NULL){
			return 1;
		}
		
		if((pid = fork()) < 0){
			status = -1;	
		}else if(pid == 0){
			execl("/bin/sh", "sh", "-c", command, NULL);//execle执行新的进程以后，pid不会发生变化
			printf("execl 执行失败,如同shell执行了exit(127)\n");
			_exit(127);	//不能用exit，是为了防止任一标准I/O缓冲
			//(这些缓冲会在fork中由父进程复制给子进程)在子进程中被冲洗
		}else{
			while(waitpid(pid, &status, 0) < 0){//waitpid记录了执行shell的终止状态
				if(errno == EINTR)
					continue;
					status = -1;
					break;	
			}
		}
		return status;
	}
	
void test()
{
	int status;
	printf("-------------date-----------------------\n");
	if((status = system("date")) < 0)
		ERR_EXIT("system() error");
	pr_exit(status);
	printf("---------------nosuchcommand---------------------\n");
	if((status = system("nosuchcommand")) < 0)
		ERR_EXIT("system() error");
	pr_exit(status);
		printf("---------------who; exit 44---------------------\n");
	if((status = system("who; exit 44")) < 0)
		ERR_EXIT("system() error");	
	pr_exit(status);
}
int main(void )
{
	test();
	printf("------------my_system()------------------------\n");	
	my_system("ls -l | wc -w");
	
	printf("hello...\n");
	exit(0);
}








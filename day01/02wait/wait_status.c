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

	子进程退出状态的使用
	
	关闭或阻止core文件生成： $ulimit -c 0
	打开core文件生成： $ulimit -c unlimited
	检查core文件的选项是否打开： $ulimit -a

*/

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

int main(void )
{	
	pid_t pid;
	int status;
	
	if((pid = fork()) < 0){
		perror("fork error");
	}else	if (pid == 0){
		exit(7);//子进程正常退出
	}
 	if(wait(&status) != pid){//wait返回的是子进程的PID，它通常是结束的子进程
 		perror("wait error");
 	}
	pr_exit(status);
//----------------------------
	if((pid = fork()) < 0){
		perror("fork error");
	}else	if (pid == 0){
		abort();//子进程异常终止 SIGABRT 6
	}
 	if(wait(&status) != pid){
 		perror("wait error");
 	}
	pr_exit(status);

//----------------------------
	if((pid = fork()) < 0){
		perror("fork error");
	}else	if (pid == 0){
		status /= 0;//子进程异常终止 SIGFPE 8
	}
 	if(wait(&status) != pid){//wait返回的是子进程的PID，它通常是结束的子进程
 		perror("wait error");
 	}
	pr_exit(status);

	printf("hello...\n");
	exit(0);
}


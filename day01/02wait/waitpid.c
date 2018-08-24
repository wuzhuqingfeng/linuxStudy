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
	int ret;
	
	if((pid = fork()) < 0){
		perror("fork error");
	}else	if (pid == 0){
		sleep(3);
		printf("this is child\n");
		
		//exit(7);//子进程正常退出
		abort();//非正常退出
	}
	
		printf("this is parent\n");
	
#if 1
	//使用wait
 	if( (ret = wait(&status)) != pid){//wait返回的是子进程的PID，它通常是结束的子进程
 		perror("wait error");
 	}
#endif

//pid_t waitpid(pid_t pid, int *status, int options);
//pid == 0 等待其组I D等于调用进程的组ID的任一子进程。换句话说是与调用者进程同在一个组的进程。
//pid < -1 等待其组I D等于pId的绝对值的任一子进程。
// options:
//   WNOHANG     return immediately if no child has exited, 使waitpid不阻塞
#if 0
//pid == -1 等待任一子进程。于是在这一功能方面waitpid与wait等效
 	ret = waitpid(-1, &status, 0);
#endif

#if 0
//pid > 0 等待其进程ID与pId相等的子进程
 	ret = waitpid(pid, &status, 0);
#endif

	pr_exit(status);


	printf("hello...\n");
	exit(0);
}








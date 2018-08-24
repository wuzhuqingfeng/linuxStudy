#include <sys/types.h>
#include <unistd.h>

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <signal.h>
#include <errno.h>
#include <signal.h>


int main(void )
{
	pid_t pid;
	
	printf("getpid():%d\n", getpid());
	      //int execlp(const char *file, const char *arg, ...);
	      //  int execle(const char *path, const char *arg,
           //       ..., char * const envp[]);
           
           char * const envp[] = {"aaa=111", "bbb=2222", NULL};
           
   //            int execle(const char *path, const char *arg,
     //             ..., char * const envp[]);
     //当你不填写envp时，默认传递当前用户的env环境变量、到hello印象中
      //当你填写envp时，传递你写的envp
    //env shell的环境变量的概念 
	execle("./hello", NULL, envp);

	printf("hello\n");
	return 0;
}


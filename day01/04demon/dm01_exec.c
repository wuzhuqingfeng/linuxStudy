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
     //���㲻��дenvpʱ��Ĭ�ϴ��ݵ�ǰ�û���env������������helloӡ����
      //������дenvpʱ��������д��envp
    //env shell�Ļ��������ĸ��� 
	execle("./hello", NULL, envp);

	printf("hello\n");
	return 0;
}


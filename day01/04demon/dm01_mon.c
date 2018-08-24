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
//#define S_IRUSR 00400//�û���
//#define S_IWUSR 00200//�û�д
//#define S_IRGRP 00040//�û����
//#define S_IWGRP 00020//�û���д
//#define S_IROTH 00004//������
//#define S_IWOTH 00002//����д

//umask��ʹ��
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
//-rw-rw-r-- 1 hzmct hzmct     0 8��  15 20:42 rwall
//-rw----rw- 1 hzmct hzmct     0 8��  15 20:42 nogrp

#endif

//���ùٷ�api
#if 0
 int test()
 {
	 	//man daemon ���Կ���
		//0��ʾ�ı��ض���   1��ʾ���ı�
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

//�ֶ�ʵ��daemon�Ĺ���
#if  1
   //int daemon(int nochdir, int noclose);
int my_daemon(int nochdir, int noclose)
{
	int i = 0;
	int fd0, fd1, fd2;
	pid_t pid;
	
	
	//����ػ�����Ҫ�����ļ�,�������Ҫ�����ض���Ȩ��
	//���ں���̳е��ļ�ģʽ���õ����������Ȩ��
	printf("%d\n", umask(0));
	
    
	pid = fork();
	if (pid == -1)
	{
		perror("fork err");
		exit(0);
	}
	
//1��ʹ�������˳�
	if (pid > 0)
	{
		exit(0);
	}
	printf("pid:%d \n", getpid());
	
	/*
		setsid()����һ���»Ự
		������ô˺����Ľ��̲���һ���������鳤,��˺�������һ���»Ự
		1���ý��̱���»Ự�ĻỰ�׽���(�Ự�׽����Ǵ����ûỰ�Ľ���)
			��ʱ�ý����ǻỰ��Ψһ���̡�
		2���ý��̳�Ϊһ���½�������鳤���̡��½�����id�Ǹõ��ý��̵Ľ���id
		3���ý���û�п����ն�
		
		
	*/
	//2����һ���»Ự
	pid = setsid();
	if (pid == -1)
	{
		perror("fork err");
		exit(0);
	}
	//3����ǰĿ¼�ĳɸ�Ŀ¼
	if (nochdir == 0)
		chdir("/");
	
	//4�ر�0��1��2�ļ�������
	if (noclose == 0)
	{
		for (i=0; i<3; i++)
		{
			close(i);
		}
	}
	
  //�൱�ڰ�0���ļ�������֮��/dev/null
	fd0 = open("/dev/null", O_RDWR); //fd�ļ�������fd-0���ļ�������ָ��/dev/null 
	fd1 = dup(0);//��0���ļ������� ��ֵ�����е��ļ������� 1
	fd2 = dup(0);//��0���ļ������� ��ֵ�����е��ļ������� 2
	
	if(fd0 != 0 || fd1 != 1 || fd2 != 2)
	{
		//һ�������ӡ��
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





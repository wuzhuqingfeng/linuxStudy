#include <sys/types.h>
#include <unistd.h>

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <signal.h>
#include <errno.h>
#include <signal.h>

/*
	exit�������IO������,
	_exit(0)������ջ�����
*/
#if 0
void test()
{
	printf("hello....");//û��\n
	exit(0); //��c�⺯�� =======�����������������ڵ���_exit
}
#endif

/*
	�����ӡ��hello....
*/
#if 0
void test()
{
	printf("hello....");
	_exit(0);//ϵͳ����
}
#endif


/*
	\n������ˢ�»�����������
*/
#if 0
void test()
{
	printf("hello....\n");//����\n
	_exit(0);//ϵͳ����
}
#endif

/*
	fflushˢ�»�����
*/

#if 0
void test()
{
		printf("hello....  fddddddddd1111");
		fflush(stdout);
		_exit(0); //ϵͳ����
}
#endif

/*
	exit �� _exit
	����1����ջ������Ĳ���
	����2��exit�������ֹ�������
	
	�й���ֹ�������
		atexit����ע����ֹ�������ANSI C�涨������ע��32����ֹ�������
		��ֹ�������ĵ�����ע������෴
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
	//ע��ص�����  ��ע��ĺ�����ִ��
	atexit(bye1);
	atexit(bye2);
	printf("hello....dddddd\n");
	exit(0); //exit�������ֹ�������
}
#endif

/*
	abort()��ʹ�쳣������ֹ��ͬʱ����SIGABRT�źŸ����ý��̡� 

*/
#if 0
void test()
{
	printf("hello....  fddddddddd1111\n");
	abort();//��һ�ַ���
}
#endif

/*
	ʹ����ǿ���˳� ctrl+ c -��
	SIGINT
		������ֹ(interrupt)�ź�, ���û�����INTR�ַ�(ͨ����Ctrl-C)ʱ������
		����֪ͨǰ̨��������ֹ���̡�

	SIGQUIT
		��SIGINT����, ����QUIT�ַ�(ͨ����Ctrl-\)������. ���������յ�SIGQUIT�˳�ʱ
		�����core�ļ�, �����������������һ����������źš�
*/
#if 1
void test()
{
	printf("hello....  fddddddddd1111\n");
	sleep(100);//���жϵ�˯��״̬
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







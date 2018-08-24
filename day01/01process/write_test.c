#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <fcntl.h>
#include <sys/resource.h>
#include <signal.h>
#include <errno.h>
#include <string.h>

/*
	write����
	write������������������¿���д����ֽ���С��ָ�����ֽ�����

	1)�ڵײ�����������û���㹻�Ŀռ�
	2)RLIMIT_FSIZE������
	3)д�뱻�źŴ��

	���ں˴���������count�ڴ���MAX_RW_COUNT������£��ḳֵΪMAX_RW_COUNT

	��MAX_RW_COUNT��һ���꣬չ��Ϊ��INT_MAX & PAGE_MASK

		INT_MAXҲ��һ���꣬չ��Ϊ((int)(~0U>>1))��Ҳ�����޷�����0ȡ��������һλת����int���ͣ�
	Ҳ����2^31.
	
		PAGE_MASKҲ��һ���꣬չ��Ϊ(~(PAGE_SIZE-1))����PAGE_SIZEչ��Ϊ(_AC(1,UL) << PAGE_SHIFT)��
	PAGE_SHIFT��ֵΪ12��Ҳ����ÿҳ�Ĵ�С��212��Ҳ����˵1����12λ��PAGE_SIZE��ֵΪ212��Ȼ��
	PAGE_SIZE-1ȡ��

		���MAX_RW_COUNT��ֵΪINT_MAX & PAGE_MASK��Ҳ����˵MAX_RW_COUNT��ֵ��int�����ֵ���12λ
	���ε�������4K��ַ����

	���������Ͻ���ÿ��write��д��buff��С��2^31-212=2147479552����Ҳ����ʵ�ʵĲ��Խ����һ��
*/

void sigsegvHandler(int sig, siginfo_t *info, void *secret) {
	printf("%d %s", sig, secret);
}
void sigtermHandler(int sig) {
	printf("%d\n", sig);
}

void setupSignalHandlers(void) {
	struct sigaction act;

	sigemptyset(&act.sa_mask);
	act.sa_flags = 0;
	act.sa_handler = sigtermHandler;
	sigaction(SIGTERM, &act, NULL);

	sigemptyset(&act.sa_mask);
	act.sa_flags = SA_NODEFER | SA_RESETHAND | SA_SIGINFO;
	act.sa_sigaction = sigsegvHandler;
	sigaction(SIGSEGV, &act, NULL);
	sigaction(SIGBUS, &act, NULL);
	sigaction(SIGFPE, &act, NULL);
	sigaction(SIGILL, &act, NULL);
	return;
}

int main(int argc, char** argv){
	signal(SIGHUP, SIG_IGN);
	signal(SIGPIPE, SIG_IGN);
	setupSignalHandlers();
	//extern int errno;
	struct rlimit limit;
	limit.rlim_cur = RLIM_INFINITY;
	limit.rlim_max = RLIM_INFINITY;
	if (setrlimit(RLIMIT_FSIZE, &limit)){
		printf("set limit failed\n");
	}
	long long buff_size = atoll(argv[1]);
	char *buff = malloc(buff_size*sizeof(char));
	int fd = open("io.dat", O_CREAT | O_WRONLY | O_TRUNC, 0644);
	int ret = 0;
	while (buff_size > 0){
		ret = write(fd, buff, buff_size);
		printf("written %d bytes\n", ret);
		if (ret < 0){
			printf("write error: %s\n", strerror(errno));
			return 0;
		}
		buff_size -= ret;
		if (buff_size == 0) break;
	}
	printf("write %lld bytes\n", buff_size);
	return 0;
}
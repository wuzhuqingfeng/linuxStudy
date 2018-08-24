#include <sys/types.h>
#include <unistd.h>

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <signal.h>
#include <errno.h>
#include <signal.h>



extern char **environ;

int main()
{
	int i = 0;
	printf("getpid():%d\n", getpid());
	
	for (i=0; environ[i] != NULL; i++)
	{
		printf("%s\n", environ[i]);
	}
	
	return 0;
	
}







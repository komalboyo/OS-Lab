#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
int mkfifo(const char *filename, mode_t mode);

int main()
{
	int res = mkfifo("/tmp/my_fifo", 0777);
	if (res == 0) printf("FIFO created\n");
	exit(EXIT_SUCCESS);
}

/*
We can look for the pipe with
$ ls -lF /tmp/my_fifo
prwxr-xr-x 1 rick users 0 July 10 14:55 /tmp/my_fifo|
*/

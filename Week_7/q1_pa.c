//Sender Program:
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#define MAX_TEXT 512
struct my_msg_st {
	long int my_msg_type;
	//char some_text[MAX_TEXT];
	int num;
};

int main()
{
	int running = 1;
	struct my_msg_st some_data;int msgid;
	int n;
	msgid = msgget((key_t)1111, 0666 | IPC_CREAT);
	if (msgid == -1) {
		fprintf(stderr, "msgget failed with error: %d\n", errno);
		exit(EXIT_FAILURE);
	}
	while(running) {
		if (n < 0) {
			running = 0;
		}
		else {
			printf("Enter a number:");
			scanf("%d", &n);
			some_data.my_msg_type = 1;
			some_data.num = n;
			if (msgsnd(msgid, (void *)&some_data, MAX_TEXT, 0) == -1) {
				fprintf(stderr, "msgsnd failed\n");
				exit(EXIT_FAILURE);
			}
		}
	}
	exit(EXIT_SUCCESS);
}

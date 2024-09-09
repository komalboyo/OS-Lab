//Receiver program:
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
struct my_msg_st {
	long int my_msg_type;
	int num;
};

int main()
{
	int running = 1;
	int msgid;
	struct my_msg_st some_data;
	long int msg_to_receive = 0;
	msgid = msgget((key_t)1111, 0666 | IPC_CREAT);
	if (msgid == -1) {
		fprintf(stderr, "msgget failed with error: %d\n", errno);
		exit(EXIT_FAILURE);
	}
	while(running) {
		if (msgrcv(msgid, (void *)&some_data, BUFSIZ, msg_to_receive, 0) == -1) {
			fprintf(stderr, "msgrcv failed with error: %d\n", errno);
			exit(EXIT_FAILURE);
		}
		/*ACTUAL LOGIC*/
		if (some_data.num < 0) {
			running = 0;
		}
		else {
			printf("You wrote: %d\n", some_data.num);
			int n = some_data.num;
			int sum = 0;
			int rem;
			while(n>0){
				rem = n%10;
				sum = sum*10 + rem;
				n = n/10;
			}
			if (sum == some_data.num) printf("The number is a palindrome: %d\n", sum);
			else printf("The number is NOT a palindrome: %d\n", some_data.num);
		}	
	}
	if (msgctl(msgid, IPC_RMID, 0) == -1) {
		fprintf(stderr, "msgctl(IPC_RMID) failed\n");
		exit(EXIT_FAILURE);
	}
	exit(EXIT_SUCCESS);
}

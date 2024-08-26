//consumer.c
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <limits.h>
#include <sys/types.h>
#include <sys/stat.h>
#define FIFO_NAME "/tmp/my_fifo"
#define MAX_SIZE 5
int main()
{
	int pipe_fd;
	int count;
	int open_mode = O_RDONLY;
	
	pipe_fd = open(FIFO_NAME, open_mode);
	while (1) {
		if (read(pipe_fd, &count, sizeof(count)) > 0){
			if (count > 0) {
			    count--;
			    printf("Consumer: Shelf count is %d.\n", count);
			    write(pipe_fd, &count, sizeof(count));  // Send the updated count to the consumer
			} 
			else {
			    printf("Producer: Shelf is full. Cannot add more items.\n");
			}
			sleep(1);  // Simulate time taken to add an item
		}
    	}
	//printf("Process %d finished\n", getpid());
	close(pipe_fd);
	exit(EXIT_SUCCESS);
}

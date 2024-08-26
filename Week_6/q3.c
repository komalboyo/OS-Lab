#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <limits.h>
#include <sys/types.h>
#include <sys/stat.h>
#define FIFO_NAME "/tmp/q3Fifo"

int main()
{
  if (access(FIFO_NAME, F_OK) == -1) 
  {
	int res = mkfifo(FIFO_NAME, 0777);
	if (res != 0) 
	{
	    fprintf(stderr, "Could not create fifo %s\n", FIFO_NAME);
	    exit(EXIT_FAILURE);
	}
  }
		
  int c_pid=fork();
  
  if(c_pid<0)
  {
    perror("Child Could not be created");
    exit(-1);
  }
  
  else if(c_pid==0)
  {
    char buffer[256];
    while(buffer[0]!='x')
    {
	    int pipe = open(FIFO_NAME,O_WRONLY);
	    printf("Child: ");
	    scanf("%[^\n]s",buffer);
	    if(buffer[0]=='x')
	      exit(0);
	    write(pipe,buffer,sizeof(buffer));
	    close(pipe);
	    pipe = open(FIFO_NAME,O_RDONLY);
	    read(pipe,buffer,sizeof(buffer));
	    printf("Parent says: %s\n",buffer);
	    close(pipe);
    }
    exit(0);
  }
  
  else
  {
    char buffer[256];
    while(buffer[0]!='x')
    {
            int pipe = open(FIFO_NAME,O_RDONLY);
	    read(pipe,buffer,sizeof(buffer));
	    if(buffer[0]=='x')
	      exit(0);
	    printf("Child says: %s\n",buffer);
	    close(pipe);
	    pipe = open(FIFO_NAME,O_WRONLY);
	    printf("Parent: ");
	    scanf("%[^\n]s",buffer);
	    write(pipe,buffer,sizeof(buffer));
	    close(pipe);
	    
    }
    exit(0);
   }
}

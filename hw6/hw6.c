#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/time.h>

#define NUM_OF_PIPES 5

int main(){
	//pid_t cpid[NUM_OF_PIPES];
	
	int comm[2];
	int result = pipe(comm);
	char buffer;

	if(result == -1){
		printf("Pipe could not be created\n");
		exit(0);
	}

	pid_t cpid = fork();
	int wstatus;
	/*for(int x = 0; x < 5; x++){
		cpid[x] = fork();
	}*/
	if(cpid == -1){
		printf("could not fork\n");
		exit(0);
	}
	if(cpid == 0){
		// start up, instantiating variables and allocating space
		close(comm[0]); //close the reading end of the pipe because we're the child
		struct timeval cur_time;
		int length;
		int current_seconds;
		int seconds; int hours; int minutes;
		int milliseconds;
		char* content = malloc(sizeof(char) * 32);
		for(int x = 0; x < 15; x++){
			gettimeofday(&cur_time, NULL);
			current_seconds = cur_time.tv_sec % (3600*12);
			milliseconds = cur_time.tv_usec % 100;
			seconds = current_seconds % 60;
			minutes = ((current_seconds - seconds) / 60) % 60;
			hours = ((current_seconds - (minutes * 60)) - seconds) / 3600;
			length = sprintf(content, "%02d:%02d:%02d:%02d Message: %d", hours, minutes, seconds, milliseconds, x);
			write(comm[1], content, length);
			write(comm[1], "\n", 1);
		}
		
		// wrap up - freeing space and closing pipe
		free(content);
		close(comm[1]);
		exit(3);
	}

	else{
		close(comm[1]); // close the writing end of the pipe because we're the parent
		while(read(comm[0], &buffer, 1) > 0){
			write(STDOUT_FILENO, &buffer, 1);
		}
		printf("child finished, exiting\n");
		close(comm[0]);
		exit(3);
	} 
	printf("test over\n");
}
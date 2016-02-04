/**************************************************************************/
/* PROGRAM: lab2.c */
/* DESCRIPTION: This program generates a chain of processes */
/* using fork(). The number of processes n is a command line argument. */
/* Each process sleeps for a random time less than 10 seconds then prints out */
/* process ID, parent ID, and child ID */
/**************************************************************************/
# include <stdio.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <unistd.h>

//argc is the number of arguments, argv is the array of arguments
int main(int argc, char *argv[])
{
	//Check and make sure wedont have more that 2 arguments
	if (argc > 2) {
        printf("\nUsage:\n");
		printf("\n %s - Runs the assignment tasks\n", argv[0]);
        printf("\n %s (Random integer) - Runs the assignment tasks, with specified sleep time\n", argv[0]);
		exit(1);
	}

	//Create directory cecs326
	mkdir("./cecs326", 0777);

	//Create a file lab2A, using a pip and a fork
	pid_t pid;
	pid = fork();

	if(pid==0) {
		execlp("bash", "bash", "-c", "echo \"This is a test file\nusing UNIX commands\" | cat >./cecs326/lab2A", NULL);
	}
	else {
		wait();
	}

	//Finish up and exit
	printf ("\n");
	printf("\nThank you! Have a nice day!\n");
	printf ("\n");
	exit(0);
}

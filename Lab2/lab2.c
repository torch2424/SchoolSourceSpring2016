/**************************************************************************/
/* PROGRAM: lab2.c Part One*/
/* DESCRIPTION: This program executes basic UNIX commands invlovling files
   and text management
*/
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

	//Create a file lab2A, fork
	pid_t pid;
	pid = fork();

	if(pid==0) {
		//Use bash to run commands and allow us to pipe
		execlp("bash", "bash", "-c", "echo \"This is a test file\nusing UNIX commands\" | cat >./cecs326/lab2A", NULL);
	}
	else {
		wait();
	}

	//Create another directory named lab2 in cecs326
	mkdir("./cecs326/lab2", 0777);

	//Use cat again to create a file named lab2b
	pid = fork();

	if(pid <= 0) {
		//Use bash to run commands and allow us to pipe another file
		execlp("bash", "bash", "-c", "echo \"This file will be merged with lab2A\nEnd of file\" | cat >./cecs326/lab2/lab2B", NULL);
	}
	else {
		wait();
	}

	//copy lab2B into cecs 326
	pid = fork();

	if(pid <= 0) {
		//Use cp to copy
		execlp("cp", "cp", "./cecs326/lab2/lab2B", "./cecs326",  NULL);
	}
	else {
		wait();
	}

	//merge the files
	pid = fork();


	if(pid <= 0) {
		//Use bash to run commands and allow us to pipe
		//use cat to concatenate the two files
		execlp("bash", "bash", "-c", "cat ./cecs326/lab2A ./cecs326/lab2/lab2B > lab2C",  NULL);
	}
	else {
		wait();
	}

	//Remove all files in cecs326 and lab2
	pid = fork();

	if(pid <= 0) {
		//Use bash to run commands and allow us to pipe
		execlp("rm", "rm", "-rf", "./cecs326", NULL);
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

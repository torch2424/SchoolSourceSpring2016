/**************************************************************************/
/* PROGRAM: lab6acquire.c */
/* DESCRIPTION: The parent generates a child process */
/* passes it arguements, and then waits for it to exit.*/
/**************************************************************************/

//Includes
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/types.h>
# include <fcntl.h>
# include <errno.h>

//Declare our helper functions
void printUsage(char *programName);
void checkInput(int argc, char *argv[]);

//Our main functions
int main(int argc, char *argv[])
{

    //First check the input
    checkInput(argc, argv);

    //Initialize some variables
    char *fname;
    int fd, sleeptime, n_try, count=0;
    pid_t pid;

    pid = getpid();
    srand((unsigned) pid);
    fname = argv[1];
    sleeptime = atoi(argv[2]);
    n_try = atoi(argv[3]);


    while ((fd = creat(fname, 0)) == -1 && errno == EACCES) if (++count < n_try) sleep(rand()%sleeptime);
    else {
        printf ("\n Unable to generate.\n"); exit(-1);
    }
    close (fd);
    printf ("\n File %s has been created\n", fname);

}

//Function to check our input
void checkInput(int argc, char *argv[]) {

    //Check the number of arguments
    //Print the usage if argument amount is invalid
    if (argc != 1) {

        //Print Usage and exit
        printUsage(argv[0]);
    }
}

//Function to print usage and exit
void printUsage(char *programName) {

    //Print the usage
    printf("\n Usage: %s\nSimply run the program, and pass no paramters to affect the lock\n\n", programName);
    //Exit
    exit(1);
}

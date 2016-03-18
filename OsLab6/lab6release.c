/**************************************************************************/
/* PROGRAM: lab5child.c */
/* DESCRIPTION: The child sleeps for a random time */
/* and prints to the console once it terminates*/
/**************************************************************************/

//Includes
# include <stdio.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>
# include <time.h>   /* Needed for struct timespec */

//Declare our helper functions
void printUsage(char *programName);
void checkInput(int argc, char *argv[]);

//Our main functions
int main(int argc, char *argv[])
{

    //First check the input
    checkInput(argc, argv);

    char *fname; int fd, sleeptime, n_try, count=0; pid_t pid;
 pid = getpid(); srand((unsigned) pid); fname = argv[1]; sleeptime = atoi(argv[2]); n_try = atoi(argv[3]);
 while (unlink(fname)!=0)
 if (++count < n_try) sleep(sleeptime);
 else { printf ("\n Cannot release file\n"); exit(-1);
 }
 printf ("\n File is released\n"); 

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

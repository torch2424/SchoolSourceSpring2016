/**************************************************************************/
/* PROGRAM:  project3Parent.c */
/*
    DESCRIPTION: This program will call 3 children
    processes to try to acquire the lock of a file,
    it will delete previous invocations of the file,
    as well as display the wait status

 */
/**************************************************************************/

//Includes
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <sys/wait.h>

//Declare our helper functions
void printUsage(char *programName);
void checkInput(int argc, char *argv[]);

//Our main functions
int main(int argc, char *argv[])
{

    //First check the input
    checkInput(argc, argv);

    //Initialize our variables
    char *fname;
    char *lockFileName = "lock";
    int sleeptime, n_try, count=0;
    pid_t pid;

    //Set our variables
    pid = getpid();
    srand((unsigned) pid);

    //Get our filname, # tries, and sleeptime
    fname = argv[1];
    n_try = atoi(argv[2]);
    sleeptime = atoi(argv[3]);

    //Try to remove all previous versions of the file
    //Check if it exists first
    if( access( lockFileName, F_OK ) != -1 ) {

        //File exists, try to remove it
        while (unlink(lockFileName)!=0) if (++count < n_try) sleep(sleeptime);
        else {
            printf ("\n Cannot release previous invocations of %s\n", lockFileName); exit(-1);
        }
    }

    //Create our children
    int k;
    for(k = 0; k < 3; ++k) {

        //Create our forkstatus
        pid_t forkStatus;

        //Create our command to exec()
        char *childFork[5];
        childFork[0] = "./child";
        childFork[1] = fname;
        childFork[2] = argv[2];
        childFork[3] = argv[3];
        sprintf(childFork[4], "%d", k);

        //Fork a child
        if ((forkStatus = fork()) == 0) {

            //Print the value,
            //and execute the child program
            //passing the sleep time
            execvp(childFork[0], &childFork[0]);

            printf("\nExec failure. Could not exec %s for child #%d\n", childFork[0], k);
            exit(1);
        }
        //Fork Failure
        else if(forkStatus == -1) printf("Unable to fork child #%d\n", k);
    }

    //Wait for the children, and display the status

    //Create our waitstatus
    pid_t waitStatus;
    int status;

    //Loop while waiting
    while((waitStatus = wait(&status)) && waitStatus != - 1) {

        //When the child dies, print the wait status
        if (waitStatus != - 1) printf ("Wait on PID: %d returns status of: %04X\n", waitStatus, (int) (status >> 8));
    }

    //Finally, Exit the program
    exit(0);
}

//Function to check our input
void checkInput(int argc, char *argv[]) {

    //Check the number of arguments
    //Print the usage if argument amount is invalid
    if (argc != 4) {

        //Print Usage and exit
        printUsage(argv[0]);
    }

    //Check for characters on integers
    int count;
    for(count = 2; count < 4; count++) {

        int value;
        if(sscanf(argv[count], "%d", &value) != 1) {

            //Print Usage and exit
            printUsage(argv[0]);
        }
    }

    //check retry bounds
    if(atoi(argv[2]) < 1) {

       //Print Usage and exit
       printUsage(argv[0]);
    }

    //check sleep bounds
    if(atoi(argv[3]) < 1) {

        //Print Usage and exit
        printUsage(argv[0]);
    }
}

//Function to print usage and exit
void printUsage(char *programName) {

    //Print the usage
    printf("\n Usage: %s [String: Name of the file] [Integer: 0 < # of times to retry accessing the file] [Integer: 0 < Sleep Time] \n\n", programName);
    //Exit
    exit(1);
}

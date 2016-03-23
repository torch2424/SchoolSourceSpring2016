/**************************************************************************/
/* PROGRAM:  project3Child.c */
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
#include <fcntl.h>
#include <errno.h>
#include <sys/types.h>
#include <unistd.h>

//Declare our helper functions
void printUsage(char *programName);
void checkInput(int argc, char *argv[]);

int main(int argc, char *argv[])
{

    //First check the input
    checkInput(argc, argv);

    //Initialize variables
    char *fname;
    char *lockFileName = "lock";
    int childNumber = atoi(argv[4]);
    int fd, sleeptime, n_try, count=0;
    pid_t pid;
    pid = getpid();
    srand((unsigned) pid);

    //Get filename,sleeptime,tries from commands line argument
    fname = argv[1];
    sleeptime = atoi(argv[2]);
    n_try = atoi(argv[3]);

    //Loop to create the lock
    while ((fd = creat(lockFileName, 0)) == -1 && errno == EACCES) {

        //Was not able to get the lock


        //sleep for a random time until count is equal to n_try
        //in which case, print message and exit
        if (++count < n_try) {

            sleep(rand() % sleeptime);
        }
        else {

            //Couldnt get the lock after so many tries
            //print, and exit with signal of child number
            printf ("\n Unable to obtain lock file\n");
            exit(childNumber);
        }
    }
    //finally, close the lock
    close (fd);


    //Read the contents of the file using cat
    pid_t catStatus;
    //Fork a child
    if ((catStatus = fork()) == 0) {

        //Cat the file
        execlp("/bin/cat", "cat", fname, (char*)NULL);
    }
    //Fork Failure
    else if(catStatus == -1) printf("\nUnable to fork cat, unable to read the file.\n");


    //Remove the lock file
    while (unlink(lockFileName)!=0) {

        if (++count < n_try) sleep(sleeptime);
        else { printf ("\n Cannot release lock\n"); exit(childNumber);
        }
    }


    //Exit the program
    //Exit with least significant 8 bits(1 byte) of PID
    exit(getpid() & 0xff);
}




//Function to check our input
void checkInput(int argc, char *argv[]) {

    //Check the number of arguments
    //Print the usage if argument amount is invalid
    if (argc != 5) {

        //Print Usage and exit
        printUsage(argv[0]);
    }

    //Check for characters on integers
    int count;
    for(count = 2; count < 5; count++) {

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

    //check child bounds
    if(atoi(argv[4]) < 0 ||
    atoi(argv[4]) > 2) {

       //Print Usage and exit
       printUsage(argv[0]);
    }
}

//Function to print usage and exit
void printUsage(char *programName) {

    //Print the usage
    printf("\n Usage: %s [Integer: Child Number] [String: Name of the file] [Integer: 0 < # of times to retry accessing the file] [Integer: 0 < Sleep Time] \n\n", programName);
    //Exit
    exit(1);
}

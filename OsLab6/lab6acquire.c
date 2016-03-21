/**************************************************************************/
/* PROGRAM: lab6acquire.c */
/* DESCRIPTION: This creates a file of the specified name, */
/* and if it is unable to, it will sleep and retry a specified amount */
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

    //check sleep bounds
    if(atoi(argv[2]) < 1) {

       //Print Usage and exit
       printUsage(argv[0]);
    }

    //check retry bounds
    if(atoi(argv[3]) < 1) {

        //Print Usage and exit
        printUsage(argv[0]);
    }
}

//Function to print usage and exit
void printUsage(char *programName) {

    //Print the usage
    printf("\n Usage: %s [String: Name of the file] [Integer: 0 < Sleep Time] [Integer: 0 < # of times to retry accessing the file] \n\n", programName);
    //Exit
    exit(1);
}

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

    //Intialize variables
    pid_t pid; int ret_value;

    //Get out pid
    pid = getpid();

    //Get our return value
    ret_value = (int) (pid % 256);

    //Set up our seed
    srand(pid);

    //Sleep a random time
    int randSleep = (rand() % atoi(argv[1])) + 1;
    sleep(randSleep);

    //Print we are terminating
    //And kill or exit the process accordingly
    if (atoi(*(argv + 1)) % 2) {

        printf("Child %d is terminating with signal 009\n", pid);
        kill(pid, 9);
    }
    else {

        printf("Child %d is terminating with exit(%04X)\n", pid, ret_value);
        exit(ret_value);
    }
}

//Function to check our input
void checkInput(int argc, char *argv[]) {

    //Check the number of arguments
    //Print the usage if argument amount is invalid
    if (argc != 2) {

        //Print Usage and exit
        printUsage(argv[0]);
    }

    //Check for characters
    int count;
    for(count = 1; count < 2; count++) {

        int value;
        if(sscanf(argv[count], "%d", &value) != 1) {

            //Print Usage and exit
            printUsage(argv[0]);
        }
    }

    //check sleep bounds
    if(atoi(argv[1]) < 1 ||
       atoi(argv[1]) > 50) {

        //Print Usage and exit
        printUsage(argv[0]);
    }
}

//Function to print usage and exit
void printUsage(char *programName) {

    //Print the usage
    printf("\n Usage: %s [Integer: 0 < Sleep Time < 50] \n", programName);
    //Exit
    exit(1);
}

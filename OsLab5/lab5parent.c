/**************************************************************************/
/* PROGRAM: lab5parent.c */
/* DESCRIPTION: The parent generates a child process */
/* passes it arguements, and then waits for it to exit.*/
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
    pid_t pid, w; int k, status; char value[3];

    //Loop through our values
    for (k = 0;k < 3; ++k) {

        //Fork a child
        if ((pid = fork()) == 0) {

            //Print the value,
            //and execute the child program
            sprintf(value, "%d", k);
            execl("child", "child", value, (char *) 0);
        }

        //Parent, print the forked child
        else printf ("Forked child %d\n", pid);
    }

    /* Wait for children */
    //Loop while waiting
    while ((w = wait(&status)) && w != - 1) {

        //When the child dies, print the wait status
        if (w != - 1) printf ("Wait on PID: %d returns status of: %04X\n", w, status);
    }

    //Exit the program
    exit(0);
}

//Function to check our input
void checkInput(int argc, char *argv[]) {

    //Check the number of arguments
    //Print the usage if argument amount is invalid
    if (argc != 3) {

        //Print Usage and exit
        printUsage(argv[0]);
    }

    //Check for characters
    int count;
    for(count = 1; count < 3; count++) {

        int value;
        if(sscanf(argv[count], "%d", &value) != 1) {

            //Print Usage and exit
            printUsage(argv[0]);
        }
    }

    //check child bounds
    if(atoi(argv[2]) < 1 ||
       atoi(argv[2]) > 20) {

       //Print Usage and exit
       printUsage(argv[0]);
    }

    //check sleep bounds
    if(atoi(argv[3]) < 1 ||
       atoi(argv[3]) > 50) {

        //Print Usage and exit
        printUsage(argv[0]);
    }
}

//Function to print usage and exit
void printUsage(char *programName) {

    //Print the usage
    printf("\n Usage: %s [Integer: 0 < # of Child Processes # < 20] [Integer: 0 < Sleep Time < 50] \n", programName);
    //Exit
    exit(1);
}

/**************************************************************************/
/* PROGRAM:  project5.c */
/*
    DESCRIPTION: This program will create a
    critical selection by forking the program to
    print various information about the process
    and be regulated by semaphores

    For operating systems, Project #5
 */
/**************************************************************************/

//Includes
# include <stdio.h>
# include <sys/types.h>
# include <sys/ipc.h>
# include <sys/sem.h>
# include <unistd.h>
# include <stdlib.h>
# include <time.h>
# include <string.h>
# include <stdbool.h>
# include <sys/wait.h>

//Declare our helper functions
void printUsage(char *programName);
void checkInput(int argc, char *argv[]);
bool writeBuffer(int childNum, pid_t childPid, int delay);

//Create our union for our semaphores
//Used for semctl
union semun {
    int val;
    struct semid_ds *buf;
};

int main(int argc, char *argv[])
{

    //Verify our input
    checkInput(argc, argv);

    //Initialize i for loops
    int i;

    //Grab our input

    //Get our number of child processes
    int numChild = atoi(argv[1]);

    //Get our ropt (remove the semaphores or not)
    bool semProtect;
    if(strcmp(argv[1], "s") == 0) {
        semProtect = true;
    }
    //Since it wasnt remove, it must be false

    //Lastly, grab our delay adjustment for priting
    int delayAdjust = atoi(argv[3]);

    //Get our semaphore array length (Only need a single semaphore)
    int NS = 1;

    //Initialize our semaphore specific variables
    int sem_id, sem_value;
    key_t ipc_key;
    struct semid_ds sem_buf;
    union semun arg;

    //get our key to generate our semphore id's
    ipc_key = ftok(".", 'S');

    /* Create semaphore */
    //Using IPC_CREAT since we are creating multiple semaphore
    if ((sem_id = semget(ipc_key, NS, IPC_CREAT | IPC_EXCL | 0666)) == -1) {

        perror ("Error: Could not create semaphore");
        exit(1);
    }

    /* Set arg (the union) to the address of the storage location for */
    /* returned semid_ds value */
    //Return the semphores values
    arg.buf = &sem_buf;
    if (semctl(sem_id, 0, IPC_STAT, arg) == -1) {

        perror ("Error: Could not store the address in union buf using IPC_STAT");
        exit(2);
    }


    //Finally create a loop to fork our children
    for(i = 0; i < numChild; ++i) {

        //Create our forkstatus
        pid_t forkStatus;

        //Fork a child
        if ((forkStatus = fork()) == 0) {

            //Check if we would like semaphore protection
            //Checking false first for code cleanliness
            if(!semProtect) writeBuffer(i, forkStatus, delayAdjust);
            else {
                //Boolean for if we are still waiting
                bool waiting = true;
                while(waiting) {

                    //Get our semaphore value in a loop
                    sem_value = semctl(sem_id, i, GETVAL, 0);
                    while (sem_value != -1 || sem_value != 0) sem_value = semctl(sem_id, i, GETVAL, 0);

                    if(sem_value == 0) {

                        //Immediately lock the semphore
                        /* Set arg (the union) to the address of the initializing vector */
                        // Set all of the semaphore's values to arg
                        arg.val = 1;

                        if (semctl(sem_id, 0, SETVAL, arg) == -1) {

                            char errorString[100];
                            sprintf(errorString, "ERROR: Could not set the value for semaphore %d", i);
                            perror(errorString);
                            exit(3);
                        }

                        //Call function to write a buffer
                        //Return bang since it will return true ,on success
                        waiting = !writeBuffer(i, forkStatus, delayAdjust);

                        //Unlock the semephore
                        arg.val = 0;

                        if (semctl(sem_id, 0, SETVAL, arg) == -1) {

                            char errorString[100];
                            sprintf(errorString, "ERROR: Could not set the value for semaphore %d", i);
                            perror(errorString);
                            exit(3);
                        }
                    }
                    else if(sem_value == -1) {

                        //Print an error
                        char errorString[100];
                        sprintf(errorString, "ERROR: Could not retrieve the value for semaphore %d", i);
                        perror(errorString);
                        exit(4);
                    }
                }
            }

            //We are no longer waiting or writing, Exit the program
            exit(1);
        }
        //Fork Failure
        else if(forkStatus == -1) printf("Unable to fork child #%d\n", i);
    }

    //Wait for our children
    pid_t pid;
    while (pid = waitpid(-1, NULL, 0)) {
    }

    //Remove the semaphore
    if (semctl(sem_id, 0, IPC_RMID, 0) == -1) {

        perror ("ERROR: Could not remove the semaphore");
        exit(5);
    }

    //Finally exit
    exit(0);
}

//Function to check our input
void checkInput(int argc, char *argv[]) {

    //Check the number of arguments
    //Print the usage if argument amount is invalid
    //We need at least 4 arguments, since it is
    //Program name, option, number(>=1), sem value
    if (argc != 4) {

        //Print Usage and exit
        printUsage(argv[0]);
    }

    //Check for characters on integers
    int value;
    if(sscanf(argv[1], "%d", &value) != 1) {

        //Print Usage and exit
        printUsage(argv[0]);
    }
    else if(sscanf(argv[3], "%d", &value) != 1) {

        //Print Usage and exit
        printUsage(argv[0]);
    }


    //Check that the ropt (argv[1]) option is s for protection
    //or n for no protection
    // 0 in strcmp means equal
    if(strcmp(argv[2], "s") != 0 && strcmp(argv[2], "n") != 0) {

       //Print Usage and exit
       printUsage(argv[0]);
    }

    //Check that values are not negative
    if(atoi(argv[1]) < 0 || atoi(argv[3]) < 0) printUsage(argv[0]);
}

//Function to print usage and exit
void printUsage(char *programName) {

    //Print the usage
    printf("\n Usage: %s  [Integer: Number of Child Processes > 0] [Character: n for no semphore protection, s for semaphore protection] [Integer: Amount of output delay > 0]\n", programName);
    //Exit
    exit(1);
}

//Function to write to a buffer
bool writeBuffer(int childNum, pid_t childPid, int delay) {

    //Max cannon, maximum numbers of characters in the array
    int maxCannon = 255;

    //Create a buffer
    char semBuffer [maxCannon];

    //Set the buffer, and store its size
    int size = sprintf (semBuffer, "i: %d process ID:%ld parent ID:%ld child ID:%ld", childNum, (long) getpid(),  (long) getppid(), (long) childPid);

    //Print our while not pointed to the end
    int i;
    for(i = 0; i < size; ++i) {

        //Print the character from the buffer
        fputc(semBuffer[i], stdout);

        //Sleep for the delay
        sleep(delay);
    }


    //Return false since the writing
    //was successful
    return true;
}

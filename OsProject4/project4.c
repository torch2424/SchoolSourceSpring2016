/**************************************************************************/
/* PROGRAM:  project4.c */
/*
    DESCRIPTION: This program will create an
    inputted number of semaphores, and then
    assign them the inputted values. They will then
    be removed or kept depending on the user input

    For operating systems, Project #4
 */
/**************************************************************************/

# include <stdio.h>
# include <sys/types.h>
# include <sys/ipc.h>
# include <sys/sem.h>
# include <unistd.h>
# include <stdlib.h>
# include <time.h>
# include <string.h>
# include <stdbool.h>

//Declare our helper functions
void printUsage(char *programName);
void checkInput(int argc, char *argv[]);

//Create our union for our semaphores
union semun {
    int val; struct semid_ds *buf; ushort *array;
};

int main(int argc, char *argv[])
{
    //Verify our input
    checkInput(argc, argv);

    //Grab our input
    //Get our ropt (remove the semaphores or not)
    bool removeOption = false;
    if(strcmp(argv[1], "r") == 0) {
        removeOption = true;
    }
    //Since it wasnt remove, it must be false

    //Get our number of semaphores to e created
    int NS = atoi(argv[2]);

    //Get our values for our semaphores in loop
    int semValues[NS];
    int i;
    //i = 3, since it is where values begin in args array
    for(i = 3; i < argc; i++) {
        semValues[i - 3] = atoi(argv[i]);
    }



    //Initialize our variables
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

    //Show the semphore Identifier
    printf ("Semaphore identifier %d\n", sem_id);

    /* Set arg (the union) to the address of the storage location for */
    /* returned semid_ds value */
    //Return the semphores values
    arg.buf = &sem_buf;
    if (semctl(sem_id, 0, IPC_STAT, arg) == -1) {

        perror ("semctl: IPC_STAT");
        exit(2);
    }

    //Display the time
    printf ("Create %s", ctime(&sem_buf.sem_ctime));

    //Loop through our semaphores and set their values
    for (i=0; i < NS; ++i) {

        /* Set arg (the union) to the address of the initializing vector */
        // Set all of the semaphore's values to arg
        arg.val = semValues[i];

        if (semctl(sem_id, i, SETVAL, arg) == -1) {

            perror("ERROR: Could not set the value for semaphore");
            exit(3);
        }
    }

    //Loop through our semaphores and print their values
    for (i=0; i < NS; ++i) {

        if ((sem_value = semctl(sem_id, i, GETVAL, 0)) == -1) {

            perror("ERROR: Could not retreive the semaphore value");
            exit(4);
        }
        printf ("Semaphore %d has value of %d\n",i, sem_value);
    }

    //Remove the semaphore if we have the rOpt
    if(removeOption) {
        if (semctl(sem_id, 0, IPC_RMID, 0) == -1) {

            perror ("ERROR: Could not remove semaphore");
            exit(5);
        }
    }
}

//Function to check our input
void checkInput(int argc, char *argv[]) {

    //Check the number of arguments
    //Print the usage if argument amount is invalid
    //We need at least 4 arguments, since it is
    //Program name, option, number(>=1), sem value
    if (argc < 4) {

        //Print Usage and exit
        printUsage(argv[0]);
    }

    //Check for characters on integers
    int count;
    for(count = 3; count < argc; count++) {

        int value;
        if(sscanf(argv[count], "%d", &value) != 1) {

            //Print Usage and exit
            printUsage(argv[0]);
        }
    }

    //Check that the ropt (argv[1]) option is r or n
    // 0 in strcmp means equal
    if(strcmp(argv[1], "r") != 0 && strcmp(argv[1], "n") != 0) {

       //Print Usage and exit
       printUsage(argv[0]);
    }

    //check number of semaphores
    if(atoi(argv[2]) < 1) {

       //Print Usage and exit
       printUsage(argv[0]);
    }

    //check if number of semphores = number of semphores values
    if(atoi(argv[2]) != argc - 3) {

       //Print Usage and exit
       printUsage(argv[0]);
    }

    //Semaphore values can be negative and non-negative
}

//Function to print usage and exit
void printUsage(char *programName) {

    //Print the usage
    printf("\n Usage: %s [Character: n to not remove created semaphore, r to remove the created semaphore] [Integer: Number of Semphores > 0] [Integer...Integerx: Semaphor Value. The number of semaphore values (1,2,...x) MUST match the number of semaphores] \n\n", programName);
    //Exit
    exit(1);
}

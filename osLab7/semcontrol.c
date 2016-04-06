/**************************************************************************/
/* PROGRAM:  semcontrol.c */
/*
    DESCRIPTION: This program will create a lock
    read the user inputted file using cat, and then
    release the lock file, and exit with the
    least significant byte of its process id

    For operating systems, Lab #7

 */
/**************************************************************************/

# include <stdio.h>
# include <sys/types.h>
# include <sys/ipc.h>
# include <sys/sem.h>
# include <unistd.h>
# include <stdlib.h>
# include <time.h>
# define NS 3

//Create our union for our semaphores
union semun {
    int val; struct semid_ds *buf; ushort *array;
};

int main(void)
{

    //Initialize our variables
    int sem_id, sem_value, i; key_t ipc_key; struct semid_ds sem_buf;
    static ushort sem_array[NS] = {3, 1, 4}; union semun arg;

    //get our key to generate our semphore id's
    ipc_key = ftok(".", 'S');

    /* Create semaphore */
    //IPC_CREAT in part A and B, IPC_CREAT | IPC_EXCL in part c
    if ((sem_id = semget(ipc_key, NS, IPC_CREAT | IPC_EXCL | 0666)) == -1) {

        perror ("semget: IPC | 0666");
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

    printf ("Create %s", ctime(&sem_buf.sem_ctime));

    /* Set arg (the union) to the address of the initializing vector */
    // Set all of the semaphore's values to arg
    arg.array = sem_array;
    if (semctl(sem_id, 0, SETALL, arg) == -1) {
        perror("semctl: SETALL");
        exit(3);
    }

    //Loop through our semaphores and print their values
    for (i=0; i<NS; ++i) {
        if ((sem_value = semctl(sem_id, i, GETVAL, 0)) == -1) {

            perror("semctl : GETVAL");
            exit(4);
        }

        printf ("Semaphore %d has value of %d\n",i, sem_value);
    }

    /* remove semaphore */
    //Removed in part B and C of the lab
    // if (semctl(sem_id, 0, IPC_RMID, 0) == -1) {
    //     perror ("semctl: IPC_RMID");
    //     exit(5);
    // }
}

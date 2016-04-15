//Exit with least significant 8 bits(1 byte) of PID
int exitValue = (int) (pid % 256);
exit(exitValue);

/* remove semaphore */
if (semctl(sem_id, 0, IPC_RMID, 0) == -1) {
    perror ("semctl: IPC_RMID");
    exit(5);
}

--------------------------------------

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

--------------------------------------

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

--------------------------------------

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

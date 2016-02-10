/**************************************************************************/
/* PROGRAM: project1.c */
/* DESCRIPTION: This program generates a chain of processes */
/* using fork(). The number of processes n is a command line argument <= 5. */
/* They will make two child processes to make a process tree*/
/*  */
/**************************************************************************/
# include <stdio.h>
# include <stdlib.h>
# include <sys/types.h>
# include <unistd.h>
int main(int argc, char *argv[])
{
     //Initialize some variables
     int i, m, n, sleeptime, seed;
     pid_t childpid;

     //Check the number of arguments
     //Check if our # of process is valid
     //Check if sleep time is valid
     if (argc > 2 ||
         argc < 2 ||
         (argc == 2 &&
         (atoi(argv[1]) < 1 ||
         atoi(argv[1]) > 10)) ||
         (argc == 3 &&
         (atoi(argv[2]) < 1 ||
         atoi(argv[2]) > 20))) {

         printf("\n Usage: %s [# of Processes < 5] \n", argv[0]);
         exit(1);
     }

     //n is num process
     //m is sleep time
     n = atoi(argv[1]);
     if(argc > 2) m = atoi(argv[2]);
     else m = 0;

     //Set our child pid
     childpid = 0;
     //Loop through and create our children
     for(i = 0; i < n; i++) if(childpid = fork()) break;


     else if (childpid == -1) {
         perror ("\n The fork failed\n");
         exit(1);
     }

     /* since each process has a different childpid, using the childpid
     as the seed number will restart the random function.
     Therefore, each process will have a different sleeptime
     */
     seed = (int)(getpid() + childpid);
     srand(seed);

     //Sleep if we have sleep time
     if(argc > 2) {
         sleeptime = (rand() % m) + 1;
         sleep(sleeptime);
     }

     //Output to the user
     printf("\n %d: process ID:%6ld parent ID:%6ld childID:%6ld", i, (long)getpid(), (long)getppid(), (long)childpid);

     //Print sleep text if we slept
     if(argc > 2) {
       printf (" sleep = %d\n", sleeptime);
     }

    //Finish up and exit
    //No nice prompt since it messes up output
 	//printf("\nProcess Died...Thank you! Have a nice day!\n");
 	exit(0);
}

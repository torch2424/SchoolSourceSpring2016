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
# include <time.h>   /* Needed for struct timespec */
int main(int argc, char *argv[])
{
     //Initialize some variables
     int numLevels;
     pid_t childpidLeft;
     pid_t childpidRight;

     //Check the number of arguments
     //Check if our # of process is valid
     if (argc > 2 ||
         argc < 2 ||
         (argc == 2 &&
         (atoi(argv[1]) < 1 ||
         atoi(argv[1]) > 10))) {

         printf("\n Usage: %s [# of Levels < 5] \n", argv[0]);
         exit(1);
     }

     //numLevels is the number of levels we want to go down
     numLevels = atoi(argv[1]);

     //Set our child pid's
     childpidLeft = 0;
     childpidRight = 0;

     //Print our Text Header
     printf("%-25s%-20s%-10s%-10s%-10s\n", "Level", "Procs", "Parent", "Child1", "Child 2");
     printf("%-25s%-20s%-10s%-10s%-10s\n", "No.", "ID", "ID", "ID", "ID");

     //Spacing
     printf("\n");

     //Save our level and parent id here
     //Since parent can finish before the child
     int level = 0;
     pid_t parentpid = getppid();

     //Loop through and create our children
     int i;
     for(i = 0; i < numLevels; i++) {

          //Create two childrens per node
          //And, If they are children
          //Enter the if
           if((childpidLeft = fork()) == 0 || (childpidRight = fork()) == 0) {

             //Error check our children
             if (childpidLeft == -1) {
                 perror ("\n The left fork failed\n");
                 exit(1);
             }

             if (childpidRight == -1) {
                 perror ("\n The right fork failed\n");
                 exit(1);
             }

             //Increase their level
             level++;

             //Save our parent pid
             parentpid = getppid();

             //reset our children's child Pids
             childpidLeft = 0;
             childpidRight = 0;

             //sleep a little to avoid child finishing before the parent
             //Nano sleep will allow us to sleep half a second
             nanosleep((const struct timespec[]){{0, 500000000L}}, NULL);

             //Continue the loop
              continue;
           }

           //then we are parent, we need to break
            break;
        }

         //Output to the user
         printf("%-25d%-20ld%-10ld%-10ld%-10ld\n", level, (long)getpid(), (long)parentpid, (long)childpidLeft, (long)childpidRight);

    //Finish up and exit
    //Make parent wait here for cleaner output
    //And to hang the terminal until everything has finished
     wait();
 	  exit(0);
}

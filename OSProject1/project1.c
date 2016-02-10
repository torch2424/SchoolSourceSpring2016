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
     childpidRight = 0 ;

     //Print our Text Header
     printf("%-25s%-20s%-10s%-10s%-10s\n", "Level", "Procs", "Parent", "Child1", "Child 2");
     printf("%-25s%-20s%-10s%-10s%-10s\n", "No.", "ID", "ID", "ID", "ID");

     //Spacing
     printf("\n\n");

     //Loop through and create our children
     int level = 0;
     int i;
     for(i = 0; i < numLevels; i++) {

          //Create two childrens per node
           childpidLeft = fork();
           childpidRight = fork();

           if(childpidLeft == 0 || childpidRight == 0) continue;
           //Error check our children
           else if (childpidLeft == -1) {
               perror ("\n The left fork failed\n");
               exit(1);
           }
           else if (childpidRight == -1) {
               perror ("\n The right fork failed\n");
               exit(1);
           }

           //Set the level
           level = i;

           //then we need to break
            break;
        }

         //Output to the user
         printf("%-25d%-20ld%-10ld%-10ld%-10ld\n", level, (long)getpid(), (long)getppid(), (long)childpidLeft, (long)childpidRight);

    //Finish up and exit
    //No nice prompt since it messes up output
 	//printf("\nProcess Died...Thank you! Have a nice day!\n");
 	exit(0);
}

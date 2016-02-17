/**************************************************************************/
/* PROGRAM: lab3.c */
/* DESCRIPTION: This program uses exec to call */
/* various user given commands, and the command's */
/* parameters */
/**************************************************************************/
# include <stdio.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <unistd.h>
int main(int argc, char *argv[])
{

    //Check if the user used the correct input
     if (argc <= 1) {

         //Print the usage and exit
         //If wront input
         printf("\nUsage:\n");
         printf("\n %s [Program To Run] [Program's Parameters]\n", argv[0]);
         exit(1);
     }

     //Run the program and it's parameters
     //&argv is a two-dimensional array that points
     //to all of the arguments that are passed into the
     //Program we are calling
     execvp(argv[1], &argv[1]);
     perror ("exec failure");
     exit(1);
}

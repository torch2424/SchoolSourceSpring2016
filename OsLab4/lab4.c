/**************************************************************************/
/* PROGRAM: lab4.c */
/* DESCRIPTION: The parent generates a child process */
/* and then overlays it by a call to exec.*/
/* parameters */
/**************************************************************************/

//Includes
# include <stdio.h>
# include <unistd.h>

//Our main functions
int main(void)
{
    //Create an array of string numbers
     static char *mesg[] = {"0", "1", "2", "3", "4", "5", "6", "7", "8", "9"};

     //Decalre some ints
     int display(char *), i;

     //Loop 10 times, and call our display fucntion
     for (i=0; i<10; ++i) display(mesg[i]);

     //Sleep the process for two seconds
     sleep(2);
}

//Fucntiion to fork and display a message
int display(char *m)
{

    //Initialize our error message
    char err_msg[25];

    //Fork a new process
    switch (fork())
    {

        //Successful fork
         case 0:

             //Was /bin/echo, but changed for parts b) and c) of lab
             //call echo, and echo our string
             execlp("~/echo", "echo", m, (char *) NULL);

             //If echo failed call the following
             sprintf (err_msg, "%s Exec failure", m);
             perror(err_msg);

             //Was return(1), but changed for part c
             exit(1);

         //Fork failed
         case -1:
             perror ("Fork failure"); return(2);

         //Default statement
         default:
             return(0);
     }
}

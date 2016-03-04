/**************************************************************************/
/* PROGRAM: parent.c */
/* DESCRIPTION: This program create 4 child processes and //invoke the exec() system call. The exec() command calls the
child program along with 4 arguments; sleep time T,one number X, and second number Y.
/**************************************************************************/
# include <stdio.h>
# include <stdlib.h>
# include <sys/types.h>
# include <unistd.h>
#include <time.h>
int main(int argc, char *argv[])
{
     //Initialize some variables
     pid_t p;
     int n,x,y,t,i;
     char cNumber[10];
     n=4;

     if(argc != 4)
     {
    printf("\n Please enter three numbers \n");
    exit(1);
     }

     x=atoi(argv[1]);
     y=atoi(argv[2]);
     t=atoi(argv[3]);

     //Print parent's information
     printf("\nI am the parent process, the max sleep time is %d and the two numbers are %d and %d\n", t, x, y);

     //Depends on the # of child processes, execute the child      //program that many time
     for(i=0;i<n;i++) {

    sprintf(cNumber,"%d",i);

    //Different cases based on the result of the fork
    switch(p=fork())
    {
        //If fork() returns a child process then exec
        case 0:
    /*Four arguments are child3#,number1,number2,time*/
    execl("./child","child",cNumber,argv[1],argv[2],argv[3],(char *)0);
        perror("Exec failure");
        return(1);
        case -1:
        perror("Fork failure!");
        return(2);
        default:
        sleep(2);
        printf("\nForked child %d\n",p);

    }
     }
    //Wait for process to finish
    wait(p);

    //exit program
    exit(1);
}

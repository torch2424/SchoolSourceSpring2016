/**************************************************************************/
/* PROGRAM:  pipe1.c */
/*
    DESCRIPTION: This program will create a pipe
    and read or write a message, and then a forked child will read
    or write to the pipe as well

    For operating systems, Lab #8
 */
/**************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <limits.h>
#include <errno.h>

# define BUFSIZE 256

int main(int argc, char *argv[])
{
    //Intiilaze some variables
     mode_t fifo_mode = S_IRUSR | S_IWUSR;
     int fd, status, child;
     char buf[BUFSIZE];
     unsigned strsize;

     //Check our input
     if (argc !=2) {
         printf ("\n Usage: %s pipename\n", argv[0]);
         exit(1);
     }

     /* generate a named pipe with r/w for user */
     if ((mkfifo(argv[1],fifo_mode) == -1) && (errno != EEXIST)) {
         perror ("Pipe");
         exit(1);
     }

     //Fork to pipe and read/write a message, with a specified pipe name.
     //Changed for the parent to read from the child
     //Originally was child reading from the parent
     if (( child = fork()) == -1) {
         perror ("Fork");
         exit(1);
     }
     else if (child == 0) {

         printf ("Child %ld is about to open FIFO %s\n", (long) getpid(), argv[1]);

         //open the pipe
         if ((fd = open(argv[1], O_RDONLY | O_NONBLOCK)) == -1) {
             perror("Child cannot open FIFO");
             exit(1);
         }
         printf ("Child is about to read\n");
         (long) getpid();

         //Wait for the parent to write
         while ((waitpid(getppid(), &status, 0) == -1) && (errno == EINTR));
         if (read(fd, buf, BUFSIZE) <=0) {
             perror("Child read from FIFO failed\n");
             exit(1);
         }

         //Print the message
         printf ("Child %ld received: %s\n", (long)getpid(), buf);
     }

     /* parent does a read */
     else {

         //Open the pipe
         printf ("\n Parent %ld is about to open FIFO %s\n", (long)getpid(), argv[1]);
         if ((fd = open(argv[1], O_WRONLY)) == -1) {
             perror("Parent cannot open FIFO");
             exit(1);
         }

         //Write to the pipe
         sprintf (buf, "This was written by parent %ld\n", (long)getpid()); strsize = strlen(buf) + 1;
         if (write(fd, buf, strsize) != strsize) {
             printf("Parent write to FIFO failed\n");
             exit(1);
         }

         //Finish message
         printf ("Parent %ld is done\n", (long)getpid());
     }

     //Fincally exit the program
     exit(0);
}

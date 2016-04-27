/**************************************************************************/
/* PROGRAM:  project6.c */
/*
    DESCRIPTION: This program will create a pipe
    and read or write a message, and then a forked child will read
    or write to the pipe as well, depending on the user input

    For operating systems, Project #6
 */
/**************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <limits.h>
#include <errno.h>

//Declare our helper functions
void printUsage(char *programName);
void checkInput(int argc, char *argv[]);
void noNamedPipe(char* name, char* message, int f_des[2], int maxBufferSize, bool readOrWrite);
void namedRead();
void namedWrite();

int main(int argc, char *argv[])
{
    //Grab our input

    //Boolean for name or unamed pipes
    //Change our argbase accordingly
    bool namedPipe = true;
    int argBase = 1;
    if(strcmp(argv[1], "u") == 0) {

        namedPipe = false;
        ++argBase;
    }

    //Grab our pipe name if we have one
    char* pipeName;
    if(namedPipe) pipeName = argv[argBase];

    //Grab the pipe directions
    bool parentToChild = true;
    if(strcmp(argv[argBase + 1], "c") == 0) parentToChild = false;

    //Grab our message
    char* pipeMessage;
    pipeMessage = argv[argBase + 2];

    //Initialize pipe variables
    mode_t fifo_mode = S_IRUSR | S_IWUSR;
    int f_des[2];
    int maxBufferSize = 32;

    //Generate our pipe
    if(namedPipe) {

        //Generate a named pipe with r/w for user
        if ((mkfifo(pipeName, fifo_mode) == -1) && (errno != EEXIST)) {
            perror ("Could not generate pipe, exiting...");
            exit(1);
        }
    }
    else {

        //Generate nameless pipe
        if (pipe(f_des) == -1) {
            perror ("Could not generate pipe, exiting...");
            exit(2);
        }
    }

    //Fork our parent and child
    pid_t childId;

    //Fork the child and check for failure
    if((childId = fork()) == -1) {
            printf("Unable to fork child, exiting...\n");
            exit(5);
    }
    //Child fork successful, child
    else if(childId == 0) {

        //Check if we are named our unamed
        if(namedPipe) {

        }
        else {

            //Check our direction
            if(parentToChild) noNamedPipe("Child", pipeMessage, f_des, maxBufferSize, true);
            else noNamedPipe("Child", pipeMessage, f_des, maxBufferSize, false);
        }
    }
    //Parent
    else {

        //Make sure our child forked
        if(childId == -1) {
                printf("Unable to fork child, exiting...\n");
                exit(5);
        }

        //Check if we are named our unamed
        if(namedPipe) {

        }
        else {

            //Check our direction
            if(parentToChild) noNamedPipe("Parent", pipeMessage, f_des, maxBufferSize, false);
            else noNamedPipe("Parent", pipeMessage, f_des, maxBufferSize, true);
        }
    }




 //Intiilaze some variables
  mode_t fifo_mode = S_IRUSR | S_IWUSR;
  int fd, status, child;
  char buf[BUFSIZE];
  unsigned strsize;

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

//Function to check our input
void checkInput(int argc, char *argv[]) {

    //Check the number of arguments
    //Print the usage if argument amount is invalid
    //We need at least 4 arguments, since it is
    //Program name, option, number(>=1), sem value
    if (argc != 4 && argc != 5) {

        //Print Usage and exit
        printUsage(argv[0]);
    }

    //Check the pipe type
    //n for named, u for unamed
    if(strcmp(argv[1], "n") != 0 && strcmp(argv[1], "u") != 0) {

       //Print Usage and exit
       printUsage(argv[0]);
    }

    //If we have named pipe, make sure args is 5
    //Make an arg base variable we can reference to
    //To get the correct array index values
    int argBase = 1;
    if(strcmp(argv[1], "n") == 0 && argc != 4) {

        //Print Usage and exit
        printUsage(argv[0]);
    }
    else if(strcmp(argv[1], "n") == 0 && argc == 5) {

        argBase = 2;
    }

    //Check the pipe type
    //p for parent to child, c for child to parent
    if(strcmp(argv[argBase + 1], "p") != 0 && strcmp(argv[argBase + 1], "c") != 0) {

       //Print Usage and exit
       printUsage(argv[0]);
    }

    //Make sure the message is only 32 characters long
    if(sizeof(argv[argBase + 2]) / sizeof(char) > 32) {

        //Print Usage and exit
        printUsage(argv[0]);
    }
}

//Function to print usage and exit
void printUsage(char *programName) {

    //Print the usage
    printf("\n Usage: %s  [Character: pipe-type, n for named, u for unamed] [String: If pipe-type is n, enter the name of the pipe] [Character: The direction of the pipe, p for parent to child, c for child to parent] [String: message that will be transffered between child and parent. Maximum of 32 characters.]\n", programName);
    //Exit
    exit(1);
}

//Functions to help with piping
//Pass the name of piper, the pipe messages, f_des, and a bool for reading and writing
void noNamedPipe(char* name, char* message, int f_des[2], int maxBufferSize, bool readOrWrite) {

    //Check if we are reading or wiritng
    if(readOrWrite) {

        //Close the other f_des
        close(f_des[1]);

        //Read the message
        if (read(f_des[0], message, maxBufferSize) != -1) {

            printf ("Message received by %s: *%s*\n", name, message); fflush(stdout);
        }
        else {
            perror ("Could not read from the pipe, exiting...");
            exit(4);
        }
    }
    else {

        //Close the other f_des
        close(f_des[0]);

        //Write to the pipe
        if (write(f_des[1], message, strlen(message)) != -1)
        {
            printf ("Message sent by %s: [%s]\n", name, message);
            fflush(stdout);
        }
        else {
            perror ("Error writing to pipe");
            exit(5);
        }
    }
}

//Pass the name of piper, the pipe messages, f_des, and a bool for reading and writing
void namedPipe(char* name, char* message, int f_des[2], int maxBufferSize, pid_t processId, bool readOrWrite) {

}

/**************************************************************************/
/* PROGRAM: project2Child.c */
/* DESCRIPTION: This child program will perform mathematic operations  */
/* and print out the result */
/*  */
/**************************************************************************/
# include <stdio.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>
# include <time.h>   /* Needed for struct timespec */
int main(int argc, char *argv[])
{
     //Initialize some variables
     int operation;
     int argA;
     int argB;
     int sleepTime;

     //Check the number of arguments
     //Print the usage if arguments are invalid
     if (argc != 5 ||
     atoi(argv[1]) > 4 ||
     atoi(argv[1]) < 0) {

         printf("\n Usage: %s [Integer: 0 <= Child/Operation # <= 3] [Integer: Argument A] [Integer: Argument B, should be nonzero] [Integer: 0 <= Sleep Time => 50] \n", argv[0]);
         exit(1);
     }

     //Check for characters
     int count;
     for(count = 2; count < 5; count++) {

         int value;
         if(sscanf(argv[count], "%d", &value) != 1) {

             //Error
             printf("\n Usage: %s [Integer: 0 <= Child/Operation # <= 3] [Integer: Argument A] [Integer: Argument B, should be nonzero] [Integer: 0 <= Sleep Time => 50] \n", argv[0]);
             exit(1);
         }
     }

     //check sleep bounds
     if(atoi(argv[4]) < 1 ||
        atoi(argv[4]) > 50) {

         //Error
         printf("\n Usage: %s [Integer: 0 <= Child/Operation # <= 3] [Integer: Argument A] [Integer: Argument B, should be nonzero] [Integer: 0 <= Sleep Time => 50] \n", argv[0]);
         exit(1);
     }

     //Since it was successful, save our values
     operation = atoi(argv[1]);
     argA = atoi(argv[2]);
     argB = atoi(argv[3]);
     sleepTime = atoi(argv[4]);

     //Sleep for a random amount from the sleep time
     srand(time(NULL));
     int randSleep = (rand() % sleepTime) + 1;
     sleep(randSleep);

     //Perform our operation
     int result;

     //Print a new line for spacing
     printf("\n");

     if(operation == 0) {

         //Addition
        //Save the result
        result = argA + argB;

        //Print the answer
        printf("I am child number %d with PID %ld, the sum is %d", operation, (long) getpid(), result);
     }
     else if(operation == 1) {

         //Subtraction
         //save the result
         result = argA - argB;

         //Print the answer
         printf("I am child number %d with PID %ld, the difference is %d", operation, (long) getpid(), result);
     }
     else if(operation == 2) {

         //Multiplication
        //Save the result
        result = argA * argB;

        //Print the answer
        printf("I am child number %d with PID %ld, the product is %d", operation, (long) getpid(), result);
     }
     else if(operation == 3) {

         //Division
         //Check for non zero
        if(argB != 0) {

            //Get the result
            result = argA / argB;
            //Get the remainder
            int remainder = argA % argB;

            //Print the answer
            printf("I am child number %d with PID %ld, the quotient is %d, with a remainder of %d", operation, (long) getpid(), result, remainder);
        }
        else {

            //Print we coult not divide
            printf("I am child number %d with PID %ld, I could not divide by zero", operation, (long) getpid());
        }

     }
     else {
         printf("Incorrect operation number! Please refer to usage. Have a nice day!");
     }

     //Print a new line for spacing
     printf("\n");

     //Finally exit
      exit(0);
}

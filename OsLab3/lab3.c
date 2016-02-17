/**************************************************************************/
/* PROGRAM: lab3.c */
/* DESCRIPTION: This program uses exec to call */
/* various user given commands */
/**************************************************************************/
# include <stdio.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <unistd.h>
int main(int argc, char *argv[])
{
     if (argc <= 1) {

         printf("\n Usage: %s text_file\n", *argv);
         exit(1);
     }

     execvp(argv[1], &argv[1]);
     perror ("exec failure");
     exit(1);
}

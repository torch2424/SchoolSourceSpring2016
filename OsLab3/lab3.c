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
         exit(1) ;
     }

     execlp("/bin/cat", "cat", argv[1], (char *) NULL);
     perror ("exec failure");
     exit(1);
}

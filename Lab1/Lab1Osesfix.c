/****************************************************************/
/* PROGRAM NAME: lab1.c */
/* DESCRIPTION: This lab assignment introduces C syntax and use of */
/* command line arguments */
/****************************************************************/
# include <stdio.h>
# include <stdlib.h>
# include <time.h>

//argc is the number of arguments, argv is the array of arguments
int main(int argc, char *argv[])
{

	//Check and make sure we have at least two arguments
	if (argc != 2) {
		printf("%s Usage: Need filename and a single arguement that is a number of random elements to generater\n", argv[0]);
		exit(1);
	}
    else if(atoi(argv[1]) < 1) {
        printf("%s Usage: Cannot generate less than one random number\n", argv[0]);
		exit(1);
    }

    //Our array of randomly given integer arguments
	//Assignment says we need to name the array randA
	//Size shall be the number of arguments (-1 since the first argument is file name)
	//However + 3 to store the largest, smallest, and average values at the end of array
	//so, + 2
	int randA[atoi(argv[1])];

	//Create our variables to store smallest, largets, and average
	int large[2];
	int small[2];
	int average;
    int count = 0;
	int sumTotal = 0;

    //our seed
    srand(time(NULL));
    //Set the seed
    rand();

	//Start looping through and grabbing integers
	int i;
	for(i = 0; i < atoi(argv[1]); ++i) {

		//Generate a number between -100 and 100
        int ran = (rand() % 201) - 100;

        //add it to the array
        randA[i] = ran;

		//Add the input int to our sum
		sumTotal = sumTotal + ran;

        //increase our count
        count = count + 1;

		//Next check if it is the smalles or the largest
		//But automatically assign if it is the first run through
		if(i == 1) {

			//assign all of our variables to the first value
			small[0] = ran;
			large[0] = ran;
			average = ran;

            //Also assignt eh first index
            small[1] = i;
			large[1] = i;
		}
		else {

			//It is not first index so we need to compare things
			if(ran < small[0]) {
				small[0] = ran;
                small[1] = i;
			}
			else if(ran > large[0]) {
				large[0] = ran;
                large[1] = i;
			}
		}

	}

    //loop and print the array
    int j;
    for(j = 0; j < atoi(argv[1]); ++j) {
        printf("\n%i, At randA index: %i\n", randA[j], j);
    }

    //Spacing
    printf ("\n");
    printf ("\n");

	//Now we are done looping, we can calculate our true average
	average = sumTotal / count;

	//output our results
	printf("\nLargest value is: %i, At randA index: %i\n", large[0], large[1]);
	printf("\nSmallest value is: %i, At randA index: %i\n", small[0], small[1]);
	printf("\nAverage of the values is: %i", average);


	//Finish up and exit
	printf ("\n");
	printf("\nThank you! Have a nice day!\n");
	printf ("\n");
	exit(0);
}

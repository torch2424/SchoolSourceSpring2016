/****************************************************************/
/* PROGRAM NAME: lab1.c */
/* DESCRIPTION: This lab assignment introduces C syntax and use of */
/* command line arguments */
/****************************************************************/
# include <stdio.h>
# include <stdlib.h>

//argc is the number of arguments, argv is the array of arguments
int main(int argc, char *argv[])
{

	//Our array of randomly given integer arguments
	//Assignment says we need to name the array randA
	//Size shall be the number of arguments (-1 since the first argument is file name)
	//However + 3 to store the largest, smallest, and average values at the end of array
	//so, + 2
	int randA[argc + 2];

	//Check and make sure we have at least two arguments
	if (argc < 2) {
		printf("\n %s Usage: Need filename and any number of following integer arguments from -100 and 100\n", argv[0]);
		exit(1);
	}

	//Create our variables to store smallest, largets, and average
	int large;
	int small;
	int average;
	int count = 0;
	int sumTotal = 0;

	//Start looping through and grabbing integers
	int i;
	for(i = 1; i < argc; ++i) {

		//First grab the string
		int inputInt = atoi(argv[i]);

		//check if it is less than -100
		//or greater than 100
		if(inputInt < -100 ||
		inputInt > 100) {
			//Inform the user
			printf("/nSorry, only values from -100 to 100 are accepted. Continuing execution...\n");
		}
		else {

			//Add it to the array
			randA[i - 1] = inputInt;

			//increase our count
			++count;

			//Add the input int to our sum
			sumTotal = sumTotal + inputInt;

			//Next check if it is the smalles or the largest
			//But automatically assign if it is the first run through
			if(i == 1) {

				//assign all of our variables to the first value
				small = inputInt;
				large = inputInt;
				average = inputInt;
			}
			else {

				//It is not first index so we need to compare things
				if(inputInt < small) {
					small = inputInt;
				}
				else if(inputInt > large) {
					large = inputInt;
				}
			}

		}
	}

	//Now we are done looping, we can calculate our true average
	average = sumTotal / count;

	//now we need to assign our values to the end of the array
	//May have null variables to the end, but use count for indexes and we wont attempt
	//to acces those
	randA[count - 1] = large;
	randA[count] = small;
	randA[count + 1] = average;

	//output our results
	printf("\nLargest value is: %i, At randA index: %i\n", randA[count - 1], count - 1);
	printf("\nSmallest value is: %i, At randA index: %i\n", randA[count], count);
	printf("\nAverage of the values is: %i, At randA index: %i\n", randA[count + 1], count + 1);


	//Finish up and exit
	printf ("\n");
	printf("\nThank you! Have a nice day!\n");
	printf ("\n");
	exit(0);
}


import java.io.*;
import java.util.*;

public class DfsPuzzle {

    //Our application name
    private static final String appName = "Sum Checker Application";


      //Main Function
      public static void main(String[] args) {

          //Print some spacing
          System.out.println();

          //Print the welcome
          System.out.println("Welcome to the " + appName + "!");
          System.out.println();

          //Check the input
          checkArgs(args);

          //Since input is good, start searching
          System.out.println("Looking for sum...");
          System.out.println();

          //Since we have the right number of arguments,
          //run the program
          //Save our sum
          int inputSum = Integer.valueOf(args[args.length - 1]);

          //Place all of our arguments in a list
          //for checking
          ArrayList<Integer> argList = new ArrayList<Integer>();

          //Loop, until -1 since the sum
          for(int i = 0; i < args.length - 1; ++i) {

              //Simply add all to the hash set
              argList.add(Integer.valueOf(args[i]));
          }

          //Nested Loop through and check the elements
          //By adding it to every element in front of the pivot
          // -1 since we do not want to reach the last the
          // Last index with i since there will be nothing to check
          for(int i = 0; i < argList.size() - 1; ++i) {
              for(int j = i + 1; j < argList.size(); ++j) {

                  if(argList.get(i) + argList.get(j) == inputSum) {

                      //Since we only want to know if the sum exists,
                      //end here
                      System.out.println("Sum found! Sum is " +
                      Integer.toString(inputSum) + " with the arguments " +
                      Integer.toString(argList.get(i)) + ", and " +
                      Integer.toString(argList.get(j)) + ".");

                      //And exit
                      exitApp();
                  }
              }
          }

          //Since no sum was found, simply print and exit
          System.out.println("Target sum not found: " + Integer.toString(inputSum) + ".");

          //Print some spacing
          System.out.println();
      }



      //Function to check input values
      public static void checkArgs(String[] args) {

          //Check if we have enough arguments
          //We need at least three arguments
          //Two integers that can add, and equal the sum
          if(args.length < 3) {

              //Print the Usage
              System.out.println("USAGE: Insert multiple integer arguments that will compose an array. the last argument will be the sum we are searching for. Need at least 3 arguments: x, y, and the sum.");

              //And exit
              exitApp();
          }

          //Now check if all arguments are integers
          //If not, exit
          for(int i = 0; i < args.length; ++i) {

              try {
                  Integer.valueOf(args[i]);
              }
              catch(NumberFormatException e) {

                  //Print the Usage
                  System.out.println("USAGE: Insert multiple integer arguments that will compose an array. the last argument will be the sum we are searching for. Need at least 3 arguments: x, y, and the sum.");

                  //And exit
                  exitApp();
              }
          }
      }

      //Function to exit the app
      public static void exitApp() {

          //Simply print spacing and exit
          System.out.println();
          System.exit(0);
      }

}

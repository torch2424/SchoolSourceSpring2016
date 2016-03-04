
import java.io.File;
import java.io.IOException;
import javax.swing.JFileChooser;
import java.util.*;

public class ArraySum {

    //Our application name
    private static final String appName = "Integer Median Application";


      //Main Function
      public static void main(String[] args) {

          //Print some spacing
          System.out.println();

          //Check if we have enough arguments
          //We need at least three arguments
          //Two integers that can add, and equal the sum
          if(args.length < 3) {

              //Print the Usage
              System.out.println("USAGE: Insert multiple Arguments that will compose an array. the last argument will be the sum we are searching for. Need at least 3 arguments: x, y, and the sum.");

              System.exit(0);
          }

          //Since we have the right number of arguments,
          //run the program
          //Save our sum
          int inputSum = Integer.valueOf(args[args.length - 1]);

          //place all of arguments into a hash set to avoid duplicates
          HashSet<Integer> argSet = new HashSet<Integer>();

          //Loop, until -1 since the sum
          for(int i = 0; i < args.length - 1; ++i) {

              //Simply add all to the hash set
              argSet.add(Integer.valueOf(args[i]));
          }

          //Place all of our non duplicates into an array list
          //for checking
          ArrayList<Integer> argList = new ArrayList<Integer>(argSet);

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

                      System.exit(0);
                  }
              }
          }

          //Since no sum was found, simply print and exit
          System.out.println("Target sum not found: " + Integer.toString(inputSum) + ".");

          //Print some spacing
          System.out.println();
      }

}

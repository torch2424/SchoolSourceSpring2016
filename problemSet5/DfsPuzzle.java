
import java.io.*;
import java.util.*;

public class DfsPuzzle {

    //Our application name
    private static final String appName = "DFS Puzzle Solver";

    //Our borders
    public static final String fancyBorder = "******************************************";
    public static final String plainBorder = "------------------------------------------";


    //Our beginning and ending states
    //Zero is the empty spot
    //Going from left to right, top to bottom
    private static final String beginState = "283164705";
    private static final String endState = "123804765";

      //Main Function
      public static void main(String[] args) {

          //Print some spacing
          System.out.println();

          //Print the welcome
          System.out.println("Welcome to the " + appName + "!");
          System.out.println();

          //Create our puzzle
          SlidePuzzle puzzle = new SlidePuzzle(beginState, endState);

          //Print our two states
          System.out.println("Beginning State: ");
          SlidePuzzle.printState(puzzle.initialState);

          System.out.println("Goal State: ");
          SlidePuzzle.printState(puzzle.endState);


          //Inform User of starting search
          System.out.println();
          System.out.println();
          System.out.println(fancyBorder);
          System.out.println();
          System.out.println("Searching to solve the puzzle...");
          System.out.println();
          System.out.println(fancyBorder);
          System.out.println();
          System.out.println();

          //Recursively Solve the puzzle!
          ArrayList<Integer> finalTree = puzzle.solvePuzzle();

          //Print some fancy answer
          System.out.println();
          System.out.println();
          System.out.println(fancyBorder);
          System.out.println();
          if(finalTree == null) {

              //We couldnt solve the puzzle
            System.out.println("Sorry, but I could not solve the puzzle...");
            System.out.println();
          }
          else {

              //Solved the puzzle!
              System.out.println("Found the solution:");
              System.out.println();
              SlidePuzzle.printState(finalTree);


          }
          //Print some fancy answer
          System.out.println(fancyBorder);
          System.out.println();
          System.out.println();

          //Exit the app
          exitApp();
      }

      //Function to exit the app
      public static void exitApp() {

          //Simply print  goodbye,spacing, and exit
          System.out.println("Thank you for using the " + appName + "!");
          System.out.println("Have a nice day!");
          System.out.println();
          System.exit(0);
      }

}

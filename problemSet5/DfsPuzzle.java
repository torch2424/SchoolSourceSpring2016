
import java.io.*;
import java.util.*;

public class DfsPuzzle {

    //Our application name
    private static final String appName = "DFS Puzzle Solver";

    //Our beginning and ending states
    //Zero is the empty spot
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
          puzzle.printTree(puzzle.stateTree);

          System.out.println("Goal State: ");
          puzzle.printTree(puzzle.endTree);


          //Inform User of starting search
          System.out.println("Searching to solve the puzzle...");
          System.out.println();
          System.out.println();
          System.out.println();

          //Recursively Solve the puzzle!
          ArrayList<Integer> finalTree = puzzle.solvePuzzle(puzzle.stateTree, puzzle.endTree);

          if(finalTree == null) System.out.println("COULD NOT SOLVE PUZZLE");
          else {

              System.out.println("COULD SOLVE PUZZLE");

          }

      }

      //Function to exit the app
      public static void exitApp() {

          //Simply print spacing and exit
          System.out.println();
          System.exit(0);
      }

}

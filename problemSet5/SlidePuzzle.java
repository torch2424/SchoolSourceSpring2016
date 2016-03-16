import java.io.*;
import java.util.*;

public class SlidePuzzle {

    //An array of our already visited states
    private ArrayList<ArrayList<Integer>> visitedStates = new ArrayList<ArrayList<Integer>>();

    //Create our state hashmaps
    public ArrayList<Integer> stateTree = new ArrayList<Integer>();
    public ArrayList<Integer> endTree = new ArrayList<Integer>();

    //Our constructor
    public SlidePuzzle (String start, String end) {

        //Place our states into the maps
        for(int i = 0; i < 9; ++i) {

            stateTree.add(i, Character.getNumericValue(start.charAt(i)));
            endTree.add(i, Character.getNumericValue(end.charAt(i)));
        }

        //Add the beginning state to the visited states
        visitedStates.add(new ArrayList<Integer>(stateTree));
    }

    //Function to solve the puzzle
    public ArrayList<Integer> solvePuzzle (ArrayList<Integer> current, ArrayList<Integer> goal) {

        for(int j = 0; j < visitedStates.size(); ++j) {

            //get our state
            ArrayList<Integer> currentState = new ArrayList<Integer>(visitedStates.get(j));

            //Check if the goal state is the current State
            if(comparePuzzles(currentState, goal)) return currentState;

            //Print the State
            System.out.println("Next State: ");
            printTree(currentState);

            //Try to move the map
            //Find the space/zero
            for(int i = 0; i < currentState.size(); i++) {

                if(currentState.get(i) == 0) {

                    ArrayList<Integer> swapPuzzle;

                    //Add all possible swaps
                    //Up
                    if(i > 2) {
                        addState(new ArrayList<Integer>(swapIndex(new ArrayList<Integer>(currentState), i, i - 3)));
                    }
                    //Left
                    if(i != 0 &&
                    i != 3 &&
                    i != 6) {
                            addState(new ArrayList<Integer>(swapIndex(new ArrayList<Integer>(currentState), i, i - 1)));
                    }
                    //Down
                    if(i < 6) {
                        addState(new ArrayList<Integer>(swapIndex(new ArrayList<Integer>(currentState), i, i + 3)));
                    }
                    //Right
                    if(i != 2 &&
                    i != 5 &&
                    i != 8) {
                        addState(new ArrayList<Integer>(swapIndex(new ArrayList<Integer>(currentState), i, i + 1)));
                    }

                    //break from the loop
                    break;
                }
            }
        }

        //Return null since we visited all found states
        return null;
    }

    //Check if the state was already visited
    public boolean addState(ArrayList<Integer> newState) {

        for(int i = 0; i < visitedStates.size(); i++) {

            if(comparePuzzles(newState, visitedStates.get(i))) return false;

        }

        //We haven't been here, add it to the array
        visitedStates.add(new ArrayList<Integer>(newState));
        return true;
    }


    //Function to compare same sized puzzles
    public static boolean comparePuzzles(ArrayList<Integer> leftPuzzle, ArrayList<Integer> rightPuzzle) {

        //Check the contents of the states
        for(int j = 0; j < leftPuzzle.size(); j++) {

            if(leftPuzzle.get(j) != rightPuzzle.get(j)) {

                //There is a difference
                return false;
            }
        }

        //They are the same
        return true;
    }

    //Function to swap two keys in a map
    public static ArrayList<Integer> swapIndex(ArrayList<Integer> swapPuzzle, Integer firstIndex, Integer secondIndex) {

        //Create our temp key
        int tempValue = 0;

        tempValue = swapPuzzle.get(firstIndex);
        swapPuzzle.set(firstIndex, swapPuzzle.get(secondIndex));
        swapPuzzle.set(secondIndex, tempValue);

        return swapPuzzle;
    }

    //Function to print a map to a readable form
    public static void printTree(ArrayList<Integer> tree) {

        //Add some spacing
        System.out.println();

        for(int i = 0; i < tree.size(); i++) {

            //Print the value, if not zero
            if(tree.get(i) > 0) System.out.print(tree.get(i));
            else System.out.print(" ");

            //Print spacing depending on key value
            if((i + 1) % 3 != 0) System.out.print(" - ");
            else System.out.println();
        }

          //Add some spacing
          System.out.println();
    }
}

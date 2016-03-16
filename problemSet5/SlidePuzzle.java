import java.io.*;
import java.util.*;

public class SlidePuzzle {

    //An array of our states
    private ArrayList<ArrayList<Integer>> possibleStates = new ArrayList<ArrayList<Integer>>();

    //Create our state hashmaps
    public ArrayList<Integer> initialState = new ArrayList<Integer>();
    public ArrayList<Integer> endState = new ArrayList<Integer>();

    //Our constructor
    public SlidePuzzle (String start, String end) {

        //Place our states into the maps
        for(int i = 0; i < 9; ++i) {

            initialState.add(i, Character.getNumericValue(start.charAt(i)));
            endState.add(i, Character.getNumericValue(end.charAt(i)));
        }

        //Add the beginning state to the visited states
        possibleStates.add(new ArrayList<Integer>(initialState));
    }

    //Function to solve the puzzle
    //Using DFS (Depth-First Search)
    public ArrayList<Integer> solvePuzzle () {

        for(int j = 0; j < possibleStates.size(); ++j) {

            //get our state
            //Creating a new list to create a refetrence
            //Or else we would override the original
            ArrayList<Integer> currentState = new ArrayList<Integer>(possibleStates.get(j));

            //Print the State
            System.out.println(DfsPuzzle.plainBorder);
            System.out.println();
            System.out.println("Checking State: ");
            printState(currentState);
            System.out.println(DfsPuzzle.plainBorder);

            //Check if the goal state is the current State
            if(comparePuzzles(currentState, endState)) return currentState;

            //Try to move the map
            //Find the space/zero
            for(int i = 0; i < currentState.size(); i++) {

                if(currentState.get(i) == 0) {

                    ArrayList<Integer> swapPuzzle;

                    //Check for all possible position movements(Children in a tree)
                    //And add the newly swapped state to our possible states
                    //By Swapping with a new reference every time to avoid
                    //Overwriting

                    //Up
                    if(i > 2) {
                        addState(swapIndex(new ArrayList<Integer>(currentState), i, i - 3));
                    }

                    //Left
                    if(i != 0 &&
                    i != 3 &&
                    i != 6) {
                            addState(swapIndex(new ArrayList<Integer>(currentState), i, i - 1));
                    }

                    //Down
                    if(i < 6) {
                        addState(swapIndex(new ArrayList<Integer>(currentState), i, i + 3));
                    }

                    //Right
                    if(i != 2 &&
                    i != 5 &&
                    i != 8) {
                        addState(swapIndex(new ArrayList<Integer>(currentState), i, i + 1));
                    }

                    //break from the loop
                    break;
                }
            }
        }

        //End of the loop
        //Return null since we visited all found states
        return null;
    }

    //Check if the state is already in our possible states
    public boolean addState(ArrayList<Integer> newState) {

        //Loop through and compare all of our possible states
        for(int i = 0; i < possibleStates.size(); i++) {

            //The state already exists, return false
            if(comparePuzzles(newState, possibleStates.get(i))) return false;

        }

        //We haven't been here, add it to the array
        //Using new array list to avoid duplicating references
        possibleStates.add(new ArrayList<Integer>(newState));
        return true;
    }


    //Function to compare same sized puzzles
    public static boolean comparePuzzles(ArrayList<Integer> leftPuzzle, ArrayList<Integer> rightPuzzle) {

        //Check the contents of the states
        //By looping through and checking eveyr index
        for(int j = 0; j < leftPuzzle.size(); j++) {

            //There is a difference at this index
            if(leftPuzzle.get(j) != rightPuzzle.get(j)) {

                //They are not the same
                return false;
            }
        }

        //They are the same
        //Since we did not return false
        //And did not find a difference
        return true;
    }

    //Function to swap two keys in a map
    public static ArrayList<Integer> swapIndex(ArrayList<Integer> swapPuzzle, Integer firstIndex, Integer secondIndex) {

        //Create our temp key
        int tempValue = 0;

        //Swap the two keys
        tempValue = swapPuzzle.get(firstIndex);
        swapPuzzle.set(firstIndex, swapPuzzle.get(secondIndex));
        swapPuzzle.set(secondIndex, tempValue);

        //Return the swapped puzzle
        return swapPuzzle;
    }

    //Function to print a map to a readable form
    public static void printState(ArrayList<Integer> state) {

        //Add some spacing
        System.out.println();

        for(int i = 0; i < state.size(); i++) {

            //Print the value, if not zero
            if(state.get(i) > 0) System.out.print(state.get(i));
            else System.out.print(" ");

            //Print spacing depending on key value
            if((i + 1) % 3 != 0) System.out.print(" - ");
            else System.out.println();
        }

          //Add some spacing
          System.out.println();
    }
}

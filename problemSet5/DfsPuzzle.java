
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

          //Create our state hashmaps
          HashMap<Integer, String> stateMap = new HashMap<Integer, String>();
          HashMap<Integer, String> endMap = new HashMap<Integer, String>();

          //Place our states into the maps
          for(int i = 0; i < 9; ++i) {

              stateMap.put(i + 1, Character.toString(beginState.charAt(i)));
              endMap.put(i + 1, Character.toString(endState.charAt(i)));
          }

          //Print our two states
          System.out.println("Beginning State: ");
          printMap(stateMap);

          System.out.println("Goal State: ");
          printMap(endMap);


          //Inform User of starting search
          System.out.println("Searching to solve the puzzle...");
          System.out.println();
          System.out.println();
          System.out.println();

          //Recursively Solve the puzzle!
          solvePuzzle(stateMap, endMap);

          //Create our tree with our initial state
          //DfsTree puzzleTree = new DfsTree(stateMap);


      }

      //Function to print a map to a readable form
      public static void printMap(HashMap<Integer, String> map) {

          //Add some spacing
          System.out.println();

          //Create our map iterator
            Iterator iterate = map.entrySet().iterator();

            //Loop through the map
            while (iterate.hasNext()) {

                //Get our entry
                Map.Entry<Integer, String> pair = (Map.Entry <Integer, String>)iterate.next();

                //Print the value, if not zero
                if(Integer.valueOf((String) pair.getValue()) > 0) System.out.print(pair.getValue());
                else System.out.print(" ");

                //Print spacing depending on key value
                if(((Integer)pair.getKey()) % 3 != 0) System.out.print(" - ");
                else System.out.println();

                //Removed the value from the iterator
                iterate.remove(); // avoids a ConcurrentModificationException
            }

            //Add some spacing
            System.out.println();
      }

      //Function to solve the puzzle
      public static HashMap<Integer, String> solvePuzzle (HashMap<Integer, String> currentMap, HashMap<Integer, String> goalMap) {

          //Print the State
          System.out.println("Current State: ");
          printMap(currentMap);

          //Check if the goal state is the current State
          if(currentMap.equals(goalMap)) return currentMap;

          //Try to move the map
          if(moveMap(currentMap).size() > 0) {

              for(int i = 0; i < moveMap(currentMap).size(); i ++) {

                  //move the map of all of it's children
                  solvePuzzle(moveMap(currentMap).get(i));
              }
          }

          //Return null since we could not solve the puzzle
          return null;

      }

      //Function to move the tree up a state
      public static ArrayList<HashMap<Integer, String>> moveMap(HashMap<Integer, String> mapState) {

          //Create our array of states
          ArrayList<HashMap<Integer, String>> mapList = new ArrayList<HashMap<Integer, String>>();

          //Iterate through the map
            Iterator iterate = mapState.entrySet().iterator();

            //Loop through the map
            while (iterate.hasNext()) {

                //Get our entry
                Map.Entry<Integer, String> pair = (Map.Entry)iterate.next();

                //Print the value, if not zero
                if(Integer.valueOf((String) pair.getValue()) == 0) {

                    //Get the key
                    int mapKey = Integer.valueOf((Integer) pair.getKey());

                    //Add all possible swaps
                    //Up
                    if(mapKey > 3) mapList.add(swapKeys(mapState, pair.getKey(), pair.getKey() - 3));
                    //Left
                    if(mapKey != 1 &&
                    mapKey != 4 &&
                    mapKey != 7) mapList.add(swapKeys(mapState, pair.getKey(), pair.getKey() - 1));
                    //Down
                    if(mapKey < 7) mapList.add(swapKeys(mapState, pair.getKey(), pair.getKey() + 3));
                    //Right
                    if(mapKey != 3 &&
                    mapKey != 6 &&
                    mapKey != 9) mapList.add(swapKeys(mapState, pair.getKey(), pair.getKey() - 1));
                }

                //Removed the value from the iterator
                iterate.remove(); // avoids a ConcurrentModificationException
            }

            //Return the array of states
            return mapList;
      }

      //Function to swap two keys in a map
      public static HashMap<Integer, String> swapKeys(HashMap<Integer, String> swapMap, Integer firstKey, Integer secondKey) {

          //Create our temp key
          int tempValue = 0;

          tempValue = swapMap.get(firstKey);
          swapMap.put(firstKey, swapMap.get(secondKey));
          swapMap.put(secondKey, Integer.toString(tempValue));

          return swapMap;
      }

      //Function to exit the app
      public static void exitApp() {

          //Simply print spacing and exit
          System.out.println();
          System.exit(0);
      }

}

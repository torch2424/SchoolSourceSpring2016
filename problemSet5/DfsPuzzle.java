
import java.io.*;
import java.util.*;

public class DfsPuzzle {

    //Our application name
    private static final String appName = "DFS Puzzle Solver";

    //Our beginning and ending states
    //Zero is the empty spot
    private static final String beginState = "283164705";
    private static final String endState = "123804765";

    //our state hashmaps
    private static HashMap<Integer, String> stateMap = new HashMap<Integer, String>();
    private static HashMap<Integer, String> endMap = new HashMap<Integer, String>();



      //Main Function
      public static void main(String[] args) {

          //Print some spacing
          System.out.println();

          //Print the welcome
          System.out.println("Welcome to the " + appName + "!");
          System.out.println();

          //Place our states into the maps
          for(int i = 0; i < 9; ++i) {

              stateMap.put(i, Character.toString(beginState.charAt(i)));
              endMap.put(i, Character.toString(endState.charAt(i)));
          }

          //Pass our maps to our DFS tree


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

      //Function to exit the app
      public static void exitApp() {

          //Simply print spacing and exit
          System.out.println();
          System.exit(0);
      }


          //Our generic tree class
          public class DfsTree<T> {

              //Create our root node
            private Node<T> rootNode;


            //Our constructor
            public DfsTree(T treeRoot) {
                rootNode = new Node<T>();
                rootNode.state = treeRoot;
                rootNode.children = new ArrayList<Node<T>>();
            }

            //Add a node to the tree
            public boolean addNode(HashMap parent, HashMap child) {

            }

            //Find a node in the tree
            public Node findNode(HashMap<Integer, String> state, Node node) {

                //Recursively look for the state
                if(node.state.equals(state)) return node;
                else if(node.children.size() > 0) {

                    //Loop through the children and add return the search
                    for(int i = 0; i < node.children.size(); ++i) {
                        return findNode(state, node.children.get(i));
                    }
                }
                else {
                    return null;
                }
            }

            public class Node<T> {

                //Initialize our node state, parent node, and children
                private T state;
                private Node<T> parent;
                private List<Node<T>> children;
            }
        }

}

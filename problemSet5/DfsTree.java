import java.io.*;
import java.util.*;

//Our generic tree class
public class DfsTree<T> {

  //Create our root node
    private Node<T> rootNode;

    //Our constructor
    public DfsTree(T treeRoot) {
        rootNode = new Node<T>(treeRoot);
    }

    //Add a state to the tree
    public boolean addState(HashMap<Integer, String> parent, HashMap<Integer, String> child) {

        //Find the parent node
        Node parentNode = findState(parent, rootNode);

        //If we found the node, add it to it'd children
        if(parentNode != null) {

            //Add the state
            parentNode.children.add(new Node(child));
            return true;
        }
        else return false;

    }

    //Find a node in the tree
    public Node findState(HashMap<Integer, String> state, Node<T> node) {

        //Recursively look for the state
        if(node.state.equals(state)) return node;
        else if(node.children.size() > 0) {

            //Loop through the children and add return the search
            for(int i = 0; i < node.children.size(); ++i) {
                return findState(state, (Node<T>) node.children.get(i));
            }

            //Return null if we no not return above
            return null;
        }
        else return null;
    }


    //Our Node Class
    private class Node<T> {

        //Initialize our node state, parent node, and children
        private T state;
        private Node<T> parent;
        private ArrayList<Node<T>> children;

        //Node constructor
        public Node(T input) {
            state = input;
            children = new ArrayList<Node<T>>();
        }
    }
}

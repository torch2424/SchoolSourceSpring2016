
import java.io.File;
import java.io.IOException;
import javax.swing.JFileChooser;
import java.util.*;

public class MedianInteger {

    //Our application name
    private static final String appName = "Integer Median Application";


    //Main Function
      public static void main(String[] args) {

            //Our file endings
            String[] endings = {".txt"};

            //Introudce program to the user
            System.out.println("Welcome to the " + appName + " !");
            System.out.println("Please enter a ");

            //Loop through our endings
            for(int i = 0; i < endings.length; ++i) {

                //If not the last ending
                //Print with  a comma
                if(i < endings.length - 1) System.out.print(endings[i] + ", ");
                else System.out.print(endings[i] + " ");
            }

            System.out.print("file with integers!\n");

            //Get our files
            ArrayList<File> inputFiles = getFiles(true, endings);

            //Create our two heaps
            //Going to use array list, as we can keep them
            //Sorted, and acces both the tail and head
            ArrayList<Integer> minHeap = new ArrayList<>();
            ArrayList<Integer> maxHeap = new ArrayList<>();
            int median = 0;

            //Create a scanner
            Scanner scan = null;

            //Inform the user we are now using the files
            System.out.println("We will now find the median of the integer streams!");

            //Loop for all of our files
            for(int i = 0; i < inputFiles.size(); ++i) {

                //Set our file to our scanner
                try {

                    scan = new Scanner(inputFiles.get(i));

                    //Loop while the file has lines
                    while(scan.hasNextLine()) {

                        //Grab the line
                        String input = scan.nextLine();

                        //Parse the integer
                        int inputInt = Integer.valueOf(input);

                        //Add is to a heap
                        if(minHeap.size() < 1 &&
                        maxHeap.size() < 1) {

                            //Set the median to the integer
                            median = inputInt;

                            //and add it to the max heap
                            maxHeap.add(inputInt);

                        }
                        else {

                            //Add it to the corrct heap
                            if(inputInt < median) minHeap.add(inputInt);
                            else maxHeap.add(inputInt);

                            //Check that our heaps are evenly distributed
                            if(minHeap.size() <= maxHeap.size() - 2) {

                                //Add the least of the max heap to the min heap
                                minHeap.add(maxHeap.get(0));
                                maxHeap.remove(0);
                            }
                            else if(maxHeap.size() <= minHeap.size() - 2) {

                                //Add the least of the max heap to the min heap
                                maxHeap.add(minHeap.get(minHeap.size() - 1));
                                minHeap.remove(minHeap.size() - 1);
                            }

                            //Sort our heaps
                            Collections.sort(minHeap);
                            Collections.sort(maxHeap);

                            //Find our median
                            if(minHeap.size() > maxHeap.size()) median = minHeap.get(minHeap.size() - 1);
                            else if(maxHeap.size() > minHeap.size()) median = maxHeap.get(0);
                            else median = minHeap.get(minHeap.size() - 1) + maxHeap.get(0) / 2;
                        }

                        //Print to the user the median
                        System.out.println();
                        System.out.println("Input Integer: " + Integer.toString(inputInt));
                        System.out.println("Current Median: " + median);
                    }
                }
                catch(Exception e) {

                    System.out.println("Error Accessing the file...");
                }
            }

            //Finish up and exit
            scan.close();
            System.out.println("Thank you for using the " + appName + " !");

      }

      //Function to grab files
      private static ArrayList<File> getFiles(boolean multiple, String[] endings) {

    		// Open our file chooser
    		JFileChooser chooser = new JFileChooser();

            //Our array list of selected files
            ArrayList<File> files = new ArrayList<>();

    			//Set a variable for if we chose a valid file
    			boolean validFile = false;

    			//Our file we shall be choosing
    			File selectedFile = null;

                //Loop while we are selecting files
    			while(!validFile ||
                selectedFile == null ||
                multiple) {

    					if (chooser.showOpenDialog(null) == JFileChooser.APPROVE_OPTION)
    					{
    							// Get the file
    							selectedFile = chooser.getSelectedFile();

    							System.out.println("You selected the file: " + selectedFile.getName());

    							//Check if the file is the correct source code
                                //By looping through our endings
                                for(int i = 0; i < endings.length; ++i) {

                                    if(selectedFile.getName().endsWith(endings[i])) {

                                        //Add the file to our files
                                        files.add(selectedFile);

                                        //And set that we have a valid file
                                        validFile = true;

                                        //And simply break out of the loop
                                        break;
                                    }
                                    else if(i == endings.length - 1) {

                                        //Wrong file type inform the user
        								System.out.println("Wrong File type! Please select a  ");

                                        //Loop through the endings to print
                                        for(int j = 0; j < endings.length; ++j) {

                                            //If not the last ending
                                            //Print with  a comma
                                            if(j < endings.length - 1) System.out.print(endings[j] + ", ");
                                            else System.out.print(endings[j] + " file.\n");
                                        }
                                    }
                                }
    					}
    					else {

    						//They pressed cancel

                            //Check if they had files
                            if(files.size() > 0) {

                                //They want to run the program
                                //Set multiple to false
                                multiple = false;
                            }
                            else {

                                //They simply quit the app
                                System.out.println("Thank you for using the " + appName + " !");
        						//Exit the program
        						System.exit(0);
                            }
    					}
    			}

                //Finally return files
                return files;
      }

}

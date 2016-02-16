import java.io.File;
import java.io.FileWriter;
import java.io.IOException;
import java.util.Arrays;
import java.util.HashMap;
import java.util.Scanner;
import java.util.regex.Matcher;
import java.util.regex.Pattern;
import javax.swing.JFileChooser;

/**
 * @author torch2424
 *
 */
public class capitalizer {

	//Arrays of reserved words and their languages
	 static final String javaWords[] = { "abstract", "assert", "boolean",
         "break", "byte", "case", "catch", "char", "class", "const",
         "continue", "default", "do", "double", "else", "extends", "false",
         "final", "finally", "float", "for", "goto", "if", "implements",
         "import", "instanceof", "int", "interface", "long", "native",
         "new", "null", "package", "private", "protected", "public",
         "return", "short", "static", "strictfp", "super", "switch",
         "synchronized", "this", "throw", "throws", "transient", "true",
         "try", "void", "volatile", "while" };

	 static final String cWords[] = {"auto", "enum", "restrict", "unsigned", "break", "extern", "return", "void",
	 "case", "float", "short", "volatile",
	 "char", "for", "signed", "while",
	 "const", "goto", "sizeof", "_Bool",
	 "continue", "if", "static", "_Complex",
	 "default", "inline", "struct", "_Imaginary",
	 "do", "int", "switch",
	 "double", "long", "typedef",
	 "else", "register", "union"};

	static final String cppWords[] = {"and",  "double",  "not",  "this",
		"and_eq",  "dynamic_cast",  "not_eq",  "throw",
		"asm",  "else",  "operator",  "true",
		"auto",  "enum",  "or",  "try",
		"bitand",  "explicit",  "or_eq",  "typedef",
		"bitor",  "export",  "private",  "typeid",
		"bool",  "extern",  "protected",  "typename",
		"break",  "false",  "public",  "union",
		"case",  "float",  "register",  "unsigned",
		"catch",  "for",  "reinterpret_cast",  "using",
		"char",  "friend",  "return", "virtual",
		"class", "goto", "short", "void",
		"compl", "if", "signed", "volatile",
		"const", "inline", "sizeof", "wchar_t",
		"const_cast", "int", "static", "while",
		"continue", "long", "static_cast", "xor",
		"default", "mutable", "struct", "xor_eq",
		"delete", "namespace", "switch",
		"do", "new", "template"};

	static final String csWords[] = {
		"abstract", "as", "base", "bool", "break", "byte", "case",
		"catch", "char", "checked", "class", "const", "continue", "decimal",
		"default", "delegate", "do", "double", "else", "enum", "event", "explicit",
		"extern", "false", "finally", "fixed", "float", "for", "foreach", "goto",
		"if", "implicit", "in", "in", "int", "interface",
		"internal", "is", "lock", "long", "namespace", "new", "null", "object",
		"operator", "out", "out", "override", "params",
		"private", "protected", "public", "readonly", "ref", "return",
		"sbyte", "sealed", "short", "sizeof", "stackalloc", "static", "string",
		"struct", "switch", "this", "throw", "true", "try", "typeof",
		"uint", "ulong", "unchecked", "unsafe", "ushort", "using",
		"virtual", "void", "volatile", "while", "add", "alias", "ascending",
		"async", "await", "descending", "dynamic", "from", "get", "global",
		"group", "into", "join", "let", "orderby", "partial", "partial",
		"remove", "select", "set", "value", "var", "where",
		"where", "yield"};

	//Booleans for if we are in a comment block
	static boolean setComment;
	static boolean inComment;



	/**
	 * @param args
	 */
	public static void main(String[] args) {

		//Introudce program to the user
		System.out.println("Welcome to the Capitalizer Application!");
		System.out.println("Please enter a .java, .c, .cpp, or .cs file");

		// Open our file chooser
		JFileChooser chooser = new JFileChooser();

			//Set a variable for if we chose a valid file
			boolean validFile = false;

			//Our file we shall be choosing
			File selectedFile = null;

			while(!validFile || selectedFile == null) {

					if (chooser.showOpenDialog(null) == JFileChooser.APPROVE_OPTION)
					{
							// Get the file
							selectedFile = chooser.getSelectedFile();

							System.out.println("You selected the file: " + selectedFile.getName());

							//Check if the file is the correct source code
							if(!selectedFile.getName().endsWith(".java") &&
									!selectedFile.getName().endsWith(".c") &&
									!selectedFile.getName().endsWith(".cpp") &&
									!selectedFile.getName().endsWith(".cs"))
							{
								//Wrong file type inform the user
								System.out.println("Wrong File type! Please select a .java, .c, .cpp, or .cs file");
							}
							else validFile = true;
					}
					else {

						//They pressed cancel
						System.out.println("Thank you for using the Capitalizer Application!");
						//Exit the program
						System.exit(0);

					}
			}

			//Call the function to read/capitalize/and write the file
			capitalizeSource(selectedFile);

			//Thank the user
			System.out.println("Thank you for using the Capitalizer Application!");
	}

	private static void capitalizeSource(File selectedFile) {

		//They entered the correct file type
		//create a map to assign our array to
		HashMap<String, Integer> reserved = new HashMap<String, Integer>();

		//Find what file type it was and use the correct array to assign the keys of our map
		if(selectedFile.getName().endsWith(".java")) reserved = setKeys(reserved, javaWords);
		else if(selectedFile.getName().endsWith(".c")) reserved = setKeys(reserved, cWords);
		else if(selectedFile.getName().endsWith(".cpp")) reserved = setKeys(reserved, cppWords);
		else if(selectedFile.getName().endsWith(".cs")) reserved = setKeys(reserved, csWords);

		try {

			//Create a scanner and read in every line and capitalize the reserved words
			Scanner scan = new Scanner(selectedFile);

			//Create our FileWriter and print to another file
			//First create the File, using the directory the user launched the app
			File outputFile = new File(System.getProperty("user.dir") + "/capitalized.txt");
			//Delete the file so we can re-write it
			outputFile.delete();
			FileWriter writer = new FileWriter(outputFile, true);

			//Booleans for if we are in a comment block
			setComment = false;
			inComment = false;

			//loop until no more lines
			while(scan.hasNextLine()) {

				//read in the line
				String newLine = scan.nextLine();

				//Get an uncommented string
				String unCommented = unCommentString(newLine);

				if(!inComment) {

					//find if the line has any reserved words
					for(String key : reserved.keySet()) {

							//Count the number of times it occurs
							Pattern regex = Pattern.compile(key + "[//{//( ]|" + key + "$");
								Matcher m = regex.matcher(unCommented);
								int count = 0;
								while (m.find()){

								//capitalize the sub string
								unCommented = unCommented.replaceFirst(key, key.toUpperCase());

									count++;
								}

							//Increase the value of the key at that point
							reserved.put(key, reserved.get(key) + count);
					}
				}

				//Rebuild our string to be written
				//Our final string to be written
				String finalString = "";
				//the index of the uncommented string
				int unCommentedIndex = 0;
				for(int i = 0; i < newLine.length() && newLine.length() > 2 && unCommented.length() > 2; ++i) {

					//Check if uncomment has something that is uppercased that newline doesnt
					if(unCommentedIndex < unCommented.length() &&
					newLine.substring(i, i + 1).equalsIgnoreCase(unCommented.substring(unCommentedIndex, unCommentedIndex + 1))) {

						//Add the uncommented line
						finalString = finalString + unCommented.substring(unCommentedIndex, unCommentedIndex + 1);

						//Increase the uncommented index
						++unCommentedIndex;
					}
					else {

						//Add the new line
						finalString = finalString + newLine.substring(i, i + 1);
					}
				}

				//Lastly print the line back to our output
				//If final string is empty, print the newLine
				if(finalString.length() > 0) writer.write(finalString);
				else writer.write(newLine);
				writer.write(System.getProperty("line.separator"));

				//If we need to set that we are in a comment block
				//Do it now
				if(setComment) inComment = true;
			}

			//Output all of the reserved words we found
			//Output the format
			System.out.println("Capitalized words (Word, Number of occurences)");

			//Also create some counters
			int numWords = 0;
			long numOccurences = 0;
			for(String key : reserved.keySet()) {

				//Output the key and the value if the value is greater than zero
				if(reserved.get(key) > 0) {

					//Print out the word
					System.out.println(key + ":" + reserved.get(key));

					//Increase our counters
					numWords++;
					numOccurences = numOccurences + reserved.get(key);
				}
			}

			//Output our number of words and occurences
			System.out.println("Total type of words found: " + Integer.toString(numWords));
			System.out.println("Total number of words replaced: " + Long.toString(numOccurences));

			//Exit
			scan.close();
			writer.close();
			System.out.println("Output file created at: " + outputFile.getAbsolutePath());

		} catch (IOException e) {

			//scanner failed
			System.out.println("There was an error reading/writing the file...Thank you for using the Capitalizer Application!");

			//Exit the app
			System.exit(1);
		}
	}

	//Function to set our reserved words to a hash map
	private static HashMap<String, Integer> setKeys(HashMap<String, Integer> map, String[] array) {

		//Simply loop through the array and add the value to the map
		for(int i = 0; i < array.length; ++i) {

			//Add it to the map, and init at zero
			map.put(array[i], 0);
		}

		//return the map
		return map;
	}


	//Function to "Uncomment" a string
	private static String unCommentString(String commented) {

		/* Do Comment checking for \\, \*, \**, and \* here,
		Simply get a substring, or set a comment boolean
		Worst case scenario int j, \* int Hello *\ i = 0; \\int Hello Again
		So check in that order
		replaced / with \ above for this comment block*/

		//First check if we are currently in a comment
		if(inComment) {

			//Check if there is a comment block ending
			if(commented.indexOf("*/") > -1) {

				//Grab everything behind it
				commented = commented.split("\\*\\/")[commented.split("\\*\\/").length - 1];

				//And set the comment booleans to false
				setComment = false;
				inComment = false;
			}
		}

		//Loop while we find comments, and we are not in a comment
		while(!inComment &&
		(commented.indexOf("//") > -1 ||
		commented.indexOf("/*") > -1 ||
		commented.indexOf("/**") > -1 ||
		commented.indexOf("*/") > -1)) {

			//There is a comment!

			//Check if there is a comment block beginning
			//Checking for both /* and /**
			if(commented.indexOf("/*") > -1 ||
			commented.indexOf("/**") > -1) {

				//Check if it also ends on the same line
				if(commented.indexOf("*/") > -1)
				{

					//Need to check which one still
					if(commented.indexOf("/**") > -1) {

						//If it does simply pull the comments out
						if(commented.indexOf("/**") == 0 && commented.indexOf("*/") == commented.length() - 1) commented = "";
						else if(commented.indexOf("/**") == 0) commented = "" + commented.substring(commented.indexOf("*/"), commented.length());
						else if(commented.indexOf("*/") == commented.length() - 1) commented  = commented.substring(0, commented.indexOf("/**") - 1) + "";
						else commented = commented.substring(0, commented.indexOf("/**") - 1) + commented.substring(commented.indexOf("*/") + 2, commented.length());
					}
					else {

						//If it does simply pull the comments out
						if(commented.indexOf("/*") == 0 && commented.indexOf("*/") == commented.length() - 1) commented = "";
						else if(commented.indexOf("/*") == 0) commented = "" + commented.substring(commented.indexOf("*/"), commented.length());
						else if(commented.indexOf("*/") == commented.length() - 1) commented  = commented.substring(0, commented.indexOf("/*") - 1) + "";
						else commented = commented.substring(0, commented.indexOf("/*") - 1) + commented.substring(commented.indexOf("*/") + 2, commented.length());
					}

					//Dont set comment since we already solved it
				}
				//It didnt end on the same line
				else if(commented.indexOf("/**") > -1) {

					//Grab everything in front
					commented = commented.split("\\/\\*\\*")[0];

					//And trigger setting the comment block after we parse the line
					setComment = true;
				}
				else {

					//Grab everything in front
					commented = commented.split("\\/\\*")[0];

					//And trigger setting the comment block after we parse the line
					setComment = true;
				}
			}

			//Check if there is a comment block ending
			if(commented.indexOf("*/") > -1) {

				//Grab everything behind it
				if(commented.split("\\*\\/").length == 0) commented = "";
				else commented = commented.split("\\*\\/")[commented.split("\\*\\/").length - 1];

				//And set the comment booleans to false
				setComment = false;
				inComment = false;
			}


			//Check if it is a single line
			if(commented.indexOf("//") > -1) {

				//Simply make newline everything before the comment
				commented = commented.split("\\/\\/")[0];
			}
		}

		//Finally return the uncommented string
		return commented;
	}


}

#include <stdio.h>
#include <stdlib.h>

// line width as command line argument, read in input file which is also a command line argument 

/* EXAMPLE OUTPUT: 
"I am a student at MIIT CST.

EQUALS: 
I am a
student at
MIIT  CST.
*/

//We need to justify each line. Run method to justify text outside of main method ? 

//If a word in the text file is longer than the width of the lines, return error only saying that "Error. The word processor can’t display the output."

//Entry to the program 
int main(int argc, charargv[]) {

    //Ensure correct command line arguments are input 
    if (argc != 3) {
         printf("Usage: %s <line_length> <input_file.txt>\n", argv[0]);
         return 1;
    }

    // Step 1(?): Read in the text file, determine how many characters are in it. Input file is a string, which is a null terminated 1D array of char characters. 
            //a. Read in the char characters from the text file into a string variable. 

    // Example: 
        // input.txt contains: I love doing c code. 
            // Read this into string variable: char string =         

    //Step 2(?)  From here we can divide the number of characters by the line length that was input, to determine how many characters can fit per row.



    // Probably want to malloc the string becasue we will most likely want to use the array outside of a function call 

    //I think we need to create a 2D array with the given inputs. Line width represents the columns, and the input text length can represent the rows

    //command line argument "line width", so array columns are known right away, but not the rows 

    // Name of the input file 
    char *inputFileName = argv[1];

    // The length of each line (Techincally the ammount of columns in the array)
    int lineWidth = atoi(argv[2]);

    //Read in the input file 
    FILE *file = fopen(inputFileName, "r");
        if (file -- NULL) {
            printf("Failed to open input file.\n");
            return 1; 
    }

    while ()


    char **matrix = (char **) malloc()





    // A numbers of everyone. AXXXX_AXXXX_AXXX format.
    char *ANum = "A00992793_A01282281_A01357857"; 

    FILE *outputFile = fopen(ANum, "w");

    if (outputFile == NULL) {
        printf("Failed to create the output file.\n");
        return 1;
    }

    fclose(outputFile);
     return 0;
}
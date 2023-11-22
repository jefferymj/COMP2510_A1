#include <stdio.h>
#include <stdlib.h>

// Return the number of lines we need to divide the input text appropiately 
int count_lines(char *arr, int line_width, int file_size) { 
    // Holds the number of lines 
    int num_lines = 0;
    char *current_position = arr;
    
    // Loop will run while it is within the array bounds
    while (current_position < arr + file_size) {
        // Keeps track of characters counted in a line 
        int char_count = 0;
        // Marks the beginning of the line 
        char *start_line = current_position;
        
        // Loops until we reach the line width limit OR we get to the end of the array bounds (done reading in the string)
        while (char_count < line_width && current_position < arr + file_size) { 
            char_count++;
            current_position++;
        }
        
        // Checks if we reached the end of the line AND we are not in the middle of a word, dereference to get value 
        if (char_count == line_width && (*current_position != ' ' && *current_position != '-')) {
            // Backtrack to the nearest delimiter to ensure word is not divided 
            char *temp_position = current_position;
            
            // While loop will break if dereferencing temp position returns either: space, - or new line
            while (temp_position > start_line && *temp_position != ' ' && *temp_position != '-') { 
                temp_position--;
            }

            // Check temp position is not at the start of a new line, as line cannot start with a hyphen
            if (*temp_position == '-' && temp_position > start_line) {
                // Point to character after hyphen
                current_position = temp_position + 1;
            } else if (temp_position == start_line) {
                // If word is longer than  line length, print out error message and exit the program 
                printf("Error. The word processor can't display the output.\n");
                exit(1);
            } else {
                // A proper delimiter was found 
                current_position = temp_position;
            }
        }
        
        num_lines++;
        // Ensure next line starts with a word
        while (current_position < arr + file_size && *current_position == ' ') {
            current_position++;
        }
    }
    return num_lines;
}

// Divide and assign the input text into a 2D array
char** divide_input(char *arr, int line_width, int num_lines, int file_size) { 
    // Allocate memory to store an array consisting of char arrays
    char **lines = (char **)malloc(num_lines * sizeof(char*));
    
    char *current_position = arr;
    // Current row
    char **current_ptr = lines;
    
    // Ignore new line character
    if (arr[file_size - 1] == '\n') { 
       file_size--;
    }
    
    // Iterate over each line 
    for (int i = 0; i < num_lines; i++) { 
        int char_count = 0;
        // Point to first element in a row
        char *start_line = current_position;
        char *end_line;
        
        // Fill a row to maximum value 
        while (char_count < line_width && current_position < arr + file_size) { 
            char_count++;
            current_position++;
        }

        // Check if in the middle of a word at the end of a row
        if (current_position < arr + file_size && *current_position != ' ') {
            // Minus 1 to go the previous char element
            char *temp_position = current_position - 1; 
            // Backtrack through the elements
            while (temp_position > start_line && *temp_position != ' ' && *temp_position != '-') {
                temp_position--;
        }
        // If a hyphen is found, include it in the proper position
        if (*temp_position == '-') {
            current_position = temp_position + 1;
        } else {
            current_position = temp_position;
            }
        }

        end_line = current_position;
	
	// Add line_width elements to each row, ensuring the correct 2D array is created 
        *current_ptr = (char *)malloc((line_width) * sizeof(char));
        char *destination = *current_ptr;
        while (start_line < end_line) { 
            *destination++ = *start_line++;
        }
        
        // Fill the remaining elements with spaces 
        while (destination < *current_ptr + line_width) {
            *destination++ = ' ';
        }
        
        // Skip spaces to start the next line with a word
        while (current_position < arr + file_size && *current_position == ' ') {
            current_position++;
        }
        current_ptr++;
    } 
    return lines;              
}

// Justify the content of each line according to the rules
void justify_rows(char **lines, int num_lines, int line_width) {
    
    for (int i = 0; i < num_lines; i++) {
        char *start_row = lines[i];
        // Track words and char in a row
        int word_count = 0;
        int char_count = 0;
        
        
        // Count words and characters in the row
        for (int j = 0; j < line_width; j++, start_row++) {
            if (*start_row != ' ') {
                char_count++;
                // Check if char is at the start of a word 
                if (j == 0 || *(start_row - 1) == ' ') {
                    word_count++;
                }
            }
        }

        // Reset pointer to the start of the row
        start_row = lines[i];

        // Center a single word in a row
        if (word_count == 1) {
            int total_spaces = line_width - char_count;
            // Calculate correct spaces to the left
            int left_spaces = total_spaces / 2 + (total_spaces % 2); 
            // Calculate correct spaces to the right
            int right_spaces = total_spaces / 2;
            
            // Add spaces to the left
            for (int j = 0; j < left_spaces; j++) {
                printf(" ");
            }
	    // Add word to the row
            for (int j = 0; j < char_count; j++) {
                printf("%c", *start_row++);
            }
            // Add spaces to the right
            for (int j = 0; j < right_spaces; j++) {
                printf(" ");
            }
        } else {
            // Total number of spaces to fill a row
            int spaces_row = line_width - char_count;
            int spaces_inbetween = spaces_row / (word_count - 1);
            int extra_spaces = spaces_row % (word_count - 1);
            // Loop over characters in a row
            for (int j = 0; j < line_width; j++, start_row++) {
                //Print non spaces
                if (*start_row != ' ') {
                    printf("%c", *start_row);
                } else {
                    // Get the number of spaces between words 
                    for (int k = 0; k < spaces_inbetween; k++) {
                        printf(" ");
                    }
                    // Print extra spaces
                    if (extra_spaces > 0) {
                        printf(" ");
                        extra_spaces--;
                    }
                    // Skip over remaining spaces in the row
                    while (*(start_row + 1) == ' ' && j < line_width - 1) {
                        start_row++;
                        j++;
                    }
                }
            }
        }
        printf("\n");
    }
}
 
// Entry to the program 
int main(int argc, char *argv[]) {

    // Ensure correct command line arguments are input 
    if (argc != 3) {
         printf("Usage: %s <line_length> <input_file.txt>\n", argv[0]);
         return 1;
    }
    
    // The length of each line
    int line_width = atoi(argv[1]);
    
    // Name of the input file 
    char *inputFileName = argv[2];
    
    // Point to a memory address. At this point in the program, size is not known. 
    char *arr;

    // Read in the input file 
    FILE *file = fopen(inputFileName, "r");
        if (file == NULL) {
            printf("Failed to open input file.\n");
            return 1; 
    }

    // Move pointer to the end
    fseek(file, 0, SEEK_END);

    // File size can be determined as ftell returns how the size in bytes from the beginning to the end of  the file 
    int file_size = (int) ftell(file);

    // Move pointer to start so we can iterate through the text file
    fseek(file, 0, SEEK_SET);

    // Allocate memory for the input txt file
    arr = (char *)malloc((file_size) * sizeof(char));
    if (arr == NULL) {
        printf("Malloc failed ! \n");
        return 1;
    }
    
    // Write the code of the text file into the allocated memory
    fread(arr, 1, file_size, file);
    
    //Close the file 
    fclose(file);
     
    int number_of_lines = count_lines(arr, line_width, file_size);
    
    char **matrix = divide_input(arr, line_width, number_of_lines, file_size);
    
    justify_rows(matrix, number_of_lines, line_width);
    
    // Free each row in the matrix
    for (int i = 0; i < number_of_lines; i++) {
        free(matrix[i]);
    }

    // Free the matrix 
    free(matrix);

    // Free the arr
    free(arr);
    
    // A numbers of everyone. AXXXX_AXXXX_AXXX format
    char *ANum = "A00992793_A01357857_A01282281"; 

    FILE *outputFile = fopen(ANum, "w");

    if (outputFile == NULL) {
        printf("Failed to create the output file.\n");
        return 1;
    }

    fclose(outputFile);
    return 0;
}

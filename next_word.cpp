#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define MAX_WORD_LENGTH 21

// Function to skip invalid characters and return the next valid character (alphabet or dot)
char skip_non_alphabetic() {
    char c;
    while ((c = getchar()) != EOF) {
        if (isalpha(c) || c == '.') {
            return c; // Return valid character (alphabet or dot)
        }
        // Skip spaces, tabs, commas, and punctuation (treated as separators)
        if (isspace(c) || c == ',' || c == '!' || c == '?' || c == '-') {
            continue;
        }
    }
    return EOF; // End of input
}

// Function to read the next word or dot sequence
void read_next_word(char word[]) {
    char c = skip_non_alphabetic(); // Get the first valid character
    int i = 0;

    while (c != EOF && i < MAX_WORD_LENGTH - 1) {
        if (c == '.') {
            if (i == 0 || word[0] == '.') {
                // If it's the first dot or another dot, keep adding dots
                word[i++] = c;
            } else {
                // Otherwise, stop when a dot follows an alphabetic character
                ungetc(c, stdin); // Put the character back into the input stream
                break;
            }
        } else if (isalpha(c)) {
            // If it's an alphabetic character, store it in lowercase
            if (word[0] == '.'){
                ungetc(c, stdin); // Put the character back into the input
                break;
            }else{ 
                word[i++] = tolower(c);
            }
            
        } else {
            // If it's a separator, stop processing
            if (word[0] == '.'){
                c = skip_non_alphabetic();
                if(c != '.'){
                    ungetc(c, stdin); // Put the character back into the input stream
                    break;
                }else{
                    ungetc(c, stdin); // Put the character back into the input
                }
            }else{
                break;
            }
        }
        c = getchar(); // Read the next character
    }
    word[i] = '\0'; // Null-terminate the string
    if (word[2] == '.'){
        word[2] = '\0'; 
    }
}

int main() {
    char word[MAX_WORD_LENGTH];
    // Read and print words one by one until EOF
    while (1) {
        word[0] = '\0';
        read_next_word(word);
        if (word[0] != '\0') { // Only print non-empty words
            printf("Word: %s\n", word);
        } else {
            break; // End of input
        }
    }
    return 0;
}

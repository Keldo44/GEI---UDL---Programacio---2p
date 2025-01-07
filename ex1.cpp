#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define MAX_WORD_LENGTH 21
#define MAX_SPAM_WORDS 100

// Function to skip invalid characters and return the next valid character (alphabet or dot)
char skip_non_alphabetic()
{
    char c;
    while ((c = getchar()) != EOF)
    {
        if (isalpha(c) || c == '.')
        {
            return c; // Return valid character (alphabet or dot)
        }
    }
    return EOF; // End of input
}

// Function to read the next word or dot sequence
void read_next_word(char word[], bool end)
{

    word[0] = '\0';
    char c = skip_non_alphabetic(); // Get the first valid character
    int i = 0;
    int ended_word = 0;
    if (end)
    {
        ended_word == 1;
        word[1] = '\0';
    }

    while (c != EOF && i < MAX_WORD_LENGTH - 1 && ended_word != 1)
    {
        if (c == '.')
        {
            if (i == 0 || word[0] == '.')
            {
                word[i] = c;
                i++;
                if (word[1] == '.')
                {
                    ended_word = 1;
                }
            }
            else
            {
                // Otherwise, stop when a dot follows an alphabetic character
                ungetc(c, stdin); // Put the character back into the input stream
                ended_word = 1;
            }
        }
        else if (isalpha(c))
        {
            // If it's an alphabetic character, store it in lowercase
            if (word[0] == '.')
            {
                ungetc(c, stdin); // Put the character back into the input
                ended_word = 1;
            }
            else
            {
                word[i++] = tolower(c);
            }
        }
        else
        {
            // If it's a separator, stop processing
            if (word[0] == '.')
            {
                c = skip_non_alphabetic();
                if (c != '.')
                {
                    ungetc(c, stdin); // Put the character back into the input stream
                    ended_word = 1;
                }
            }
            else
            {
                ended_word = 1;
            }
        }
        c = getchar(); // Read the next character
    }
    if (!end)
    {
        ungetc(c, stdin); // Put the character back into the input
        word[i] = '\0';   // Null-terminate the string
        if (word[2] == '.')
        {
            word[2] = '\0';
        }
    }
}

void init_word_list(char list[MAX_SPAM_WORDS][MAX_WORD_LENGTH + 1])
{
    for (int i = 0; i < MAX_SPAM_WORDS; i++)
    {
        list[i][0] = '\0';
    }
}

int fill_spam_list(char list[MAX_SPAM_WORDS][MAX_WORD_LENGTH + 1], char word[MAX_WORD_LENGTH], int &word_count)
{
    bool dot_found = false;
    while (!dot_found)
    {
        read_next_word(word, false);
        if (strcmp(".", word) == 0)
        {
            dot_found = true;
        }
        else
        {
            // Check if the word is already in the list
            int is_duplicate = 0;
            for (int j = 0; j < word_count; j++)
            {
                if (strcmp(list[j], word) == 0)
                {
                    is_duplicate = 1;
                }
            }

            // If the word is not a duplicate, add it to the list
            if (!is_duplicate)
            {
                strcpy(list[word_count++], word);
                if (word_count == MAX_SPAM_WORDS)
                {
                    printf("Spam word list is full. Aborting...\n");
                    return 2;
                }
            }
        }
    }
    return 0;
}

void count_message_spam_words(char list[MAX_SPAM_WORDS][MAX_WORD_LENGTH + 1], char word[MAX_WORD_LENGTH], int counts[MAX_SPAM_WORDS], int word_count)
{
    bool doble_dot_found = false;
    while (!doble_dot_found)
    {
        read_next_word(word, false);
        if (strcmp("..", word) == 0)
        {
            doble_dot_found = true;
        }
        else
        {
            // compare word with every word in list and count it in counts
            for (int i = 0; i < word_count; i++)
            {
                if (strcmp(word, list[i]) == 0)
                {
                    counts[i]++;
                }
            }
        }
    }
}

void print_results(char list[MAX_SPAM_WORDS][MAX_WORD_LENGTH + 1], int counts[MAX_SPAM_WORDS], int word_count)
{
    printf("Introdueix les paraules a identificar:\n");
    printf("Introdueix el text acabat en doble punt (..):\n");
    printf("Relacio de paraules buscades:\n");
    int spamed_words = 0;
    // for each word on the list see if had appeared twce or more
    for (int i = 0; i < word_count; i++)
    {
        // desitred output
        // La paraula "qwert" apareix 0 vegada/es
        printf("La paraula \"%s\" apareix %d vegada/es\n", list[i], counts[i]);
        if (counts[i] >= 2)
        {
            spamed_words++;
        }
    }

    printf("Resultat:\n");
    printf("Rati: paraules amb 2 o mes aparicions / total de paraules = %d / %d = %.3f\n", spamed_words, word_count, (float)spamed_words / word_count);
    if (spamed_words >= (word_count / 2))
    {
        printf("El missatge es SPAM!\n");
    }
    else
    {
        printf("El missatge no es SPAM.\n");
    }
}

int main()
{
    char word[MAX_WORD_LENGTH];
    char words[MAX_SPAM_WORDS][MAX_WORD_LENGTH + 1];
    int counts[MAX_SPAM_WORDS] = {0};
    int word_count = 0;
    bool end = false;

    init_word_list(words);
    if (fill_spam_list(words, word, word_count) == 2)
    {
        return 0;
    }
    count_message_spam_words(words, word, counts, word_count);
    print_results(words, counts, word_count);
    return 0;
}

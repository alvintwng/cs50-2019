// Implements a dictionary's functionality
/*
# load
* for every dictionary word, iterate through the trie
* each element in children corresponds to a different letter
* check the value at childen[i]
* * if NULL, malloc a new node, have children[i] point to it
* * if not NULL, move to new node and continue
* if at end of word, set is_word to true

each word will contain only lowercase alphabetical characters and possibly apostrophes,
*/

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h> // strlen
#include "dictionary.h"

// Default dictionary
#define DICTIONARY "dictionaries/medium"

// Represents number of children for each node in a trie
#define N 27 // 26 letters + apostrophes ??

// Represents a node in a trie
typedef struct node
{
    bool is_word;
    struct node *children[N];
}
node;

// Represents a trie
node *root;

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    // TODO
    //return false;
    printf(" >>>>> unloading >>>>> \n");
    int test = 0; // for testing

    int a = 0;
    node *ptr = root;
    node *t;

    while (a < 27)
    {
        //printf("%i ", a);
        test++ ; if (test >300) break;  // ******

        if (ptr -> children[a] != NULL)
        {
            t = ptr;
                //printf("%i t:", ptr->is_word); for (int z = 0; z < N; z++) // 0 is false**** my test
                //{ if (ptr->children[z]) printf("%c ", 97+z); else printf(". ");  } printf("\n");

            ptr = ptr -> children[a];
                printf("%i p:", ptr->is_word); for (int z = 0; z < N; z++) // 0 is false**** my test
                { if (ptr->children[z]) printf("%c ", 97+z); else printf(". ");  } printf("\n");

            if (ptr->is_word == false)
            {printf("break if \n"); ptr = t;}

            a = 0;

            //printf("\n");
        }
        else
        { a ++;
            /* if (a > 26)
            {
                a = 0;
                printf("\n b:"); for (int z = 0; z < N; z++) // ********* .  my test
                { if (ptr->children[z]) printf("%c ", 97+z); else printf(". ");  } printf("\n");

                free (ptr);
                ptr = t;

                //break;
            }*/
        }
    }

    return false;
}
/*
           //printf("not null ");
            node *t = ptr -> children[a];
            if (t -> is_word == true)
            {
           //printf("not null ");
            node *t = ptr -> children[a];
            if (t -> is_word == true)
            {
printf("lvl? "); for (int z = 0; z < N; z++) // ********* .  my test
                { if (ptr->children[z]) printf("%c ", 97+z); else printf(". ");  } printf("\n");
*/
// Loads dictionary into memory, returning true if successful else false
/*
* for every dictionary word, iterate through the trie
* each element in children corresponds to a different letter
* check the value at childen[i]
* * if NULL, malloc a new node, have children[i] point to it
* * if not NULL, move to new node and continue
* if at end of word, set is_word to true
*/
bool load(const char *dictionary)
{
    // Initialize trie
    root = malloc(sizeof(node));
    if (root == NULL)
    {
        return false;
    }
    root->is_word = false;
    for (int i = 0; i < N; i++)
    {
        root->children[i] = NULL;
    }


    //printf("%i r:", root->is_word); for (int z = 0; z < N; z++) // 0 is false**** my test
    //{ if (root->children[z]) printf("%c ", 97+z); else printf(". ");  } printf("\n");

    // Open dictionary
    FILE *file = fopen(dictionary, "r");
    if (file == NULL)
    {
        unload();
        return false;
    }

    // Buffer for a word
    char word[LENGTH + 1];

    // Insert words into trie
    while (fscanf(file, "%s", word) != EOF)
    {
        printf("word: %s: \n", word); // ****

        node *ptr = root;
        for ( int i = 0, l = strlen(word); i<l; i++)
        {
            // n - 97 integer of alphabet, which coressponding to children[n]
            int alpha = (int)word[i] - 97;
            if (alpha == -58) { alpha = 26;} //  apostrophes, 39,

            // Allocate space for new node
            node *n = malloc(sizeof(node));
            if (!n) {return 1; }

            // Add alpha to list
            n->is_word = false;
            n->children[alpha] = NULL;

            if (!ptr->children[alpha])
            {
                //ptr->is_word = true; // set this pointer to true (1) for every node reached
                ptr->children[alpha] = n;
                //printf("B");
                //break;
            }

            printf("%i t:", ptr->is_word); for (int z = 0; z < N; z++) // 0 is false**** my test
            { if (ptr->children[z]) printf("%c ", 97+z); else printf(". ");  } printf("\n");

            ptr = ptr->children[alpha]; // next ptr
            //printf("%i p:", ptr->is_word); for (int z = 0; z < N; z++) // 0 is false**** my test
            //{ if (ptr->children[z]) printf("%c ", 97+z); else printf(". ");  } printf("\n");
        }

        // if at end of word, set is_word to true
        ptr->is_word = true;
        printf("%i e:", ptr->is_word); for (int z = 0; z < N; z++) // 0 is false**** my test
        { if (ptr->children[z]) printf("%c ", 97+z); else printf(". ");  } printf("\n");
    }

    /*/ Print numbers
    printf("\n");
    for (node *ptr = numbers; ptr != NULL; ptr = ptr->next)
    {
        printf("%i\n", ptr->number);
    }
    */

    // Close dictionary
    fclose(file);

    // Indicate success
    return true;
}



int main(void)
{
    bool loaded = load(DICTIONARY);
    //bool unloaded = unload();
    printf("so far so good!\n");
}

/*
int main(void)
{
    // Memory for numbers
    node *numbers = NULL;

    // Prompt for numbers (until EOF)
    while (true)
    {
        // Prompt for number
        int number = get_int("number: ");

        // Check for EOF
        if (number == INT_MAX)
        {
            break;
        }

        // Allocate space for number
        node *n = malloc(sizeof(node));
        if (!n)
        {
            return 1;
        }

        // Add number to list
        n->number = number;
        n->next = NULL;
        if (numbers)
        {
            for (node *ptr = numbers; ptr != NULL; ptr = ptr->next)
            {
                if (!ptr->next)
                {
                    ptr->next = n;
                    break;
                }
            }
        }
        else
        {
            numbers = n;
        }
    }

    // Print numbers
    printf("\n");
    for (node *ptr = numbers; ptr != NULL; ptr = ptr->next)
    {
        printf("%i\n", ptr->number);
    }

    // Free memory
    node *ptr = numbers;
    while (ptr != NULL)
    {
        node *next = ptr->next;
        free(ptr);
        ptr = next;
    }
}

*/
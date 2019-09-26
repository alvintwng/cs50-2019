// status: copied node by created temp for main

// scan.c Sep23,2019
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h> // for strlen
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

// my prototype
bool scanline(int sc_low, int sc_max);

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    //bool scanning;
    bool scanning = scanline(0,50);

    node *ml[46];           // memorise the address at this level
    int ma[46];             // memorise the alphabetic of that level

    node *ptr = root;       // copy pointer

    int mc = 0;             // levelth
    int a = 0;              // alpha position

    while (a < 27)
    {
        if (ptr->children[a] != NULL)
        {                   //printf("w lvl %i %c\n", mc,  97+a);// testing *
            ml[mc] = ptr;   // save the pointer at mc level
            ma[mc] = a;     // save the alpha position at mc level
                                                //printf("m%i ", mc);
            // point to the next children
            ptr = ptr->children[a]; //same as ptr = ml[mc]->children[ma[mc]];
            mc++;           // next deeper level
            a=0;            // start to scan at alpha 0
        }
        else
        {
            a++;                                // if the children null, move to next alpha

            while (a >= 27)
            {                                   //printf("N lvl %i %c\n", mc,  97+a); // testing *
                node *temp = ptr;
                mc = mc -1;                     // move back to the previous level
                if (mc < 0) { break; }          // if already at root level, break

                // copy pointer and alpha to pointer
                ptr = ml[mc];                   //printf("ml[%i]  |  ", mc); //previous , t
                ptr->children[ma[mc]] = NULL;   //printf("children[ma[%i] %c = null |  ", mc, ma[mc]+97 );

                if (temp != NULL)
                                                //printf("free ml[%i + 1] \n",mc);

                { free (temp); }

                a = ma[mc]+1;   // if a is 26, loop back
            }
        }
    }

    //return n;
    // for testing
    //printf("%i N:", ptr->is_word); for (int z = 0; z < N; z++) // 0 is false**** my test
    //{ if (ptr->children[z]) printf("%c ", 97+z); else printf(". ");  } printf("\n");

    scanning = scanline(0,50);

    return false;
    // no valgrind error ****/

}

/**** cat only *******
bool unload(void)
{
    bool scanning;          // bool scanning = scanline(0,50);

    node *ml[46];           // memorise the address at this level
    int   ma[46];             // memorise the alphabetic of that level
    int   mc = 0;             // levelth
    int    a = 0;              // alpha position


    node *ptr = root;           ml[0] = ptr; ma[0] = 2 ;
    ptr = ptr->children[ma[0]]; ml[1] = ptr; ma[1] = 0 ;  // found  'c'
    ptr = ptr->children[ma[1]]; ml[2] = ptr; ma[2] = 19; // found 'a'
    ptr = ptr->children[ma[2]]; ml[3] = ptr; ma[3] = 4 ; // found 't'
    ptr = ptr->children[ma[3]]; // ml[4] = ptr; // 'e'

    scanning = scanline(0,50);
    //FREE MEMORY  ptr = previous;
    ptr = ml[2]; ptr->children[ma[2]] = NULL; free (ml[3]);
    ptr = ml[1]; ptr->children[ma[1]] = NULL; free (ml[2]);
    ptr = ml[0]; ptr->children[ma[0]] = NULL; free (ml[1]); //bool

    scanning = scanline(0,50);

    return false;
    // no valgrind error
}    ******/

int main(void)
{

    char *word = "catch";
    node *l[46];

    root = malloc(sizeof(node)); if (root == NULL) {return false;}
    root->is_word = false;for (int i = 0; i < N; i++) { root->children[i] = NULL; }

    node *ptr = root;
    ptr->is_word = false;
    l[0] = ptr;


    node *temp = malloc(sizeof(node));
    *temp = *root;
    //free (temp);

    l[1] = malloc(sizeof(node));
    * l[1] = * temp;
    ptr->children[word[0]-97] = l[1]; // l[0]->children[2] 'c' // 27 error on scanning
                //ptr->children[2] = NULL; free (l[1]); bool scanning = scanline(0,50); // zero error here
    ptr = ptr->children[word[0]-97];
                //ptr = l[0]; ptr->children[2] = NULL; free (l[1]); bool scanning = scanline(0,50);// zero error here

    l[2] = malloc(sizeof(node));
    * l[2] = * temp;
                //free (l[2]);ptr = l[0]; ptr->children[2] = NULL; free (l[1]); bool scanning = scanline(0,50);// zero error here
    ptr->children[word[1]-97] = l[2]; // l[1]->children[0] 'a'
    ptr = ptr->children[word[1]-97];

    l[3] = malloc(sizeof(node));
    * l[3] = * temp;
    ptr->children[word[2]-97] = l[3]; // l[1]->children[0] 'e'
    ptr = ptr->children[word[2]-97];

    free (temp);

    /****************
    //FREE MEMORY  ptr = previous;
    ptr = l[2]; ptr->children[word[2]-97] = NULL;free (l[3]);
    ptr = l[1]; ptr->children[word[1]-97] = NULL;free (l[2]);
    ptr = l[0]; ptr->children[word[0]-97] = NULL; free (l[1]); bool scanning = scanline(0,50);
    // YES zero error
    ****************/

    /***********

    node *ml[46];           // memorise the address at this level
    int ma[46];             // memorise the alphabetic of that level

    node *T = root;
    ml[0] = T; ma[0] = 2 ; T = T->children[ma[0]]; // 'c'
    ml[1] = T; ma[1] = 0 ; T = T->children[ma[1]]; // 'a'
    ml[2] = T; ma[2] = 19; T = T->children[ma[2]]; // 't'
    ml[3] = T; ma[3] = 4 ; T = T->children[ma[3]]; // 'e'
    ml[4] = T;

    //FREE MEMORY  ptr = previous;
    ptr = ml[2]; ptr->children[ma[2]] = NULL;free (ml[3]);
    ptr = ml[1]; ptr->children[ma[1]] = NULL;free (ml[2]);
    ptr = ml[0]; ptr->children[ma[0]] = NULL; free (ml[1]); bool scanning = scanline(0,50);

    ******/


    l[4] = malloc(sizeof(node));
    l[4]->is_word = false;for (int i = 0; i < N; i++) { l[4]->children[i] = NULL; }
    ptr->children[word[3]-97] = l[4]; // 'c'
    ptr = ptr->children[word[3]-97];

    l[5] = malloc(sizeof(node));
    l[5]->is_word = false;for (int i = 0; i < N; i++) { l[5]->children[i] = NULL; }
    ptr->children[word[4]-97] = l[5]; // 'h'
    ptr = ptr->children[word[4]-97];

    bool unloaded = unload();
    //bool scanning = scanline(0,50);
}
/*
            Allocate space for new node
            node *n = malloc(sizeof(node));
            n->is_word = false;
            n->children[alpha] = NULL;
            ptr->children[alpha] = n;
            ptr = ptr->children[alpha]; // next ptr

    printf("%i r:", root->is_word); for (int z = 0; z < N; z++) // 0 is false**** my test
    { if (root->children[z]) printf("%c ", 97+z); else printf(". ");  } printf("\n");
*/

// Scan print of node from root to bottom, only for debugging
bool scanline(int sc_low, int sc_max)
{
    if (root == NULL) return false;
    printf("scanline sc _ level alpha is_word: children + alpha\n");
    int sc = 0; // scanline count.. can adjust sc_low & sc_max

    node *ml[46];           // memorise the address at this level
    int ma[46];             // memorise the alphabetic of that level

    node *ptr = root;       // copy pointer

    int mc = 0;             // levelth
    int a = 0;              // alpha position
    while (a < 27)
    {
        if (ptr->children[a] != NULL)
        {
            if (sc >= sc_low)
            {
                printf("%i _%2i %c %i: ",sc,mc,97+a,ptr->is_word);
                for (int z = 0; z < N; z++) // 0 is false**** my test
                { if (ptr->children[z]) printf("%c ", 97+z); else printf(". "); } printf("\n");
            }
            sc++; if (sc>sc_max ) {printf(" exit sc_max = %i\n", sc_max);return false; }

            ml[mc] = ptr;   // save the pointer at mc level
            ma[mc] = a;     // save the alpha position at mc level

            // point to the next children
            ptr = ptr->children[a]; //same as ptr = ml[mc]->children[ma[mc]];
            mc++;           // next deeper level
            a=0;            // start to scan at alpha 0
        }
        else
        {
            // if the children null, move to next alpha
            a++;
            while (a >= 27)
            {
                mc = mc -1;                 // move back to the previous level
                if (mc < 0)                 // if already at root level, break
                {
                    break;
                }
                ptr = ml[mc];   // copy pointer and alpha to pointer
                a = ma[mc]+1;   // if a is 26, loop back
            }
        }
    }
    return true;
}


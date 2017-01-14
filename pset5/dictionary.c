/**
 * dictionary.c
 *
 * Computer Science 50
 * Problem Set 5
 *
 * Implements a dictionary's functionality.
 */

#include <stdbool.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdio.h>
#include "dictionary.h"
#include <string.h>

typedef struct node
{
    bool is_word;
    struct node* subNode[27];
}
node;

node* root;
unsigned int dicSize = 0;

void freenode (node* curNode)
{
    for (int i=0;i<27;i++)
    {
        if (curNode->subNode[i] != NULL)
        freenode (curNode->subNode[i]);
    }
    
    free(curNode);
}


/**
 * Returns true if word is in dictionary else false.----------------------------------------------------------------------------
 */
bool check(const char* word)
{
    // TODO--Returns true if word is in dictionary else false
    int wordLen = strlen(word);
    struct node* curNode = root;
    
    for (int i = 0; i < wordLen; i++)
    {
        int c = tolower(word[i]);

        // assign value for letter
            if (c == '\'')
                c = 26;
            else
                c -= 'a';
        //check for letter and go to letter
        if (curNode->subNode[c] == NULL)
            return false;
        else
            curNode=curNode->subNode[c];

    }
   
   if (curNode->is_word)
        return true;
            
            
   return false; 
}

/**
 * Loads dictionary into memory.  Returns true if successful else false.---------------------------------------------------------------------------
 */
bool load(const char* dictionary)
{
    root = calloc(1, sizeof(node));
    
    // TODO
    // try to open dicitonary
    FILE* fp = fopen(dictionary, "r");
    if (fp == NULL)
        return false;
    
    //prepare to load
     struct node* curNode;
     root->is_word = false;
     int c = 0;
      // read each word in dictionary
    
    for (c = fgetc(fp); c != EOF; c = fgetc(fp))
    {
        // return to root node
        curNode = root;
        
        for (; c != '\n'; c = fgetc(fp))
        {
            // assign value for letter
            if (c == '\'')
                c = 26;
            else
                c -= 'a';
    
            // if no node, create node for letter
            if (curNode->subNode[c] == NULL)
                curNode->subNode[c] = calloc(1, sizeof(node));
            //point root to new node
            curNode=curNode->subNode[c];
        }

        // make last node's "isword" TRUE
        curNode->is_word = true;
        dicSize++; // would that it were so simple
    }
    
    fclose(fp);
    if (c == EOF)
        return true;
    else
        return false;

}

/**
 * Returns number of words in dictionary if loaded else 0 if not yet loaded.------------------------------------------
 */
unsigned int size(void)
{
    // TODO
    return dicSize;
}

/**
 * Unloads dictionary from memory.  Returns true if successful else false.
 */
bool unload(void)
{
    // TODO
    for (int i=0;i<27;i++)
    {
        if (root->subNode[i] != NULL)
        freenode (root->subNode[i]);
    }
    
    free(root);
    return true;
}


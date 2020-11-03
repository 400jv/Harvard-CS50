// Implements a dictionary's functionality
#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Dictionary is loaded
bool dictionaryLoad = false;

// Number of word
int wordCount = 0;

// Number of buckets in hash table
const unsigned int N = 1;

// Hash table
node *table[N];

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    // TODO
    int hashValue = hash(word);

    for (node *i = table[hashValue]; i != NULL; i = i->next)
    {
        if (strcasecmp(word, i->word) == 0) return true;
    }

    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // TODO
    int hashValue = 0;
    for (int i = 0; word[i] != '\0'; i++)
    {
        hashValue += tolower(word[i]);
    }

    return hashValue % N;
}

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    // TODO
    FILE *dictionaryFile = fopen(dictionary, "r");
    if (!dictionaryFile) return false;

    char word[LENGTH +1];

    for (int i = 0; i < N; i++)
    {
        table[i] = NULL;
    }


    while(fscanf(dictionaryFile, "%s", word) != EOF)
    {
        node *newNode = malloc(sizeof(node));
        if (!newNode) return false;

        strcpy(newNode->word, word);

        int hashValue = hash(word);

        if (table[hashValue] == NULL)
        {
            newNode->next = NULL;
            table[hashValue] = newNode;
        }
        else
        {
            newNode->next = table[hashValue];
            table[hashValue] = newNode;
        }

        wordCount++;
    }

    fclose(dictionaryFile);
    return true;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    return wordCount;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    // TODO
    for (int i = 0; i < N; i++)
    {
        node *cursor = table[i];

        while (cursor != NULL) {
            node *tmp = cursor;
            cursor = cursor->next;

            free(tmp);
        }

        table[i] = NULL;
    }

    return true;
}

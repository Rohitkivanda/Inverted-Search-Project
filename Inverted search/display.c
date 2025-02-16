#include "main.h"

void display_database(mainnode **hash_t)
{
    mainnode *temp;
    printf("Index   Word    Filecount       FileName    WordCount\n");
    
    // Loop through each index of the hash table
    for (int i = 0; i < 27; i++)
    {
        if (hash_t[i] != NULL)
        {
            temp = hash_t[i];
            // Traverse the linked list at this index
            while (temp)
            {
                printf("%d\t%s\t%d\t", i, temp->word, temp->filecount);
                
                // Traverse the subnode list for each file containing the word
                subnode *s = temp->subnode;
                while (s)
                {
                    printf("\t%s\t%d\t", s->filename, s->wordcount);
                    s = s->subnode; // Move to the next subnode
                }
                printf("\n"); 
                temp = temp->mainnode; // Move to the next main node
            }
        }
    }
}

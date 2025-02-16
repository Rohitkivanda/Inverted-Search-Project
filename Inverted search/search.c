#include "main.h"

int search_database(mainnode **hash_t)
{
    char word_search[50];
    printf("Enter a word: ");
    scanf("%s", word_search);

    int index = tolower(word_search[0]) % 97;
    mainnode *main = hash_t[index];

    // Check if there are any entries at the calculated index
    if (main == NULL)
    {
        printf("Word %s not found\n", word_search);
        return DATA_NOT_FOUND;
    }

    // Traverse the linked list of main nodes at this index
    while (main)
    {
        if (!strcmp(main->word, word_search))
        {
            subnode *sub = main->subnode;
            printf("Word %s is present in :\n", word_search);

            // Traverse the subnode list to display file names and word counts
            while (sub)
            {
                printf("In %s for %d times\n", sub->filename, sub->wordcount);
                sub = sub->subnode; // Move to the next subnode
            }
            return SUCCESS;
        }
        main = main->mainnode; // Move to the next main node
    }

    printf("Word %s is not found\n", word_search);
    return DATA_NOT_FOUND;
}

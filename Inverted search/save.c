#include "main.h"

int save_database(mainnode **hash_t)
{
    char f_name[50];
    printf("Enter file name :");
    scanf("%s", f_name);

    // Open file in write mode
    FILE *fptr = fopen(f_name, "w");
    if (!fptr)
    {
        // Error if file cannot be opened
        printf("ERROR: opening file\n");
        return FAILURE;
    }

    // Check if the file name has .txt extension
    if (!strstr(f_name, ".txt"))
    {
        printf("ERROR: Please include .txt extension\n");
        return FAILURE;
    }

    // Iterate through each index in the hash table
    for (int i = 0; i < 27; i++)
    {
        mainnode *temp = hash_t[i];
        // Traverse the main nodes at this index
        while (temp)
        {
            fprintf(fptr, "#%d;%s;%d;", i, temp->word, temp->filecount);
            
            // Traverse and write subnode data
            subnode *temp_subnode = temp->subnode;
            while (temp_subnode)
            {
                fprintf(fptr, "%s;%d;", temp_subnode->filename, temp_subnode->wordcount);
                temp_subnode = temp_subnode->subnode; // Move to next subnode
            }
            fprintf(fptr, "#\n"); 
            temp = temp->mainnode; // Move to next main node
        } 
    }
    fclose(fptr); 
    return SUCCESS;
}

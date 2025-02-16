#include "main.h"

int create_database(mainnode **hash_t, Slist *filename_head)
{
    Slist *temp = filename_head;
    int index = 0;

    while (temp)
    {
        // Check if the filename is already present in the hash table
        int file_found = 0;
        for (int i = 0; i < 27; i++)
        {
            mainnode *m = hash_t[i];
            while (m)
            {
                subnode *s = m -> subnode;
                while (s)
                {
                    if (strcmp(s -> filename, temp -> filename) == 0)
                    {
                        file_found = 1;
                        break;
                    }
                    s = s -> subnode;
                }
                if (file_found)
                    break;
                m = m -> mainnode;
            }
            if (file_found)
                break;
        }

        if (file_found)
        {
            printf("Error: Duplicate filename '%s'. Skipping...\n", temp -> filename);
            temp = temp -> link;
            continue;
        }

        FILE *fptr = fopen(temp -> filename, "r");
        if (!fptr)
        {
            fclose(fptr);
            return FAILURE;
        }

        char word[50];
        while (fscanf(fptr, "%s", word) != EOF)
        {
            index = tolower(word[0]) % 97;
            if (index < 0 || index > 25)
                index = 26;

            mainnode *m = hash_t[index];
            mainnode *prev = NULL;
            int word_found = 0;

            // Traverse the list at this index to find the word
            while (m)
            {
                if (strcmp(m -> word, word) == 0)
                {
                    subnode *s = m -> subnode;
                    int sub_file_found = 0;

                    // Traverse through subnodes to check if filename exists
                    while (s)
                    {
                        if (strcmp(s -> filename, temp -> filename) == 0)
                        {
                            s -> wordcount++;
                            sub_file_found = 1;
                            break;
                        }
                        s = s -> subnode;
                    }

                    if (!sub_file_found)
                    {
                        subnode *new_subnode = malloc(sizeof(subnode));
                        new_subnode -> wordcount = 1;
                        new_subnode -> filename = malloc(strlen(temp -> filename) + 1);
                        strcpy(new_subnode -> filename, temp -> filename);
                        new_subnode -> subnode = m -> subnode;
                        m -> subnode = new_subnode;
                        m -> filecount++;
                    }
                    word_found = 1;
                    break;
                }
                prev = m;
                m = m -> mainnode;
            }

            if (!word_found)
            {
                mainnode *new_main = malloc(sizeof(mainnode));
                subnode *new_sub = malloc(sizeof(subnode));

                new_main -> word = malloc(strlen(word) + 1);
                strcpy(new_main -> word, word);
                new_main -> filecount = 1;
                new_main -> subnode = new_sub;
                new_main -> mainnode = NULL;

                new_sub -> wordcount = 1;
                new_sub -> filename = malloc(strlen(temp -> filename) + 1);
                strcpy(new_sub -> filename, temp -> filename);
                new_sub -> subnode = NULL;

                if (prev)
                    prev -> mainnode = new_main;
                else
                    hash_t[index] = new_main;
            }
        }
        fclose(fptr);
        temp = temp -> link;
    }
    return SUCCESS;
}
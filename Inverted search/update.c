#include "main.h"

/* Function to Update the Database*/
int update_database(mainnode **hash_t, char *file_name)
{
    /* Open File in read mode*/
    FILE *fptr = fopen(file_name, "r");
    if (!fptr)
        return FAILURE;

    char temp[100];
    char *token;
    int index = 0, filecount = 0, wordcount = 0;

    /* Read from File*/
    while (fscanf(fptr, "%s", temp) != EOF)
    {
        if (temp[0] == '#')
        {
            /* Use strtok function to generate tokens*/
            token = strtok(temp + 1, ";");
            index = atoi(token);

            token = strtok(NULL, ";");
            char *word = strdup(token);

            token = strtok(NULL, ";");
            filecount = atoi(token);

            /* Create main node*/
            mainnode *m_node = hash_t[index];
            mainnode *prev = NULL;
            int word_found = 0;

            /* Iterate through nodes*/
            while (m_node)
            {
                if (strcmp(m_node -> word, word) == 0)
                {
                    for (int i = 0; i < filecount; i++)
                    {
                        token = strtok(NULL, ";");
                        char *filename = strdup(token);

                        token = strtok(NULL, ";");
                        wordcount = atoi(token);

                        subnode *s_node = m_node -> subnode;
                        int file_found = 0;

                        while (s_node)
                        {
                            if (strcmp(s_node -> filename, filename) == 0)
                            {
                                s_node -> wordcount += wordcount;
                                file_found = 1;
                                break;
                            }
                            if (s_node -> subnode == NULL)
                            {
                                subnode *new_subnode = malloc(sizeof(subnode));
                                new_subnode -> wordcount = wordcount;
                                new_subnode -> filename = malloc(strlen(filename) + 1);
                                strcpy(new_subnode -> filename, filename);
                                new_subnode -> subnode = NULL;
                                s_node -> subnode = new_subnode;
                                m_node -> filecount++;
                                break;
                            }
                            s_node = s_node -> subnode;
                        }
                        if (!file_found)
                        {
                            subnode *new_subnode = malloc(sizeof(subnode));
                            new_subnode -> wordcount = wordcount;
                            new_subnode -> filename = malloc(strlen(filename) + 1);
                            strcpy(new_subnode -> filename, filename);
                            new_subnode -> subnode = m_node -> subnode;
                            m_node -> subnode = new_subnode;
                            m_node -> filecount++;
                        }
                    }
                    word_found = 1;
                    break;
                }
                prev = m_node;
                m_node = m_node -> mainnode;
            }

            if (!word_found)
            {
                mainnode *new_main = malloc(sizeof(mainnode));
                new_main -> word = malloc(strlen(word) + 1);
                strcpy(new_main -> word, word);
                new_main -> filecount = filecount;
                new_main -> mainnode = hash_t[index];
                hash_t[index] = new_main;

                for (int i = 0; i < filecount; i++)
                {
                    token = strtok(NULL, ";");
                    char *filename = strdup(token);

                    token = strtok(NULL, ";");
                    wordcount = atoi(token);

                    subnode *new_sub = malloc(sizeof(subnode));
                    new_sub -> wordcount = wordcount;
                    new_sub -> filename = malloc(strlen(filename) + 1);
                    strcpy(new_sub -> filename, filename);
                    new_sub -> subnode = new_main -> subnode;
                    new_main -> subnode = new_sub;
                }
            }
        }
    }
    fclose(fptr);
    return SUCCESS;
}
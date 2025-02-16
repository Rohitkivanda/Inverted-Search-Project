#include "main.h"

int insert_at_last(Slist **filename_head, char *filename)
{
    //Create a new Node
    Slist *new = malloc(sizeof(Slist));

    //Check node is created or not
    if (new == NULL)
        return FAILURE;

    //If node created Update data and link
    strcpy(new -> filename, filename);
    new -> link = NULL;

    //Check if list is empty
    if (*filename_head == NULL)
    {
        //Update head
        *filename_head = new;
        return SUCCESS;
    }
    else
    {
        Slist *temp = *filename_head;
        while (temp)
        {
            if (!strcmp(temp -> filename, filename))
            {
                printf("ERROR: Duplicate File Detected\tMoving Next...\n");
                return SUCCESS;
            }
            temp = temp -> link;
        }
    }

    //Traverse through the list
    Slist *temp = *filename_head;
    while (temp -> link != NULL)
        temp = temp -> link;
    
    temp -> link = new;
    
    return SUCCESS;
}


#include "main.h"
int read_validate_update(char *file_name)
{
/* Open file in read mode*/
    FILE *fptr = fopen(file_name, "r");
    if (!fptr)
    {
        printf("ERROR: Opening file\n");
        return FAILURE;
    }

    if (!strstr(file_name, ".txt"))
    {
        printf("ERROR: Wrong extension\n");
        printf("USAGE: <filename.txt>\n");
        return FAILURE;
    }

    fseek(fptr, 0, SEEK_END);
    if (!ftell(fptr))
    {
        printf("INFO: File is Empty\n");
        printf("Create Database First\n");
        return SUCCESS;
    }

    rewind(fptr);

    char temp[100];
    fscanf(fptr, "%s", temp);
    if (temp[0] != '#')
    {
        printf("ERROR: File Does not start with #");
        return FAILURE;
    }
    return SUCCESS;
}
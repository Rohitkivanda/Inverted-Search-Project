#include "main.h"
int read_and_validate(int argc, char *argv[], Slist **filename_head)
{
    int i = 1;
    if (argc < 2)
    {
        printf("ERROR: Please Enter FileNames\n");
        printf("Usage: ./a.out <file1.txt> <file2.txt> <file3.txt> ...\n");
        return FAILURE;
    }
    else
    {
        /* Opening all the files in Read Mode*/
        while (argv[i] != NULL)
        {
            if (!fopen(argv[i], "r"))
            {
                printf("ERROR: File <%s> Doesn't Exists\n", argv[i]);
            }
            else
            {
                if (!strstr(argv[i], ".txt"))
                {
                    printf("ERROR: Please include .txt extension\n");
                    printf("Usage: ./a.out <filename.txt> ...\n");
                }     
                else
                {
                    FILE *fptr = NULL;
                    fptr = fopen(argv[i], "r");
                    if (!fptr)
                    {
                        fclose(fptr);
                        return FAILURE;
                    }

                    fseek(fptr, 0, SEEK_END);
                    if (!ftell(fptr))
                    {
                        printf("ERROR: %s is EMPTY\n", argv[i]);
                    }
                    else
                    {
                        insert_at_last(filename_head, argv[i]);
                    }
                }   
            }
            i++;
        }
    }
    return SUCCESS;
}
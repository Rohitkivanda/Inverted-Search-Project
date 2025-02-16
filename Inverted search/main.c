#include "main.h"

int main(int argc, char *argv[])
{
    // Initialize the filename list pointer
    Slist *filename_head = NULL;
    
    if (!read_and_validate(argc, argv, &filename_head))
    {
        return 0; // Exit if validation fails
    }

    printf("Read and Validation Completed\n");

    // Initialize the hash table for the database
    mainnode *hash_t[27] = {NULL};
    int flag = 0; 
    
    int option = 0;
    do
    {
        // Display menu options
        printf("\n1. Create Database\n2. Display Database\n3. Search Database\n4. Save Database\n5. Update Database\n6. Exit\nEnter Choice: ");
        scanf("%d", &option);
        printf("\n");
        
        switch (option)
        {
        case 1:
            // Create the database
            if (create_database(hash_t, filename_head) == 1)
            {
                printf("Created Database successfully\n");
                flag = 1; // Set flag if creation is successful
            }
            else
            {
                printf("Creation of Database Failed\n");
            }
            break;
        
        case 2:
            // Display the database contents
            display_database(hash_t);
            break;

        case 3:
            if (search_database(hash_t) == 1)
            {
                printf("Search Completed Successfully\n");
            }
            else if (search_database(hash_t) == 2)
            {
                printf("Search Failed\n");
            }
            break;
            
        case 4:
            // Save the database to a file
            save_database(hash_t);
            break; 
            
        case 5:
            if (!flag)
            {
                char filename[50];
                printf("Enter the name of File :");
                scanf("%s", filename);
                if (read_validate_update(filename) == 1) 
                {
                    update_database(hash_t, filename);  //update function call
                }
            }
            else
            {
                printf("ERROR: cannot update after creation\n");
            }
            break;
            
        case 6:
            // Exit the program
            break;
            
        default:
            printf("Invalid Option\n");
            break;
        }
    }
    while (option != 6);
}

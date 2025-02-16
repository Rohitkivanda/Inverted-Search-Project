#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#ifndef MAIN_H
#define MAIN_H
#define FAILURE 0
#define SUCCESS 1
#define DATA_NOT_FOUND 2

//structure of linked list
typedef struct Slist_node
{
    char filename[20];
    struct Slist_node *link;
}Slist;

//structure of sub node 
typedef struct sub_node
{
    int wordcount;
    char *filename;
    struct sub_node *subnode;
} subnode;

//structure of main node
typedef struct main_node
{
    int filecount;
    char *word;
    subnode *subnode;
    struct main_node *mainnode;
} mainnode;

/* Function prototypes below*/
int read_and_validate(int argc, char *argv[], Slist **filename_head);
int insert_at_last(Slist **filename_head, char *filename);

int create_database(mainnode **hash_t, Slist *filename_head);
void display_database(mainnode **hash_t);
int search_database(mainnode **hash_t);
int save_database(mainnode **hash_t);
int update_database(mainnode **hash_t,char *file_name);
int read_validate_update(char *file_name);
#endif
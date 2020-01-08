//Include
#include "ISAM.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef _ISAM_C
#define _ISAM_C

#define ISAM_DEBUG 1

//Function: Creates database files, and sets all records to available. Inits ISAM structure
ISAM new_ISAM(char* pName, int pMax_records, int pMax_overflow)
{
    if(ISAM_DEBUG)
    {
        printf("**CREATING NEW ISAM DB: %s\n", pName);
        
    }
    //allocate a new ISAM structure
    ISAM temp = malloc(sizeof(ISAM_STRUCT));
    //Init struct variables
    strncpy(temp->name, pName, 512);
    //Set the max record counts
    temp->max_records = pMax_records;
    temp->max_overflow = pMax_overflow;
    temp->max_total_records = pMax_records * pMax_overflow;

    //Zero out the current count of items
    temp->record_count = 0;
    temp->overflow_count = 0;
    temp->total_record_count = 0;

    //Set the internal record structs to null
    temp->record = NULL;
    temp->index = NULL;


    //Set the function pointers
    temp->write_index = NULL;
    temp->write_record = NULL;


    //Create the database files
    create_index(temp);

    return temp;

}
/*
    Creates the database .idx, .raf, and .of files.
    Inits all record positions to available.
*/
void create_database_files(ISAM DB)
{

}

int create_index(ISAM DB)
{
    FILE *fileptr = NULL;
    int offset = 0;

    if (ISAM_DEBUG)
        printf("\n**CREATING INDEX FILE");

    //Check for existing file
    if(open_isam_file(DB, INDEXFILE, "r") == NULL)
    {
        if(ISAM_DEBUG)
        {
            puts("\n**CREATING THE INDEX FILE");
        }
        //Create the index file
        fileptr = open_isam_file(DB, INDEXFILE, "w");
    }
    else
    {
        if(ISAM_DEBUG)
        {
            puts("\n**INDEX FILE EXISTS - CHECKING FOR EXISTING DATA");
        }
        //TODO check for existing index file
        //fileptr = open_isam_file(DB, INDEXFILE, "r")
    }

    //init counts and record entries
    //ensure the file is open
    if(fileptr != NULL)
    {
        //Write the record counts to the file
        //Write raf record count
        fprintf(fileptr, "%d", DB->record_count);
        //seek to second integer
        fseek(fileptr, sizeof(int), SEEK_SET);
        //Write overflow record count
        fprintf(fileptr, "%d", DB->overflow_count);
        
        int i;

        for(i = 0; i < 100; i++)
        {
            //TODO: seek the size of the index struct plus the offset of the counts
            //offset = (sizeof(int) * 2) + (i * INDEX_STRUCT);
            //Write all index entries to the file
            //Seek to all record entries
            
            //Print an empty Record
            fprintf(fileptr, "%s", i);
        }
        //close file
        fclose(fileptr);
    }


 

    //Return success 
    return 0;
}

/* Creates the ISAM main record file */
int create_record_file(ISAM DB)
{
    if (ISAM_DEBUG)
        printf("\nCREATING RECORD FILE");
    //Open/create file
    FILE *fileptr = open_isam_file(DB, RAFILE, "w");

    //Set all records to available
    //close file
    fclose(fileptr);

    //Return success 
    return 0;
}

/* Creates the ISAM overflow file */
int create_overflow_file(ISAM DB)
{
    if (ISAM_DEBUG)
        printf("\nCREATING OVERFLOW FILE");

    //Open/create file
    FILE *fileptr = open_isam_file(DB, OVERFLOWFILE, "w");

    //Set all records to available

    //Close file
    fclose(fileptr);

    //Return success 
    return 0;
}

/*
    Once the random access file is created the 
*/
int init_record_file(ISAM DB, FILE* fileptr)
{
    //Loop through 0 to DB->max_record_count
    //Set each record as available
    int i;
    for(i = 0; i < DB->max_records; i++)
    {
        fseek(fileptr, i*sizeof(RECORD_STRUCT), SEEK_SET);
        //Set the record to available
    }
    //return success
    return 0;
}


/*
    Opens the specified file in the specified mode and returns a pointer
    Utilizes the files enum to determine the selected file
*/
FILE *open_isam_file(ISAM DB, int pFile_num, char *pMode)
{
    FILE *fileptr;
    char filename[512];
    switch (pFile_num)
    {
    case RAFILE:
        sprintf(filename, "%s.raf", DB->name);
        fileptr = fopen(filename, pMode);
        break;
    case OVERFLOWFILE:
        sprintf(filename, "%s.of", DB->name);
        fileptr = fopen(filename, pMode);
        break;
    case INDEXFILE:
        sprintf(filename, "%s.idx", DB->name);
        fileptr = fopen(filename, pMode);
        break;
    default:
        puts("\n**INVALID FILE SELECTED FOR CREATION");
        break;
    }

    return fileptr;
}
#endif
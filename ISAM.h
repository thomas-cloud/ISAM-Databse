/*
    This is a defenition of the functions used to create the isam files
    struct ISAM is the structre that contains all information for the data base 
    as well as the functions used to interact with the database
*/

#include <stdio.h>

#ifndef _ISAM_H_
#define _ISAM_H_

//Debug variable. if set debug info will be printed
#define DEBUG 0

//Define an external data type for the index and record format
extern struct INDEX_STRUCT; //Placeholder declaration for the INDEX datastructure. Used in the record file to store key/value pairs and file location. Must be created before use.
extern struct RECORD_STRUCT; //Placeholder declaration for the RECORD datastructure. Used to read and write data to the database

//Define the pointer types
typedef struct ISAM_STRUCT *ISAM; //ISAM DB structure. Holds all information required for the database to operate.
typedef struct INDEX_STRUCT *INDEX; //INDEX structure. Used in the record file to store key/value pairs and file location.
typedef struct RECORD_STRUCT *RECORD; //RECORD structure. This is the structure that will be read/written to the database files.



typedef struct ISAM_STRUCT
{
    char name[512];        //Name of the database. Limit of 512 characters
    int max_records;       //Max number of records that can be held in the Random Access File (.raf) file
    int max_overflow;      //Max number of records that can be held in the Overflow (.of) file 
    int max_total_records; //Max number of records that can be held in the database. A sum of raf and of max records
    int record_count;      //Count of non-overflow records
    int overflow_count;    //Count of records in overflow file
    int total_record_count;     //Total number of records stored in databases
    void *record;          //Pointer to record struct
    void *index;           //Pointer to index record struct

    //Functions to set up the database
    void (*write_index)(ISAM isam, int record_num, char* mode);                         //Function: Writes a single index entry
    void (*write_record)(ISAM isam, int file_selector, int record_hash, char* mode);    //Function: Writes a single database record


} ISAM_STRUCT;

//Enunumerated File names to ints for easier file reference
enum files
{
    RAFILE,
    OVERFLOWFILE,
    INDEXFILE
};

                                   //Function: Creates database files, and sets all records to available. Inits ISAM structure
ISAM new_ISAM(char* pName, int pMax_records, int pMax_overflow);
//Function to create the required database files
void create_database_files(ISAM DB);
//Creates the index files and inits the data
int create_index(ISAM DB);
//Creates the record file and sets all records to available
int create_record_file(ISAM DB);
//Creates the overflow file and sets all records to available
int create_overflow_file(ISAM DB);
//Opens the specified file in the specified mode
FILE *open_isam_file(ISAM DB, int pFile_num, char *pMode);



#endif
#include <stdio.h>
#include <string.h>
#include "filesystem.h"

static FileControlBlock files[MAX_FILES];


/* 
    the initializeFileSystem() prepares the file system at the program start

    1 - takes 100 file slots as empty 
    2 - clears names and contents
    3 - set size to 0

*/
void initializeFileSystem(void) { 
    int i;
    for (i = 0; i < MAX_FILES; i++) {
        files[i].isUsed = 0;
        files[i].size = 0;
        files[i].name[0] = '\0';
        files[i].content[0] = '\0';
    }
}

/*
    this helper function to search for a file by name
    it is used in most of the function

    1 - loops all file slots
    2 - checks isUsed == 1 
    3 - compares the file name with strcmp
    4 - returns the index if found, if not -1

*/
int findFile(const char *name) {
    int i;
    for (i = 0; i < MAX_FILES; i++) {
        if (files[i].isUsed && strcmp(files[i].name, name) == 0) {
            return i;
        }
    }
    return -1;
}

/*
    this function creates new file

    1 - checks if the file name already exists
    2 - find empty slot in the array
    3 - stores the file name
    4 - set size to 0 and content to empty
    5 - mark that it is used isUsed = 1

*/
void createFile(const char *name) {
    int i;

    if (findFile(name) != -1) {
        printf("Error: File '%s' already exists.\n", name);
        return;
    }

    for (i = 0; i < MAX_FILES; i++) {
        if (!files[i].isUsed) {
            files[i].isUsed = 1;
            strncpy(files[i].name, name, MAX_NAME_LENGTH - 1); 
            files[i].name[MAX_NAME_LENGTH - 1] = '\0';
            files[i].size = 0;
            files[i].content[0] = '\0';

            printf("File '%s' created successfully.\n", files[i].name);
            return;
        }
    }

    printf("Error: File system is full. Cannot create more files.\n");
}

/*
    this writes data into existing file

    1 - finds the file by name
    2 - checks that content size < 1024
    3 - copies the text into the file content
    4 - update the size
*/
void writeFile(const char *name, const char *content) {
    int index;
    size_t len;

    index = findFile(name);
    if (index == -1) {
        printf("Error: File '%s' not found.\n", name);
        return;
    }

    len = strlen(content);
    if (len >= MAX_CONTENT_SIZE) {
        printf("Error: Content exceeds maximum file size (%d bytes).\n", MAX_CONTENT_SIZE - 1);
        return;
    }

    strncpy(files[index].content, content, MAX_CONTENT_SIZE - 1);
    files[index].content[MAX_CONTENT_SIZE - 1] = '\0';
    files[index].size = (int)strlen(files[index].content);

    printf("Content written to file '%s' successfully.\n", name);
}


/*
    this prints the file content

    1 - finds the file by name
    2 - display text stored inside the content
*/
void readFile(const char *name) {
    int index;

    index = findFile(name);
    if (index == -1) {
        printf("Error: File '%s' not found.\n", name);
        return;
    }

    printf("Content of '%s':\n%s\n", name, files[index].content);
}

void deleteFile(const char *name) {

}

void listFiles(void) {
    
}

void searchFile(const char *name) {
    
}
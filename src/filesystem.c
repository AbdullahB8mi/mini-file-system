#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "filesystem.h"

static FileControlBlock files[MAX_FILES];

/*
    this function clears the terminal screen

    1 - check system type
    2 - use cls for windows
    3 - use clear for linux/mac
*/
void clearScreen(void) {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

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
        printf(RED "Error: File '%s' already exists.\n" RESET, name);
        return;
    }

    for (i = 0; i < MAX_FILES; i++) {
        if (!files[i].isUsed) {
            files[i].isUsed = 1;
            strncpy(files[i].name, name, MAX_NAME_LENGTH - 1); 
            files[i].name[MAX_NAME_LENGTH - 1] = '\0';
            files[i].size = 0;
            files[i].content[0] = '\0';

            printf(GREEN "File '%s' created successfully.\n" RESET, files[i].name);
            return;
        }
    }

    printf(RED "Error: File system is full.\n" RESET);
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
        printf(RED "Error: File '%s' not found.\n" RESET, name);
        return;
    }

    len = strlen(content);
    if (len >= MAX_CONTENT_SIZE) {
        printf(RED "Error: Content exceeds maximum size.\n" RESET);
        return;
    }

    strncpy(files[index].content, content, MAX_CONTENT_SIZE - 1);
    files[index].content[MAX_CONTENT_SIZE - 1] = '\0';
    files[index].size = (int)strlen(files[index].content);

    printf(GREEN "Content written to file '%s'.\n" RESET, name);
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
        printf(RED "Error: File '%s' not found.\n" RESET, name);
        return;
    }

    printf(BLUE "\nContent of '%s':\n" RESET, name);
    printf("%s\n", files[index].content);
}

/*
    this function deletes a file

    1 - finds the file by name
    2 - mark isUsed = 0 (free the slot)
    3 - clear name and content
    4 - set size to 0
*/
void deleteFile(const char *name) {
    int index;

    index = findFile(name);
    if (index == -1) {
        printf(RED "Error: File '%s' not found.\n" RESET, name);
        return;
    }

    files[index].isUsed = 0;
    files[index].size = 0;
    files[index].name[0] = '\0';
    files[index].content[0] = '\0';

    printf(GREEN "File '%s' deleted successfully.\n" RESET, name);
}

/*
    this function lists all files

    1 - loops all file slots
    2 - checks isUsed == 1
    3 - prints file name and size in table style
    4 - prints message if no files found
*/
void listFiles(void) {
    int i;
    int count = 0;

    printf(BLUE "\n-----------------------------------------------\n" RESET);
    printf(BLUE "No.   File Name                         Size\n" RESET);
    printf(BLUE "-----------------------------------------------\n" RESET);

    for (i = 0; i < MAX_FILES; i++) {
        if (files[i].isUsed) {
            count++;
            printf("%-5d %-30s %d bytes\n", count, files[i].name, files[i].size);
        }
    }

    if (count == 0) {
        printf(YELLOW "No files found.\n" RESET);
    }

    printf(BLUE "-----------------------------------------------\n" RESET);
    printf(YELLOW "Total files: %d / %d\n", count, MAX_FILES);
}

/*
    this function searches for a file

    1 - finds the file by name
    2 - if found print file details
    3 - if not found print error
*/
void searchFile(const char *name) {
    int index;

    index = findFile(name);
    if (index == -1) {
        printf(RED "File '%s' not found.\n" RESET, name);
        return;
    }

    printf(GREEN "File found:\n" RESET);
    printf("Name: %s\n", files[index].name);
    printf("Size: %d bytes\n", files[index].size);
}
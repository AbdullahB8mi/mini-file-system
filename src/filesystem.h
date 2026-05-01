#ifndef FILESYSTEM_H
#define FILESYSTEM_H

#define GREEN "\033[0;32m"
#define RED   "\033[0;31m"
#define BLUE  "\033[0;34m"
#define YELLOW "\033[0;33m"
#define RESET "\033[0m"

#define MAX_FILES 100 //takes 100 files slots as empty
#define MAX_NAME_LENGTH 50
#define MAX_CONTENT_SIZE 1024
#define INPUT_SIZE 2048

typedef struct {
    char name[MAX_NAME_LENGTH];
    int size;
    char content[MAX_CONTENT_SIZE];
    int isUsed;
} FileControlBlock;

void initializeFileSystem(void); //prepares the file system at program starts
int findFile(const char *name); 
void createFile(const char *name); 
void writeFile(const char *name, const char *content);
void readFile(const char *name);
void deleteFile(const char *name);
void listFiles(void);
void searchFile(const char *name);

void clearScreen(void);

#endif
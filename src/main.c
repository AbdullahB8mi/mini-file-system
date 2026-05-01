#include <stdio.h>
#include <string.h>
#include "filesystem.h"

static void printHelp(void) {
    printf(BLUE "\nAvailable commands:\n" RESET);
    printf("  create <filename>          Create file\n");
    printf("  write <filename> <text>    Write content\n");
    printf("  read <filename>            Read file\n");
    printf("  delete <filename>          Delete file\n");
    printf("  list                       Show files\n");
    printf("  search <filename>          Search file\n");
    printf("  help                       Show help\n");
    printf("  exit                       Exit\n\n");
}

void printwelcome(void) {
    printf(GREEN "============================================================\n" RESET);
    printf(GREEN "        KING FAHD UNIVERSITY OF PETROLEUM & MINERALS        \n" RESET);
    printf(GREEN "============================================================\n" RESET);
    printf(YELLOW "                    KFUPM - ICS 433                         \n" RESET);
    printf(BLUE   "              Mini File System Simulator                    \n" RESET);
    printf(GREEN "============================================================\n\n" RESET);
}

int main(void) {
    char input[INPUT_SIZE];
    char command[20];
    char name[MAX_NAME_LENGTH];
    char content[MAX_CONTENT_SIZE];
    int firstTime = 1;

    initializeFileSystem();

    clearScreen();
    printwelcome();
    printHelp();

    while (1) {
        printf("mfs> ");

        if (fgets(input, sizeof(input), stdin) == NULL) {
            break;
        }

        input[strcspn(input, "\n")] = '\0';

        if (sscanf(input, "%19s", command) != 1) {
            continue;
        }

        clearScreen();
        printwelcome();

        if (firstTime) {
            firstTime = 0;
        }

        if (strcmp(command, "create") == 0) {
            if (sscanf(input, "create %49s", name) == 1)
                createFile(name);
            else
                printf("Usage: create <filename>\n");

        } else if (strcmp(command, "write") == 0) {
            if (sscanf(input, "write %49s %[^\n]", name, content) == 2)
                writeFile(name, content);
            else
                printf("Usage: write <filename> <content>\n");

        } else if (strcmp(command, "read") == 0) {
            if (sscanf(input, "read %49s", name) == 1)
                readFile(name);
            else
                printf("Usage: read <filename>\n");

        } else if (strcmp(command, "delete") == 0) {
            if (sscanf(input, "delete %49s", name) == 1)
                deleteFile(name);
            else
                printf("Usage: delete <filename>\n");

        } else if (strcmp(command, "list") == 0) {
            listFiles();

        } else if (strcmp(command, "search") == 0) {
            if (sscanf(input, "search %49s", name) == 1)
                searchFile(name);
            else
                printf("Usage: search <filename>\n");

        } else if (strcmp(command, "help") == 0) {
            printHelp();

        } else if (strcmp(command, "exit") == 0) {
            printf(YELLOW "Exiting...\n" RESET);
            break;

        } else {
            printf(RED "Unknown command.\n" RESET);
        }

        printf("\n");
    }

    return 0;
}
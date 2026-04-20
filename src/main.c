#include <stdio.h>
#include <string.h>
#include "filesystem.h"

static void printHelp(void) { // help command prints this
    printf("\nAvailable commands:\n");
    printf("  create <filename>\n");
    printf("  write <filename> <content>\n");
    printf("  read <filename>\n");
    printf("  delete <filename>\n");
    printf("  list\n");
    printf("  search <filename>\n");
    printf("  help\n");
    printf("  exit\n\n");
}

int main(void) {
    char input[INPUT_SIZE];
    char command[20];
    char name[MAX_NAME_LENGTH];
    char content[MAX_CONTENT_SIZE];

    initializeFileSystem(); //starter function

    printf("Mini File System Simulator\n");
    printHelp();

    while (1) { // infinite loop
        printf("mfs> ");

        if (fgets(input, sizeof(input), stdin) == NULL) {
            break;
        }

        input[strcspn(input, "\n")] = '\0';

        if (sscanf(input, "%19s", command) != 1) {
            continue;
        }

        if (strcmp(command, "create") == 0) {
            if (sscanf(input, "create %49s", name) == 1) {
                createFile(name);
            } else {
                printf("Usage: create <filename>\n");
            }

        } else if (strcmp(command, "write") == 0) {
            if (sscanf(input, "write %49s %[^\n]", name, content) == 2) {
                writeFile(name, content);
            } else {
                printf("Usage: write <filename> <content>\n");
            }

        } else if (strcmp(command, "read") == 0) {
            if (sscanf(input, "read %49s", name) == 1) {
                readFile(name);
            } else {
                printf("Usage: read <filename>\n");
            }

        } else if (strcmp(command, "delete") == 0) {
            if (sscanf(input, "delete %49s", name) == 1) {
                deleteFile(name);
            } else {
                printf("Usage: delete <filename>\n");
            }

        } else if (strcmp(command, "list") == 0) {
            listFiles();

        } else if (strcmp(command, "search") == 0) {
            if (sscanf(input, "search %49s", name) == 1) {
                searchFile(name);
            } else {
                printf("Usage: search <filename>\n");
            }
            
        } else if (strcmp(command, "help") == 0) {
            printHelp();
        } else if (strcmp(command, "exit") == 0) {
            printf("Exiting Mini File System Simulator.\n");
            break;
        } else {
            printf("Unknown command. Type 'help' to see available commands.\n");
        }
    }

    return 0;
}
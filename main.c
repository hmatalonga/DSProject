/* 
 * File:   main.c
 * Author: hugo
 *
 * Created on 17 de Setembro de 2014, 16:40
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "config.h"
#include "utils.h"
#include "file.h"

/*
 * Main
 */
int main(int argc, char** argv) {
    // Data structures
    int cc = 20;
    PERSON *people = NULL;
    COURSE **courses = (COURSE **) malloc(cc*sizeof(COURSE *));
    
    char queryInput[QUERY_MAX_SIZE]; // String query
    char filePath[128]; // File path string
    FILE *fp = NULL; // File pointer
    int verbose = 0; // Verbose mode flag
    int customFile = 0; // File parameter flag
    int i = 0; // for variable helper
    int query_det = 0; // Query flag
    int isRunning = 0; // Program KeepAlive flag
    
    if (argc > 1) {
        for (i = 1; i < argc; i++) {
            if (strcmp(argv[i], "-v") == 0)
                verbose = 1; // Turn on verbose flag
            else if (strcmp(argv[i], "-f") == 0) {
                if (argv[i+1] != NULL) {
                    customFile = 1; // Turn on custom file flag
                    strcpy(filePath, argv[i+1]); // Copy file path
                }
            }
        }
    }

    // if custom flag is off load default data file
    if (!customFile) 
        strcpy(filePath, DATA_FILE_PATH);
    
    // Begin ---
    // Init courses array to NULL
    for (i = 0; i < 20; i++)
        courses[i] = NULL;
    
    // Build screen
    clearScreen();
    printf(PROGRAM_HEADER);
    
    // Load file into memory
    // Check
    if (verbose)
        printf("Checking if file exists...");
    if (fileExists(filePath)) {
        if (verbose)
            printf(" -> DONE\n");
        // if file exists then load it
        if (verbose)
            printf("Loading file...\n");
        // Building data struct
        people = fileRead(fp, filePath, people, courses, &cc);
        isRunning = 1; // Keep alive
        if (verbose)
            printf("DONE\n");        
    }
    else {
        // else throw IO error exception
        printf(IO_ERROR_EXCEPTION);
        return(EXIT_FAILURE);
    }
    
    if (verbose)
        printf("Initialization done...\n");  
    
    // Loop
    while(isRunning) {
        clearScreen();       
        printf(PROGRAM_HEADER);
        printf("Type 'help' for more information, 'exit' to quit.\n\n");
        printf("-> ");
        // Read input
        if (fgets(queryInput, sizeof(queryInput), stdin)) {
            if (verbose)
                printf("Converting to uppercase...\n");
            toUpperCase(queryInput);
            // Check
            // if input is valid continue
            if ((query_det = checkQueryFormat(queryInput)) > 0) {
                // Show query results if any
                if (query_det == 1);
                    //peformQuery(myDataset, queryInput, verbose);
                else if (query_det == 2) {
                    clearScreen();       
                    printf(PROGRAM_HEADER);
                    printf(HELP_INFO);
                }
                else if (query_det == 3)
                    return (EXIT_SUCCESS);
            }
            // else throw format error exception
            else {
                printf(QUERY_ERROR_EXCEPTION);
            }
            doPause();
        } 
    // EndLoop
    }
    return (EXIT_SUCCESS);
}
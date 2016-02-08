#include "utils.h"
#include "file.h"

/**
 * Converte uma string para uppercase
 * @param value String a converter
 */
void toUpperCase(char *value) {
    while (*value != '\0') {
        if (*value >= 'a' && *value <= 'z')
            *value -= 32;
        value++;
    }
}

/**
 * Limpa o ecran da consola usando terminal codes
 */
void clearScreen() {
    printf("\033[2J");
    printf("\033[%d;%dH", 0, 0);
}

/**
 * Pausa a execução do programa
 */
void doPause() {
    printf("%s", PAUSE_MESSAGE);
    getchar();
}

/**
 * Verifica se a query recebida é válida e que tipo de comando representa
 * @param query Query a ser validada
 * @return Retorna 0 se a query não for válida, outros valores dependendo do tipo de comando
 */
int checkQueryFormat(char *query) {
    int isValid = 0, i = 0, prev = 0;
    while (query[i] != '\0' && query[i] != '\n') {
        if (query[i] == 'C') {
            i++;
            prev = i;
            while (query[i] >= '0' && query[i] <= '9')
                i++;
            if (prev == i) {
                isValid = 0;
                break;
            }
            if (!(query[i] == '+' || query[i] == '-')) {
                isValid = 0;
                break;
            }
            i++;
            prev = i;
            while (query[i] >= '0' && query[i] <= '9')
                i++;
            // Check if grade has less than 2 digits
            if (prev == i || (i-prev) > 2) {
                isValid = 0;
                break;
            }
            isValid = 1;
        }
        else {
            isValid = 0;
            break;
        }
    }
    if ((strcmp(query, "HELP\n") == 0) || (strcmp(query, "?\n") == 0))
        isValid = 2;
    else if (strcmp(query, "EXIT\n") == 0)
        isValid = 3;
    return isValid;
}

/**
 * Executa uma query de pesquisa e mostra o seu output
 * @param dataset Lista contendo os registos a ser pesquisados
 * @param query Query de pesquisa a processar
 * @param verbose Flag de modo verbose 
 */
void peformQuery(PLIST *dataset, char *query, int verbose) {
    unsigned short int course;
    unsigned char grade;
    char operator, *pch = strtok(query, "C");
    PLIST *temp = NULL;
    RESLIST *output = NULL, *ret = NULL;
    clock_t start, diff;

    /**
     * Ler query de pesquisa
     * Aceder a primeira query
     * Loop:
     *   Percorrer Lista e encontrar equals da segunda lista
     *   inserir elementos iguais numa nova lista
     * :endLoop
     * contar elementos da lista de resultados
     * sort lista de resultados
     * output de valores
     */
    
    if (verbose)
        printf("Building query from dataset...\n");    

    if (verbose)
        start = clock();
    
    while (pch != NULL) {
        sscanf(pch, QUERY_FORMAT, &course, &operator, &grade);

        temp = dataset;
        
        if (operator == '+') {
            while (temp != NULL) {
                if (temp->course == course && temp->grade > grade)
                    ret = ResAppend(ret, temp);
                temp = temp->next;
            }
            if (verbose)
                printf("\tUpdating output list...");
            output = ResCopy(output, ret);
            if (verbose)
                printf(" -> DONE\n");            
            if (verbose)
                printf("\tClearing memory of auxiliar variables...");          
            ret = ResClearAll(ret); // ret = NULL
            if (verbose)
                printf(" -> DONE\n");
        }
        else if(operator == '-') {
            while (temp != NULL) {
                if (temp->course == course && temp->grade < grade)
                    ret = ResAppend(ret, temp);
                temp = temp->next;
            }
                
            if (verbose)
                printf("\tUpdating output list...");
            output = ResCopy(output, ret);
            if (verbose)
                printf(" -> DONE\n");            
            if (verbose)
                printf("\tClearing memory of auxiliar variables...");          
            ret = ResClearAll(ret); // ret = NULL
            if (verbose)
                printf(" -> DONE\n");      
        }
        
        pch = strtok(NULL, "C");
    }
    
    if (verbose)
        printf("DONE\nSorting results...\n");
    output = quickSort(output, getTail(output));
    if (verbose)
        printf("DONE\nRemoving duplicates...\n");
    output = removeDuplicates(output);
    if (verbose)
        printf("DONE\n");
    long int c = ResCount(output);

    if (verbose)
        diff = clock() - start;

    printf("%ld\n", c);
    ResPrint(output);
    if (verbose)
        printf("Results count -> %ld\n", c);

    if (verbose) {
        float msec = ((float)diff) / CLOCKS_PER_SEC;
        printf("Time taken to build and sort results -> %f seconds", msec);
    }
}
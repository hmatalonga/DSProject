#include "utils.h"

void toUpperCase(char *value) {
    while (*value != '\0') {
        if (*value >= 'a' && *value <= 'z')
            *value -= 32;
        value++;
    }
}

void clearScreen() {
    printf("\033[2J");
    printf("\033[%d;%dH", 0, 0);
}

void doPause() {
    printf("%s", PAUSE_MESSAGE);
    getchar();
}

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
            if (prev == i || (i - prev) > 2) {
                isValid = 0;
                break;
            }
            isValid = 1;
        } else {
            isValid = 0;
            break;
        }
    }
    if ((strcmp(query, "HELP\n") == 0) || (strcmp(query, "?\n") == 0))
        isValid = 2;
    else if (strcmp(query, "EXIT\n") == 0)
        isValid = 3;
    /*
    else if (sscanf(query, "SHOW %s %d\n") != EOF)
        isValid = 4;
    else if (sscanf(query, "COUNT %s %d\n") != EOF)
        isValid = 5;
     */
    return isValid;
}

int validaRegisto(NOTE **course_array, unsigned short int course_index, QUERY *pesquisa, QUERY *best) {
    while (pesquisa != NULL) {
        if (pesquisa == best) {
            pesquisa = pesquisa->next;
            continue;
        }
        if (course_array[pesquisa->course - 1] == NULL)
            return 0;
        if (pesquisa->operator == '+') {
            if (course_array[pesquisa->course - 1]->grade <= pesquisa->grade)
                return 0;
        } else {
            if (course_array[pesquisa->course - 1]->grade >= pesquisa->grade)
                return 0;
        }
        pesquisa = pesquisa->next;
    }
    return 1;
}

int peformQuery(PERSON *people, COURSE **courses, char *query, int verbose) {
    unsigned short int course;
    unsigned char grade, valido = 0;
    char operator, *pch = strtok(query, "C");
    unsigned long int totalRec = 0;
    COURSE *rc = NULL;
    NOTE *rg = NULL;
    RESLIST *output = NULL, *ret = NULL;
    QUERY *search = NULL, *best = NULL, *tempt = NULL;
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

    while (pch != NULL) {
        sscanf(pch, QUERY_FORMAT, &course, &operator, &grade);
        if (grade < 20) //safefail
            search = appendCriteria(search, course, grade, operator);
        pch = strtok(NULL, "C");
    }

    if (search != NULL) {
        if (search->next != NULL) {
            // varias pesquisas
            best = findBest(search);
            rc = courses[best->course - 1];
            if (rc != NULL)
                rg = rc->grades[best->grade - 1];
            while (rg != NULL) {
                if (validaRegisto(rg->person->course_array, rg->person->course_index, search, best))
                    output = ResAppend(output, rg->person);
                rg = rg->next;
            }
        } else {
            if (courses[search->course - 1] != NULL) {
                // Pesquisa unica
                NOTE *aux = NULL;
                if (search->operator == '+') {
                    unsigned char i = search->grade + 1;
                    for (; i < 21; i++) {
                        aux = courses[search->course - 1]->grades[i];
                        while (aux != NULL) {
                            output = ResAppend(output, aux->person);
                            aux = aux->next;
                        }
                    }
                } else { // -

                    unsigned char i = search->grade - 1;
                    for (; i >= 0; i--) {
                        aux = courses[search->course - 1]->grades[i];
                        while (aux != NULL) {
                            output = ResAppend(output, aux->person);
                            aux = aux->next;
                        }
                    }
                }
            }
        }
    }

    // Free search
    QUERY *current = search, *temp = NULL;
    while (current != NULL) {
        temp = current;
        current = current->next;
        free(temp);
    }
    search = NULL;

    if (verbose)
        printf("DONE\nSorting results...\n");
    output = quickSort(output, getTail(output));
    if (verbose)
        printf("DONE\n");
    long int c = ResCount(output);
    printf("%ld\n", c);
    ResPrint(output);
    if (verbose)
        printf("Results count -> %ld\n", c);

    output = ResClearAll(output);

    return 0;
}
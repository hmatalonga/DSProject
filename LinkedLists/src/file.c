#include "file.h"

/**
 * Verifica se um ficheiro existe
 * @param filename Caminho para o ficheiro
 * @return 1 se ficheiro existe, 0 se não existir
 */
int fileExists(char *filename) {
    FILE *fp = fopen(filename, "r");
    if (fp != NULL) {
        fclose(fp);
        return 1;
    }
    return 0;
}

/**
 * Carrega registos de um ficheiro de texto para uma estrutura de dados em memória
 * @param fp Ponteiro para ficheiro a ler
 * @param filename Caminho do ficheiro a ler
 * @param dataset Ponteiro para a estrutura de dados que guarda os registos
 * @return A Lista de registos preenchida
 */
PLIST *fileRead(FILE *fp, char *filename, PLIST *dataset) {
    fp = fopen(filename, "r");
    int n = 0;
    PLIST rec;
    
    // Use for limited number of records
    // n < MAX_RECORD_NUMBER
    // User for whole file
    // !feof(fp)
    while (!feof(fp)) {
        fscanf(fp, DATA_RECORD_FORMAT,
                &rec.cal.day, &rec.cal.month, &rec.cal.year,
                &rec.id, &rec.course, &rec.grade);
        
        dataset = PLISTAppend(dataset, &rec);
        //n++; // for limited number of records
    }
    fclose(fp);
    
    return dataset;
}
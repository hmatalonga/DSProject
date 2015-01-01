#include "file.h"

int fileExists()
{
    FILE *fp = fopen(DATA_FILE_PATH, "r");
    if (fp != NULL) {
        fclose(fp);
        return 1;
    }
    return 0;
}

PERSON *fileRead(FILE *fp, char *filename, PERSON *persons, COURSE **courses, unsigned char *cc)
{
    fp = fopen(filename, "r");
    int n = 0;
    TEMP rec;
    PERSON *courseRec = NULL;

    // Use for limited number of records
    // n < MAX_RECORD_NUMBER
    // User for whole file
    // !feof(fp)

    while (n < MAX_RECORD_NUMBER) {
        // Read data from file
        fscanf(fp, DATA_RECORD_FORMAT,
               &rec.cal.day, &rec.cal.month, &rec.cal.year,
               &rec.id, &rec.course, &rec.grade);

        if (rec.grade > *cc) {
            // Save new index
            *cc = rec.grade;            
            // Extend array size
            courses = (COURSE **) realloc(courses, *cc*sizeof(COURSE *));
            // Set array new index to NULL
            courses[*cc-1] = NULL;
        }
        
        // Insert data
        persons = insertPerson(persons, courses, rec);

        n++;
    }
    fclose(fp);

    /*
    while (!feof(fp)) {
        fscanf(fp, DATA_RECORD_FORMAT,
                &rec.cal.day, &rec.cal.month, &rec.cal.year,
                &rec.id, &rec.course, &rec.grade);

        if ((courseRec = CNodeLookUp(tree, rec.course)) == NULL) {
            tree = CNodeInsert(tree, rec.course);
            courseRec = CNodeLookUp(tree, rec.course);
        }

        courseRec->hash->count[rec.grade]++;
        courseRec->hash->table[rec.grade] = BLISTAppend(courseRec->hash->table[rec.grade], rec.cal, rec.id);

        //n++; // for limited number of records
    }
    */

    return persons;
}

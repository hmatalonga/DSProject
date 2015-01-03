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
    int n = 0, i;
    TEMP rec;

    // Use for limited number of records
    // n < MAX_RECORD_NUMBER
    // User for whole file
    // !feof(fp)

    while (!feof(fp)) {
        // Read data from file
        fscanf(fp, DATA_RECORD_FORMAT,
               &rec.cal.day, &rec.cal.month, &rec.cal.year,
               &rec.id, &rec.course, &rec.grade);

        if (rec.course > *cc) {      
            // Extend array size
            courses = (COURSE **) realloc(courses, rec.course*sizeof(COURSE *));
            // Set array new index to NULL
            for (i = *cc; i < rec.course; i++)
                courses[i] = NULL;
            // Save new index
            *cc = rec.course;            
        }
        
        // Insert data
        persons = insertPerson(persons, courses, rec);
        
        //n++;
    }
    fclose(fp);

    return persons;
}

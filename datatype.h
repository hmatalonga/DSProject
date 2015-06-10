typedef struct Calendar {
    unsigned char day, month;
    unsigned short int year;
} CALENDAR;
    
typedef struct Temp {
    CALENDAR cal;
    unsigned long int id;
    unsigned short int course;
    unsigned char grade;
} TEMP;     

typedef struct Person PERSON;

typedef struct Note {
    unsigned char grade;
    PERSON *person;
    struct Note *prev, *next;
} NOTE;

typedef struct Person {
    unsigned long int id;
    unsigned short int course_index; // Num max de index de curso
    NOTE **course_array;
    unsigned int height;
    struct Person *left, *right;
} PERSON;

typedef struct Course {
    unsigned int counter;
    NOTE **grades;
} COURSE;

typedef struct Query {
    unsigned short int course;
    unsigned char grade;
    char operator;
    struct Query *next;
} QUERY;

typedef struct ResList {
    PERSON *elem;
    struct ResList *next;
} RESLIST;

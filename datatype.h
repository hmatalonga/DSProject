/* 
 * File:   datatype.h
 * Author: hugo
 *
 * Created on 23 de Setembro de 2014, 19:09
 */

#ifndef DATATYPE_H
#define	DATATYPE_H

#include "config.h"

#ifdef	__cplusplus
extern "C" {
#endif

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

typedef struct BList { // Lista com datas e pessoas
    CALENDAR cal;
    unsigned long int id;
    struct BList *next;
} BLIST;  

typedef struct Hashtable {
    int size;
    unsigned long int count[HASH_SIZE];
    BLIST **table;
} HASH;

typedef struct CNode {
    unsigned short int course;
    HASH *hash;
    struct CNode *left, *right;
    int height;
} CNODE;

typedef struct ResList {
    BLIST *elem;
    struct ResList *next;
} RESLIST;

#ifdef	__cplusplus
}
#endif

#endif	/* DATATYPE_H */

/* 
 * File:   datatype.h
 * Author: hugo
 *
 * Created on 23 de Setembro de 2014, 19:09
 * 
 * Biblioteca que define as estruturas de dados usadas no programa
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
    
typedef struct PList {
    CALENDAR cal;
    unsigned long int id;
    unsigned short int course;
    unsigned char grade;
    struct PList *next;
} PLIST;    

typedef struct ResList {
    PLIST *elem;
    struct ResList *next;
} RESLIST;

#ifdef	__cplusplus
}
#endif

#endif	/* DATATYPE_H */


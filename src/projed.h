#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "config.h"
#include "datatype.h"

#ifndef PROJED_H
#define PROJED_H

#ifdef  __cplusplus
extern "C" {
#endif

// dataobj.c
NOTE *appendNote(NOTE *head, PERSON *person, unsigned char grade);
int PersonElemHeight(PERSON *elem);
PERSON *PersonNewElem(unsigned long int val);
PERSON *PersonRightRotate(PERSON *y);
PERSON *PersonLeftRotate(PERSON *x);
int PersonGetBalance(PERSON *node);
PERSON *insertPerson(PERSON *node, COURSE **courses, TEMP data);
RESLIST *ResAppend(RESLIST *head, PERSON *obj);
RESLIST *ResClearAll(RESLIST *head);
long int ResCount(RESLIST *head);
void ResPrint(RESLIST *head);
RESLIST *getTail(RESLIST *elem);
RESLIST *partition(RESLIST *head, RESLIST *end, RESLIST **newHead, RESLIST **newEnd);
RESLIST *quickSort(RESLIST *head, RESLIST *end);
QUERY *appendCriteria(QUERY *head, unsigned short int course, unsigned char grade, char oper);
QUERY *findBest(QUERY *head);


// file.c
int fileExists();
PERSON *fileRead(FILE *fp, char *filename, PERSON *persons, COURSE **courses, unsigned char *cc);


// utils.c
void toUpperCase(char *value);
void clearScreen();
void doPause();
int checkQueryFormat(char *query);
int validaRegisto(NOTE **course_array, unsigned short int course_index, QUERY *pesquisa, QUERY *best);
int peformQuery(COURSE **courses, char *query, int verbose);

#ifdef  __cplusplus
}
#endif

#endif  /* PROJED_H */
/* 
 * File:   dataobj.h
 * Author: hugo
 *
 * Created on 23 de Setembro de 2014, 19:27
 */

#ifndef DATAOBJ_H
#define	DATAOBJ_H

#ifdef	__cplusplus
extern "C" {
#endif
    
#include <stdio.h>
#include <stdlib.h>
#include "config.h"
#include "datatype.h"
    
int max(int a, int b);

// Binary Tree methods
int PersonElemHeight(PERSON *elem);
PERSON *PersonNewElem(unsigned long int val);
PERSON *PersonRightRotate(PERSON *y);
PERSON *PersonLeftRotate(PERSON *x);
int PersonGetBalance(PERSON *node);
PERSON *insertPerson(PERSON *node, COURSE **courses, TEMP data);

// Result List methods
RESLIST *ResAppend(RESLIST *head, PERSON *obj);
RESLIST *ResClearAll(RESLIST *head);
long int ResCount(RESLIST *head);
void ResPrint(RESLIST *head);
RESLIST *getTail(RESLIST *elem);
RESLIST *partition(RESLIST *head, RESLIST *end, RESLIST **newHead, RESLIST **newEnd);
RESLIST *quickSort(RESLIST *head, RESLIST *end);

// Query
QUERY *appendCriteria(QUERY *head, unsigned short int course, unsigned char grade, char oper);
QUERY *findBest(QUERY *head);

#ifdef	__cplusplus
}
#endif

#endif	/* DATAOBJ_H */


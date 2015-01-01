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

/*
// Linked List methods
BLIST *BLISTMemAlloc();
BLIST *BLISTCreate(BLIST *);
BLIST *BLISTAppend(BLIST *, CALENDAR, unsigned int);
BLIST *BLISTPrint(BLIST *);
BLIST *BLISTSwap(BLIST *, BLIST *);
BLIST *BLISTMove(BLIST *);
BLIST *BLISTSort(BLIST *);
BLIST *BLISTExtend(BLIST *, BLIST *);

// Hashtable methods - Notas unsigned char
HASH *HashMemAlloc();
HASH *HashCreate(int size);
unsigned char HashFunction(HASH *hashtable, unsigned char key);
BLIST *HashLookUp(HASH *hashtable, unsigned char val);
int HashAdd(HASH *hashtable, unsigned char val);
 * */

// Binary Tree methods - Cursos unsigned short int
int PersonElemHeight(PERSON *elem);
PERSON *PersonNewElem(unsigned long int val);
PERSON *PersonRightRotate(PERSON *y);
PERSON *PersonLeftRotate(PERSON *x);
int PersonGetBalance(PERSON *node);
PERSON *insertPerson(PERSON *node, COURSE **courses, TEMP data);
PERSON *CNodeLookUp(PERSON *node, unsigned short int val);
PERSON *CNodePrint(PERSON *node);

// Result List methods
RESLIST *ResMemAlloc();
RESLIST *ResAppend(RESLIST *head, PERSON *obj);
RESLIST *ResFind(RESLIST *head, PERSON *obj);
RESLIST *ResCopy(RESLIST *output, RESLIST *nlist);
RESLIST *ResClearAll(RESLIST *head);
long int ResCount(RESLIST *head);
void ResPrint(RESLIST *head);
RESLIST *removeDuplicates(RESLIST *);
RESLIST *getTail(RESLIST *elem);
RESLIST *partition(RESLIST *head, RESLIST *end, RESLIST **newHead, RESLIST **newEnd);
RESLIST *quickSort(RESLIST *head, RESLIST *end);

// Query
QUERY *appendCriteria(QUERY *head, unsigned short int course, unsigned char grade, char operator);
QUERY *findBest(QUERY *head);
QUERY *clearSearch(QUERY *head);

#ifdef	__cplusplus
}
#endif

#endif	/* DATAOBJ_H */


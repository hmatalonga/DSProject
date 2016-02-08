/* 
 * File:   dataobj.h
 * Author: hugo
 *
 * Created on 23 de Setembro de 2014, 19:27
 * 
 * Biblioteca que contém funções de manipulações das estruturas de dados
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

// Linked List methods
PLIST *PLISTMemAlloc();
PLIST *PLISTAppend(PLIST *, PLIST *);

// Result List methods
RESLIST *ResMemAlloc();
RESLIST *ResAppend(RESLIST *, PLIST *);
RESLIST *ResFind(RESLIST *, PLIST *);
RESLIST *ResCopy(RESLIST *, RESLIST *);
RESLIST *ResClearAll(RESLIST *);
long int ResCount(RESLIST *);
void ResPrint(RESLIST *);
RESLIST *ResSwap(RESLIST *, RESLIST *);
RESLIST *ResSort(RESLIST *);
RESLIST *removeDuplicates(RESLIST *);
RESLIST *getTail(RESLIST *elem);
RESLIST *partition(RESLIST *head, RESLIST *end, RESLIST **newHead, RESLIST **newEnd);
RESLIST *quickSort(RESLIST *head, RESLIST *end);

#ifdef	__cplusplus
}
#endif

#endif	/* DATAOBJ_H */


/* 
 * File:   utils.h
 * Author: hugo
 *
 * Created on 17 de Setembro de 2014, 17:07
 */

#ifndef UTILS_H
#define	UTILS_H

#ifdef	__cplusplus
extern "C" {
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "config.h"
#include "datatype.h"
#include "dataobj.h"
 
void toUpperCase(char *value);
void clearScreen();
void doPause();
int checkQueryFormat(char *query);
void peformQuery(PLIST *dataset, char *query, int verbose);


#ifdef	__cplusplus
}
#endif

#endif	/* UTILS_H */


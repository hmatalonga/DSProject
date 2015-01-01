/* 
 * File:   file.h
 * Author: hugo
 *
 * Created on 17 de Setembro de 2014, 17:08
 */

#ifndef FILE_H
#define	FILE_H

#ifdef	__cplusplus
extern "C" {
#endif
    
#include <stdio.h>
#include <stdlib.h>
#include "config.h"
#include "dataobj.h"    

int fileExists();
PERSON *fileRead(FILE *fp, char *filename, PERSON *persons, COURSE **courses, unsigned char *cc);

#ifdef	__cplusplus
}
#endif

#endif	/* FILE_H */


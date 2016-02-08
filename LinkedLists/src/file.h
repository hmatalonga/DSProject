/* 
 * File:   file.h
 * Author: hugo
 *
 * Created on 17 de Setembro de 2014, 17:08
 * 
 * Biblioteca que contém funções de controlo de ficheiros
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

int fileExists(char *filename);
PLIST *fileRead(FILE *fp, char *filename, PLIST *dataset);

#ifdef	__cplusplus
}
#endif

#endif	/* FILE_H */


#ifndef __CSV_H
#define __CSV_H

#include "stdio.h"
#include "stdlib.h"
#include "eprintf.h"

#define NOMEM -2

static char* line = NULL;
static char* sline = NULL;
static int maxline = 0;
static char** field = NULL;
static int maxfield = 0;
static int nfield = 0;
static char fieldsep[] = ",";

char* csvgetline(FILE* f);
char* csvfield(int n);
int csvnfield(void);

#endif
#ifndef __EPRINTF_H
#define __EPRINTF_H

static char* name = NULL;

void eprintf(const char *fmt, ...);

void weprintf(const char *fmt, ...);

char* estrdup(const char *s);

void* emalloc(size_t n);

void* erealloc(void* p, size_t n);

char* program(void);

void setprogram(const char* p);
#endif
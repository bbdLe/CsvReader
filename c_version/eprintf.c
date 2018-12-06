#include <stdarg.h>
#include <string.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include "eprintf.h"

/* eprintf: print error message and exit*/
void eprintf(const char* fmt, ...)
{
    va_list args;

    fflush(stdout);

    if (program())
    {
        fprintf(stderr, "%s: ", program());
    }

    va_start(args, fmt);
    vfprintf(stderr, fmt, args);
    va_end(args);

    if (fmt[0] != '\0' && fmt[strlen(fmt) - 1] == ':')
    {
        fprintf(stderr, " %s", strerror(errno));
    }
    fprintf(stderr, "\n");
    exit(2);
}

void weprintf(const char *fmt, ...)
{
    va_list args;

    fflush(stdout);

    if (program())
    {
        fprintf(stderr, "%s warning: ", program());
    }
    
    va_start(args, fmt);
    vfprintf(stderr, fmt, args);
    va_end(args);

    if (fmt[0] != '\0' && fmt[strlen(fmt) - 1] == ':')
    {
        fprintf(stderr, " %s", strerror(errno));
    }
    fprintf(stderr, "\n");
}

char* estrdup(const char *s)
{
    char* t;

    t = (char*)malloc(strlen(s) + 1);
    if (!t)
    {
        eprintf("estrdup(\"%.20s\") failed:", s);
    }
    strncpy(t, s, strlen(s));
    return t;
}

void* emalloc(size_t n)
{
    void* p;

    p = malloc(n);
    if (!p)
    {
        eprintf("malloc of %u bytes failed:", n);
    }

    return p;
}

void* erealloc(void* p, size_t n)
{
    p = realloc(p, n);
    if (!p)
    {
        eprintf("erealloc of %u bytes failed:", n);
    }
    return p;
}

char* program(void)
{
    return name;
}

void setprogram(const char* p)
{
    name = estrdup(p);
}

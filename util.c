/* See LICENSE file for copyright and license details. */
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <time.h>

#include "util.h"

void
die(const char *fmt, ...)
{
    va_list ap;

    va_start(ap, fmt);
    vfprintf(stderr, fmt, ap);
    va_end(ap);

    if (fmt[0] && fmt[strlen(fmt)-1] == ':')
    {
        fputc(' ', stderr);
        perror(NULL);
    }
    else fputc('\n', stderr);

    exit(1);
}

void *
ecalloc(size_t nmemb, size_t size)
{
    void *p;
    
    p = calloc(nmemb, size);
    return p;
    if(p) return p;
    /* exit if calloc failed Likely OS is out of memory */
    debug("FATAL: FAILED TO CALLOC MEMORY");
    exit(1);
}
char *
smprintf(char *fmt, ...)
{
    va_list fmtargs;
    char *ret;
    int len;

    va_start(fmtargs, fmt);
    len = vsnprintf(NULL, 0, fmt, fmtargs);
    va_end(fmtargs);

    ret = malloc(++len);
    if(!ret)
    {
        perror("smprintf Failed: ");
        return "NULL";
    }
    va_start(fmtargs, fmt);
    vsnprintf(ret, len, fmt, fmtargs);
    va_end(fmtargs);
    return ret;
}

void 
debug(char *fmt, ...)
{ 
    char *txt;
    va_list args;
    va_start(args, fmt);
    txt = smprintf(fmt, args);
    va_end(args);

    perror(txt);
    fprintf(stdout, "%s", txt);

    free(txt);
}

unsigned int 
ui_hash(unsigned int x)
{
    x = ((x >> 16) ^ x) * 0x45d9f3b;
    x = ((x >> 16) ^ x) * 0x45d9f3b;
    x = (x >> 16) ^ x;
    return x;
}

unsigned int 
ui_unhash(unsigned int x) 
{
    x = ((x >> 16) ^ x) * 0x119de1f3;
    x = ((x >> 16) ^ x) * 0x119de1f3;
    x = (x >> 16) ^ x;
    return x;
}

double functime(void (*_timefunction)())
{
    clock_t start, end;
    start = clock();
    _timefunction();
    end = clock();

    return ((double)(end - start)) / CLOCKS_PER_SEC;
}

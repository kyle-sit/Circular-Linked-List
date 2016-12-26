#ifndef MYLIB_H
#define MYLIB_H

void clrbuf (int);
long decin (void);
void decout (long);
void hexout (unsigned long);
void newline (void);
long writeline (char *);

#ifndef TRUE
#define TRUE 1
#endif

#ifndef FALSE
#define FALSE 0
#endif

#ifdef NULL
#undef NULL
#define NULL 0
#endif

#endif

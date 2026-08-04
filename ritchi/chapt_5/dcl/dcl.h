#ifndef DCL_H
#define DCL_H

#define MAXTOKEN 100

enum { NAME, PARENS, BRACKETS };
extern int tokentype;
extern char token[MAXTOKEN];
extern char name[MAXTOKEN];
extern char datatype[MAXTOKEN];
extern char out[1000];

void dcl(void);
void dirdcl(void);

int gettoken(void);

#endif

%{
#include <stdio.h>
#include <stdlib.h>
#include "fb3-1.h"
#include <string.h>

char c[100];
char d[100];
char e[100];
char f[100];
char g[100];
char h[100];

char i[100];
char j[100];



%}
%union {
	struct ast *a;
	double d;
}

/* declare tokens */
%token <d> NUMBER
%token EOL

%type <a> exp factor term

%%
calclist: /* nothing */{printf("Regra 1\n");strcpy(j,"calclist[vazio]");printf("%s\n",j);}
| calclist exp EOL {
	sprintf(g,"[calclist[%s %s EOL]]",j,f);printf("%s\n",g);
	printf("Regra 2\n");
	printf("= %4.4g\n", eval($2));
	treefree($2);
	printf("> ");
  }
| calclist EOL { printf("> "); {printf("Regra 3\n");}} /* blank line or a comment */
;

exp: factor	{printf("Regra 4");sprintf(e,"exp%s",c);printf("%s\n",e);}
| exp '+' factor { $$ = newast('+', $1,$3);printf("Regra 5");sprintf(f," exp[%s + %s]",e,c);printf("%s\n",f);}
| exp '-' factor { $$ = newast('-', $1,$3);printf("Regra 6");sprintf(f," exp[%s - %s]",e,c);printf("%s\n",f);}
;

factor: term	{printf("Regra 7");sprintf(c,"[factor%s]",d);printf("%s\n",c);}
| factor '*' term { $$ = newast('*', $1,$3);printf("Regra 8\n");sprintf(f," exp[%s * %s]",c,d);printf("%s\n",f); }
| factor '/' term { $$ = newast('/', $1,$3);printf("Regra 9\n");sprintf(f," exp[%s / %s]",c,d);printf("%s\n",f);}
;

term: NUMBER { printf("Regra 10\n");$$ = newnum($1);strcpy(d,"[term[NUMBER]]");}
| '|' term { $$ = newast('|', $2, NULL); printf("Regra 11\n");}
| '(' exp ')' { $$ = $2; printf("Regra 12\n");}
| '-' term { $$ = newast('M', $2, NULL); printf("Regra 13\n");}
;



%%

# include <stdio.h>
# include <stdlib.h>
# include <stdarg.h>
# include "fb3-1.h"

struct ast *newast(int nodetype, struct ast *l, struct ast *r){
	struct ast *a = malloc(sizeof(struct ast));

	if(!a) {
		yyerror("out of space");
		exit(0);
	}
	a->nodetype = nodetype;
	a->l = l;
	a->r = r;
	//printf("%c\n", a->nodetype);
	//printf("%c\n", a->l->nodetype);
	//printf("%c\n", a->r->nodetype);
	return a;
}

struct ast *newnum(double d){
	struct numval *b = malloc(sizeof(struct numval));
		
	if(!b) {
		yyerror("out of space");
		exit(0);
	}
	b->nodetype = 'K';
	b->number = d;
	return (struct ast *) b;
}

double eval(struct ast *a){
	double v; //calculated value of this subtree
	
	switch(a->nodetype) {
		case 'K': v = ((struct numval *)a)->number; break;
		case '+': v = eval(a->l) + eval(a->r); break;
		case '-': v = eval(a->l) - eval(a->r); break;
		case '*': v = eval(a->l) * eval(a->r); break;
		case '/': v = eval(a->l) / eval(a->r); break;
		case '|': v = eval(a->l); if(v < 0) v = -v; break;
		case 'M': v = -eval(a->l); break;
		default: printf("internal error: bad node %c\n", a->nodetype);
	}
	return v;
}

void treefree(struct ast *a){
	switch(a->nodetype) {
			/* two subtrees */
		case '+':
		case '-':
		case '*':
		case '/':

			//treefree(a->r);
			//printf("valor no nó: %c\n", a->nodetype);
			//printf("valor no nó: %d\n", a->r->nodetype);	
			//printf("valor no nó: %c\n", a->l->nodetype);	
			/* one subtree */
		case '|':
		case 'M':
			//treefree(a->l);
			//printf("valor no nó M");
			/* no subtree */
		case 'K':
			free(a);
			break;
		default: printf("internal error: free bad node %c\n", a->nodetype);
	}
}

void yyerror(char *s, ...){
	va_list ap;
	va_start(ap, s);

	fprintf(stderr, "%d: error: ", yylineno);
	fprintf(stderr, s, ap);
	fprintf(stderr, "\n");
}

void teste(){
	printf("error: ");
}

int main() {

	return yyparse();
}











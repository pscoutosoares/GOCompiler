%{
#ifndef YYSTYPE
# define YYSTYPE long int
#endif
#include <stdlib.h>
#include <string.h>
#include "tabelaNumero.h"
void yyerror(char *c);
#include "y.tab.h"


%}

delim	[ \t\n]
ws	{delim}+
letra	[a-z|A-Z|_] 
numero	[0-9]
identificador	{letra}({letra}|{numero})*
print	fmt.Println
scan 	fmt.Scanf

%%
{ws}	{}
{numero}+	   { 
	valor v;
	v.dval = atoi(yytext);
	/* o "uintptr_t" livra os warning de conversão pra ponteiro */
	yylval = (long int) criar_numero(v, INT_type); 
	return NUMBER;
}

{numero}+"."{numero}+	  { 
	valor v;
	v.fval = atof(yytext);
	yylval = (long int) criar_numero(v, FLOAT_type);
	return NUMBER;
}

int	{	
	yylval = INT_type;
	return TYPE;
}
float64 {
	yylval = FLOAT_type;
	return TYPE;
}
var {
	return VAR;
}
if {
	return IF;
}	
else {
	return ELSE;
}
for {
	return FOR;
}
{print} {	
	return PRINT;
}
{scan} {
	return SCAN;
}
{identificador}	{
	/*O identificador tem que ficar mais em baixo por ser mais generico */
	yylval = (long int) strdup(yytext);
	return ID;
}

"<"		{return LT;}
"<="	{return LE;}
"=="	{return EQ;}
"<>"	{return NE;}
">"		{return GT;}
">="	{return GE;}

[-+*;=\/\(\){}]	{return *yytext; }

[ \t\n] 	; /* skip whitespace */

. 	yyerror("invalid character");

%%


int yywrap(void) {
return 1;
}

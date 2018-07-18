%{
#include <stdlib.h>
void yyerror(char *);
#include "y.tab.h"
%}

delim	[ \t\n]
ws	{delim}+
letra	[a-z|A-Z|_] 
digito	[0-9]
numero	{digito}+(\.{digito}+)?
identificador	{letra}({letra}|{digito})*

%%
{ws}	{}
{numero}+	{ 
	yylval = atoi(yytext);
	return NUMBER;
}
int	{	
	yylval = INT;
	return TYPE;
}
float {
	yylval = FLOAT;
	return TYPE;
}
var{
	return VAR;
}
func {
	return FUNC;
}
PRINT {	
	return PRINT; 
}
SCAN {
	return SCAN
}
{identificador}	{
	yylval = (int) strdup(yytext);
	return ID;
}

if {

}	
else {

}

for {

}

"<"		{}
"<="	{}
"="		{}
"<>"	{}
">"		{}
">="	{}





[-+*;=\/\(\)]	{return *yytext; }  // removi \n



. 	yyerror("invalid character");

%%


int yywrap(void) {
return 1;
}

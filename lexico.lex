%{
#include <stdlib.h>
#include "y.tab.h"
void yyerror(char *c);

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
	//yylval = atoi(yytext);
	return NUMBER;
}
int	{	
	//yylval = INT;
	return TYPE;
}
float {
	//yylval = FLOAT;
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
'fmt.Println' {	
	return PRINT; 
}
'fmt.Scanf' {
	return SCAN;
}
{identificador}	{
	//yylval = (int) strdup(yytext);
	return ID;
}

"<"		{return LT;}
"<="	{return LE;}
"="		{return EQ;}
"<>"	{return NE;}
">"		{return GT;}
">="	{return GE;}

[-+*=;\{\}\/\(\)]	{return *yytext; }  // removi \n
. 	yyerror("invalid character");

%%


int yywrap(void) {
return 1;
}

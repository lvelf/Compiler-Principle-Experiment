%option yylineno
%{
#include "string.h"
#include "def.h"


int yycolumn=1;
#define YY_USER_ACTION    \
	yylloc.first_line=yylloc.last_line=yylineno; \
	yylloc.first_column=yycolumn;\
	yylloc.last_column=yycolumn+yyleng-1;\
	yycolumn+=yyleng;
		   	   



#include "parser.tab.h"

#define act(x) \
{ \
    strcpy(yylval.type_id, yytext);  \
    return x; \
}

%}



ID   [A-Za-z][A-Za-z0-9]*  
INT    [0-9]+
FLOAT ([0-9]*\.[0-9]+)|([0-9]+\.)

WHILE while
IF if
ELSE else
SCAN scan
//OP (\+)|-|(\*)|(\/)|<|>|=|(<=)|(>=)|(==)|(!=)

GT >
LT < 
NE !=
GE >=
LE <=
EQ == 
ASSIGNOP =

PLUS +
MINUS - 
STAR * 
DIV \/


LC \{
RC \}
LP \(
RP \)



PRINT print

SEMI ;
delim [" "\n\t]

%%
{WHILE} act(WHILE)
{IF} act(IF)
{ELSE} act(ELSE)

{SCAN} act(SCAN)
{PRINT} act(PRINT)

//{OP} act(OP)

{LC} act(LC)
{RC} act(RC)
{LP} act(LP)
{RP} act(RP)
{SEMI} act(SEMI)
{delim} {}
{ID} act(ID)

{GT} act(GT)
{LT} act(LT)
{NE} act(NE)
{GE} act(GE)
{LE} act(LE)
{EQ} act(EQ) 
{ASSIGNOP} act(ASSIGNOP)

{PLUS} act(PLUS)
{MINUS} act(MINUS)
{STAR} act(STAR)
{DIV} act(DIV)

{INT} {
    int a = 0; 
    for (int i = 0; yytext[i] != '\0'; i++) {
        a = a * 10 + yytext[i] - '0';
    }
    yylval.type_int = a;
    return INT;
}
{FLOAT} {
    float a = 0;
    int flag = 0;
    float b = 1;
    for (int i = 0; yytext[i] != '\0'; i++) {
        if (yytext[i] == '.') {
            flag = 1;
            continue;
        }
        if (flag == 0) {
            a = a * 10 + yytext[i] - '0';
        } else {
            b = b * 0.1;
            a = a + b * (yytext[i] - '0');
        }   
    }
    yylval.type_float = a;
    return FLOAT;
}
. {printf("\n<error character '%s' in line %d> ", yytext, yylineno);}
%%

int yywrap()
{
return 1;
}


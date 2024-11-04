%option  yylineno
/**************以下为定义段******************/
%{
#include "stdio.h"
#include "string.h"
#define no_int 1
#define no_while 2
#define no_if 3
#define no_else 4
#define no_return 5
#define no_id 50
#define no_intconst 51
#define no_plus 60
#define no_minus 61
#define no_multi 62
#define no_divide 63
#define no_assign 64
#define no_l 65
#define no_le 66
#define no_g 67
#define no_ge 68
#define no_eq 69
#define no_neq 70
#define no_begin 71
#define no_end 72
#define no_lbracket 73
#define no_rbracket 74
#define no_comma 75
#define no_semi 76

#define no(x) no_##x
#define space(x) (no(x) == 50)? "\"" : "" 
#define str(x) (no(x) == 50 || no(x) == 51)? yytext :"-" 
#define act(x) {printf("(%d,%s%s%s) ", no(x), space(x), str(x), space(x));}

int statue;
char name[20];

int val_int=0;
%}

id   [A-Za-z][A-Za-z0-9]*  
intconst    [0-9]+

/**************下面为需要填写的规则段******************/
int int
while while
if if
else else
return return 
plus \+
minus - 
multi \*
divide \/
assign =
l <
le <= 
g >
ge >= 
eq ==
neq !=
begin \{
end \}
lbracket \(
rbracket \)
comma ,
semi ;
delim [" "\n\t]
%%
{intconst} act(intconst)
{int} act(int)
{while} act(while)
{if} act(if)
{else} act(else)
{return} act(return) 

{id} act(id)
{plus} act(plus)
{minus} act(minus)
{multi} act(multi)
{divide} act(divide)
{assign} act(assign)
{l} act(l)
{le} act(le)
{g} act(g)
{ge} act(ge)
{eq} act(eq)
{neq} act(neq)
{begin} act(begin)
{end} act(end)
{lbracket} act(lbracket)
{rbracket} act(rbracket)
{comma} act(comma)
{semi} act(semi)
{delim} {}
. {printf("\n<error character '%s' in line %d> ", yytext, yylineno);}
%%


/**************以下为用户子程序段******************/
int main(int argc,char *argv[])
{
yylineno=1;      //行序号变量，每次遇到\n后会自动加1
yyin=fopen(argv[1],"r");
if (!yyin) return 0;
while (yylex());
return 0;
}
int yywrap() {
    return 1;
}


%error-verbose
%locations
%token ID INT FLOAT IF ELSE WHILE LC RC SEMI SCAN PRINT LP RP 
%token OP1 OP2 OP3 OP4

%{
#include "stdio.h"
#include "math.h"
#include "string.h"
#include "def.h"
extern int yylineno;
extern char *yytext;
extern FILE *yyin;
void yyerror(const char* fmt, ...);
int yylex();

YYLVAL root;


%}

/*********************请在下面完成parser.y*******************/

%%


program :
    StmList {
        $$.type_node = create_node1(PROGRAM, ($1));
        root = $$;
    }

StmList:
    { $$.type_node = create_node1(STMLIST, e);}  | Stmt StmList {
        $$.type_node = create_node2(STMLIST, ($1), ($2));
    }

CompSt : 
    LC StmList RC {
        $$.type_node = create_node1(COMPST, ($2));
    }

Stmt :
    MatchStmt
    | OpenStmt

MatchStmt : 
    Exp4 SEMI    //表达式语句    
    {
        $$.type_node = create_node1(EXPSTMT, ($1));
    }
    | CompSt  //表达式语句
    {  $$.type_node = create_node1(COMPSTMT, ($1)); } 
    | SCAN ID SEMI     //表达式语句    
    { $$.type_node = create_node1(SCANSTMT, ($2));}
    | PRINT Exp4 SEMI     //输出语句  
    {
        $$.type_node = create_node1(PRINTSTMT, ($2));
    } 
    | WHILE LP Exp4 RP Stmt    //循环语句
    {
        $$.type_node = create_node2(WHILESTMT, ($3), ($5));
    }
    | IF LP Exp4 RP MatchStmt ELSE MatchStmt
    {
        $$.type_node = create_node3(IFELSESTMT, ($3), ($5), ($7));
    } 

OpenStmt: IF LP Exp4 RP Stmt    //条件语句
    {
        $$.type_node = create_node2(IFSTMT, ($3), ($5));
    } | IF LP Exp4 RP MatchStmt ELSE OpenStmt
    {
        $$.type_node = create_node3(IFELSESTMT, ($3), ($5), ($7));
    } 

Exp0 : 
    INT {
        $$.type_node = create_node1(INTEXP, ($1));
    } | FLOAT {
        $$.type_node = create_node1(FLOATEXP, ($1));
    }| ID {
        $$.type_node = create_node1(IDEXP, ($1));
    }   //整型常量，浮点常量、变量   
    | LP Exp4 RP  {
        $$.type_node = create_node1(PEXP, ($2));
    } | OP2 Exp0  {
        $$.type_node = create_node2(OPEXP, ($1), ($2));
    }   //单目运算

Exp1:
    Exp0 
    | Exp1 OP1 Exp0 {
        $$.type_node = create_node3(OP2EXP, ($1), ($2), ($3));
    }       // 二目运算


Exp2 :
    Exp1
    | Exp2 OP2 Exp1 {
        $$.type_node = create_node3(OP2EXP, ($1), ($2), ($3));
    }       // 二目运算
    

Exp3:
    Exp2
    | Exp3 OP3 Exp2 {
        $$.type_node = create_node3(OP2EXP, ($1), ($2), ($3));
    }       // 二目运算

Exp4:
    Exp3
    | Exp4 OP4 Exp3 {
        $$.type_node = create_node3(OP2EXP, ($1), ($2), ($3));
    }       // 二目运算

/************************************************************/
%%
Node node_e;

int main(int argc, char *argv[]){
    e.type_node = &node_e;
    e.type_node->type = EMPTY;
	yyin=fopen(argv[1],"r");
	if (!yyin) return 0;
	yylineno=1;
	yyparse();
    output(root);
	return 0;
}

#include<stdarg.h>
void yyerror(const char* fmt, ...)
{
    va_list ap;
    va_start(ap, fmt);
    fprintf(stderr, "Grammar Error at Line %d Column %d: ", yylloc.first_line,yylloc.first_column);
    vfprintf(stderr, fmt, ap);
    fprintf(stderr, ".\n");
}
	


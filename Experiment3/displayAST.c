#include "stdio.h"
#include "parser.tab.h"
#include "def.h"
#include "stdlib.h"

/****************请在下面填写代码显示语法树*************/


YYLVAL e;

Node* create_node(int type, YYLVAL a, YYLVAL b, YYLVAL c) {
    Node* ret = (Node *)malloc(sizeof(Node));
    ret->type = type;
    ret->a = a;
    ret->b = b;
    ret->c = c;
    return ret;
}

YYLVAL* dupval(YYLVAL val) {
    YYLVAL* ret = (YYLVAL*)malloc(sizeof(YYLVAL));
    *ret = val;
    return ret;
}

int output_step = 0;
#define LL output_step++
#define OO for(int i=0;i<output_step;i++) printf("    ")
#define LO LL;OO
#define RR output_step--

void output(YYLVAL node) {
    //printf("starting output %d\n", node.type_node->type);
    switch(node.type_node->type) {
        case PROGRAM:
            output(node.type_node->a);
            break;

        case STMLIST:
            output(node.type_node->a);
            output(node.type_node->b);
            break;
        
        case COMPST: 
            output(node.type_node->a);
            break;

        case EXPSTMT:
            OO;printf("表达式语句：\n");
            LL;output(node.type_node->a);RR;
            break;
        
        case COMPSTMT:
            output(node.type_node->a);
            break;

        case SCANSTMT:
            OO;printf("输入变量：%s\n", node.type_node->a.type_id);
            break;
        
        case PRINTSTMT:
            OO;printf("输出表达式:\n");
            LL;output(node.type_node->a);RR;
            break;
        
        case IFSTMT:
            OO;printf("条件语句(if_then)：\n");
            LO;printf("条件：\n");
            LL;output(node.type_node->a);RR;
            LO;printf("if子句：\n");
            LL;output(node.type_node->b);RR;
            RR;
            break;

        case IFELSESTMT:
            OO;printf("条件语句(if_then_else)：\n");
            LO;printf("条件：\n");
            LL;output(node.type_node->a);RR;
            OO;printf("if子句：\n");
            LL;output(node.type_node->b);RR;
            OO;printf("else子句：\n");
            LL;output(node.type_node->c);RR;RR;
            break;

        case WHILESTMT:
            OO;printf("循环语句：\n");
            LO;printf("条件：\n");
            LL;output(node.type_node->a);RR;
            OO;printf("循环体：\n");
            LL;output(node.type_node->b);RR;RR;
            break;
    

        case INTEXP:
            OO;printf("整型常量：%d\n", node.type_node->a.type_int);
            break;
        case FLOATEXP:
            OO;printf("浮点常量：%.6f\n", node.type_node->a.type_float);
            break;
        case IDEXP: 
            OO;printf("变量：%s\n", (node.type_node->a.type_id));
            break;
        
        case OP2EXP:
            OO;printf("%s\n", node.type_node->b.type_id);
            LL;output(node.type_node->a);
            output(node.type_node->c);RR;
            break;
        
        case OPEXP:
            OO;printf("单目%s\n", node.type_node->a.type_id);
            LL;output(node.type_node->b);RR;
            break;
        case PEXP:
            output(node.type_node->a);
            break;
        case EMPTY:
            break;
    }   
}





/*****************************************************/
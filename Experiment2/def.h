/***********定义结点类型和给出函数说明*********/
#ifndef __DEF_H__
#define __DEF_H__

struct Node;

#define PROGRAM 1
#define STMLIST 2

#define COMPST 3

#define EXPSTMT 101
#define COMPSTMT 102
#define SCANSTMT 103
#define PRINTSTMT 104
#define IFSTMT 105
#define IFELSESTMT 106
#define WHILESTMT 107


#define INTEXP 201
#define FLOATEXP 202
#define IDEXP 203
#define OP2EXP 204
#define OPEXP 205
#define PEXP 206

#define EMPTY 666




typedef struct node_t Node;

typedef union {
	int type_int;
	float type_float;
	char type_id[32];
    struct node_t* type_node;
} YYLVAL;

#define YYSTYPE YYLVAL
extern YYLVAL e;

struct node_t{
    int type; 
    YYLVAL a, b, c;
};

Node* create_node(int type, YYLVAL a, YYLVAL b, YYLVAL c);

#define create_node1(type, a) create_node(type, a, e, e);
#define create_node2(type, a, b) create_node(type, a, b, e);
#define create_node3(type, a, b, c) create_node(type, a, b, c);

extern YYLVAL e;
void output(YYLVAL node);
YYLVAL* dupval(YYLVAL val);
#endif 
/*********************************************/
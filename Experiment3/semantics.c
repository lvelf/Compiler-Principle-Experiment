#include "stdio.h"
#include "parser.tab.h"
#include "def.h"
#include "stdlib.h"
#include "string.h"
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

Value vo(){
    Value v;
    v.type = -1;
    v.Lvalue = -1;
    return v;
}
Value z(){
    Value z;
    z.type = 0;
    z.value.type_int = 0;
    z.Lvalue = -1;
    return z;
}

int tableCnt = 0;

Data table[MaxTable];

Value get(char* str){
    for(int i=0; i<tableCnt; i++){
        if(strcmp(str,table[i].identifier) == 0){
        
            return table[i].value;
        }
    }
    return vo();
}

Value insert(char *str, Value value){
    strcpy( table[tableCnt].identifier, str);
    table[tableCnt].value = value;
    table[tableCnt].value.Lvalue = tableCnt;
    return table[tableCnt++].value;
}

Value update(char *str, Value value){
    if(get(str).type<0){
        return insert(str, value);
    } else {
        value.Lvalue = get(str).Lvalue; 
        table[get(str).Lvalue].value = value;
        return value;
    }
}

Value do_op2(char* op,Value a, Value b){
    if (b.type < 0 && b.Lvalue >= 0) {
        printf("第2行的符号%s未定义值\n", table[b.Lvalue].identifier);
        return vo();
    }


    if(strcmp(op,"=") == 0){
        if(a.Lvalue >= 0){
            table[a.Lvalue].value.type = b.type;
            table[a.Lvalue].value.value = b.value; 
        }else{
            printf("lval err\n");
        }
        return b;
    }

    if (a.type < 0 && a.Lvalue >= 0) {
        printf("第2行的符号%s未定义值\n", table[a.Lvalue].identifier);
        return vo();
    }

    Value c;
    if (a.type == 0 && b.type == 0){
        c.type = 0;
    } else {
        if(a.type == 0) {
            a.type = 1;
            a.value.type_float = a.value.type_int;
        }
        if(b.type == 0) {
            b.type = 1;
            b.value.type_float = b.value.type_int;
        }
        c.type = 1;
    }
    c.Lvalue = -1;
    if(strcmp(op,"+") == 0){
        if(c.type == 0) c.value.type_int = a.value.type_int + b.value.type_int;
        else c.value.type_float = a.value.type_float + b.value.type_float;
    }
    if(strcmp(op,"-") == 0){
        if(c.type == 0) c.value.type_int = a.value.type_int - b.value.type_int;
        else c.value.type_float = a.value.type_float - b.value.type_float;
    }
    if(strcmp(op,"*") == 0){
        if(c.type == 0) c.value.type_int = a.value.type_int * b.value.type_int;
        else c.value.type_float = a.value.type_float * b.value.type_float;
    }
    if(strcmp(op,"/") == 0){
        if(c.type == 0) c.value.type_int = a.value.type_int / b.value.type_int;
        else c.value.type_float = a.value.type_float / b.value.type_float;
    }
    if(strcmp(op,">") == 0){
        if(c.type == 0) c.value.type_int = a.value.type_int > b.value.type_int;
        else c.value.type_int = a.value.type_float > b.value.type_float;
        c.type = 0;
    }
    if(strcmp(op,">=") == 0){
        if(c.type == 0) c.value.type_int = a.value.type_int >= b.value.type_int;
        else c.value.type_int = a.value.type_float >= b.value.type_float;
        c.type = 0;
    }
    if(strcmp(op,"<") == 0){
        if(c.type == 0) c.value.type_int = a.value.type_int < b.value.type_int;
        else c.value.type_int = a.value.type_float < b.value.type_float;
        c.type = 0;
    }
    if(strcmp(op,"<=") == 0){
        if(c.type == 0) c.value.type_int = a.value.type_int <= b.value.type_int;
        else c.value.type_int = a.value.type_float <= b.value.type_float;
        c.type = 0;
    }
    if(strcmp(op,"==") == 0){
        if(c.type == 0) c.value.type_int = a.value.type_int == b.value.type_int;
        else c.value.type_int = a.value.type_float == b.value.type_float;
        c.type = 0;
    }
    if(strcmp(op,"!=") == 0){
        if(c.type == 0) c.value.type_int = a.value.type_int != b.value.type_int;
        else c.value.type_int = a.value.type_float != b.value.type_float;
        c.type = 0;
    }    
    return c;
}

Value do_op1(char* op, Value b){
    return do_op2(op, z(), b);
}

Value read(){
    Value vv;
    char buf[MaxTable];
    scanf("%s",buf);
    int fp = 0;
    for(int i=0;buf[i]!='\0';i++){
        if(buf[i]=='.') fp=1;
    }
    if(fp) {
        vv.type = 1;
        sscanf(buf,"%f",&vv.value.type_float);
    } else {
        vv.type = 0;
        sscanf(buf,"%d",&vv.value.type_int);
    }
    return vv;
}

int output_step = 0;
#define LL output_step++
#define OO for(int i=0;i<output_step;i++) printf("    ")
#define LO LL;OO
#define RR output_step--



Value dfs(YYLVAL node) {
    Value v = vo();
    //printf("starting output %d\n", node.type_node->type);
    switch(node.type_node->type) {
        case PROGRAM:
            dfs(node.type_node->a);
            break;

        case STMLIST:
            dfs(node.type_node->a);
            dfs(node.type_node->b);
            break;
        
        case COMPST: 
            dfs(node.type_node->a);
            break;

        case EXPSTMT:
            dfs(node.type_node->a);
            break;
        
        case COMPSTMT:
            dfs(node.type_node->a);
            break;

        case SCANSTMT:
            // ;printf("输入变量：%s\n", node.type_node->a.type_id);
            v = read();
            char* idname = node.type_node->a.type_id;
            update(idname, v);
            break;
        
        case PRINTSTMT:
            v = dfs(node.type_node->a);
            
            if (v.type == 0) {
                printf("%d\n", v.value.type_int);
            } else {
                printf("%f\n", v.value.type_float);
            }
            break;
        
        case IFSTMT:
            if (do_op2("!=", dfs(node.type_node->a), z()).value.type_int)
                dfs(node.type_node->b);
            break;

        case IFELSESTMT:
            if (do_op2("!=", dfs(node.type_node->a), z()).value.type_int)
                dfs(node.type_node->b);
            else dfs(node.type_node->c);
            break;

        case WHILESTMT:
            while (do_op2("!=", dfs(node.type_node->a), z()).value.type_int)
                dfs(node.type_node->b);
            break;
    

        case INTEXP:
            v.type = 0;
            v.value.type_int =  node.type_node->a.type_int;
             
            
            break;
        case FLOATEXP:
            v.type = 1;
            v.value.type_float =  node.type_node->a.type_float;
            break;

        case IDEXP:
            if(get(node.type_node->a.type_id).Lvalue < 0)
                v = update(node.type_node->a.type_id, v);
            else return get(node.type_node->a.type_id);
            break;
        
        case OP2EXP:
            v = do_op2(node.type_node->b.type_id, dfs(node.type_node->a), dfs(node.type_node->c));
            break;
        
        case OPEXP:
            v = do_op1(node.type_node->a.type_id, dfs(node.type_node->b));
            break;
        case PEXP:
            v = dfs(node.type_node->a);
            break;
        case EMPTY:
            break;
    }  

    return v;
}






/*****************************************************/
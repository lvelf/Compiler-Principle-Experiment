#include "stdio.h"  
#include "stdlib.h"  
#include "ctype.h"  
#include "string.h"
#include <string>
#include <regex>
#include <map>
#include <iostream>
using namespace std;

map<int,regex> mp;

char buf[256 * 1024];
string s;  

regex id_regex(R"([A-Za-z][A-Za-z0-9]*)");
regex intconst_regex(R"([0-9]+)");


int propose(string str) {
    for(auto a:mp){
        if(regex_match(str, a.second)) {
            return a.first;
        }
    }
    return -1;
}


void map_init(){
    /*
    id   [A-Za-z][A-Za-z0-9]*  
    intconst    [0-9]+
    */

    mp[1] = std::regex(R"(int)");
    mp[2] = std::regex(R"(while)");
    mp[3] = std::regex(R"(if)");
    mp[4] = std::regex(R"(else)");
    mp[5] = std::regex(R"(return)");
    mp[50] = std::regex("^[a-zA-Z_][a-zA-Z0-9_]*$");
    mp[51] = std::regex("^[0-9]+$");
    mp[60] = std::regex(R"(\+)");
    mp[61] = std::regex(R"(-)");
    mp[62] = std::regex(R"(\*)");
    mp[63] = std::regex(R"(/)");
    mp[64] = std::regex(R"(=)");
    mp[65] = std::regex(R"(<)");
    mp[66] = std::regex(R"(<=)");
    mp[67] = std::regex(R"(>)");
    mp[68] = std::regex(R"(>=)");
    mp[69] = std::regex(R"(==)");
    mp[70] = std::regex(R"(!=)");
    mp[71] = std::regex(R"(\{)");
    mp[72] = std::regex(R"(\})");
    mp[73] = std::regex(R"(\()");
    mp[74] = std::regex(R"(\))");
    mp[75] = std::regex(R"(,)");
    mp[76] = std::regex(R"(;)");
    mp[0] = std::regex(R"([\s]+)");
}

int main(int argc,char *argv[])    
{    
    
    FILE *fp;    
    fp=fopen(argv[1],"r");         //如果用C++实现，自行修改文件打开方式
    if (!fp) {printf("Fail Open\n");return 0;}    

    map_init();

 /***********在下面添加程序，根据文件指针读取测试文件中进行词法分析*********/  
    fread(buf, 1, 256*1024, fp);
    char* p = buf;
    while(*p != '\0') {
        s = p;
        string tmp = "", res = "#";
        int _max = 0;
    
        for(int i=0;i<s.length();i++){
            tmp.push_back(s[i]);
            if(propose(tmp) >= 0) {
                _max=i+1;
                res = tmp;
            }
        }
        p+=_max;
        int num = propose(res);
        if (res == "#") {
            break;
        }
        if (num == 0) {
            continue;
        }
        if (num == 50) {
            printf("(%d,\"%s\") ", num, res.c_str());
        } else if (num == 51) {
            printf("(%d,%s) ", num, res.c_str());
        } 
        else {
            printf("(%d,-) ", num);
        }
    }

    /*********************************************************************/  
    return 0;  
} 
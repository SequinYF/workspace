//
// Created by Sequin_YF on 2017/10/16.
//

#ifndef LEX_LEX_H
#define LEX_LEX_H
#include <iostream>
#include <map>
#include <vector>
#include <fstream>
#include <sstream>
#include <queue>
#include <cctype>
#define filePath "/Users/sequin_yf/Desktop/source.txt"
#define listPath "/Users/sequin_yf/Desktop/list.txt"
#define KEY 1 //start from 1
#define SAFE 10240
#define SYMBOL 30 //start from 30
#define NUMBER 2 //flag
using namespace std;

//pretreatment source
vector <string> source, vfile;

queue <string> ret;

//key value list
map <string, long> list;

string buf;
//const char* cStr = buf.c_str();


bool doList();
void getSource();
void pretreatment();
void analyse();
void judge();
bool isNum(string str);
void symbol_judge(string str);
bool doList();
#endif //LEX_LEX_H

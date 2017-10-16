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
#define filePath "/Users/sequin_yf/Desktop/source.txt"
using namespace std;

//pretreatment source
vector <string> source, vfile;
vector<string>::iterator iter;
//key value list
map <string, int> list;
string keyword[26]={
        "main","if","then","while","do","static","defualt","do","int",
        "double","struct","break","else","long","swtich","case","typedf",
        "char","return","const","float","short","continue","for","void","sizeof"};
string symbol[9]={'+','-','*','/','=',';','(',')','#'};
//file buf;
string buf;
const char* cStr = buf.c_str();
#endif //LEX_LEX_H

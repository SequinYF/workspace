#include "lex.h"


void getSource() {

    ifstream file;
    try {
        //open
        file.open(filePath);
        //size
//        file.seekg(0, ios_base::end);
//        streampos fileSzie = file.tellg();
        file.seekg(0, ios_base::beg);
        //copy
        while(getline(file, buf)) {
            vfile.push_back(buf);
        }
    }catch(const int err) {
        cout << "err" << endl;
        //error
    }
    file.close();
}

void pretreatment() {
    string str;
    for(iter = vfile.begin(); iter != vfile.end(); iter++) {
        char temp[40];
        string word;
        buf = *iter;
        int pos = 0, i = 0;

        //whitespace
        while (buf[i] == ' ') i++;
        while (i < buf.length()) {
            //note
            if (buf[i] == '/' && buf[i + 1] == '*') {
                i += 2;
                while (buf[i] != '*' && buf[i + 1] != '/') {
                    i++;
                }
                i++;
            }
            //push
            if (buf[i] == ' ') {
                temp[pos] = '\0';
                word = temp;
                source.push_back(word);
                pos = 0;
            }
            //whitespace in case
            while (buf[i] == ' ') i++;
            temp[pos] = buf[i++];
            pos++;

        }
        if(pos != 0) {
            temp[pos] = '\0';
            word = temp;
            source.push_back(word);
        }
    }
}
bool isNum(string str) {
    stringstream sin(str);
    double d;
    char c;
    if(!(sin >> d)) return false;
    if(sin >> c) return false;
}

void analyse() {
    for(iter = source.begin(); iter != source.end(); iter++) {
        string temp;
        temp = *iter;
        if(isNum(temp)) {
           cout << "num" << endl;
        }
        else{
            cout << list[temp] << endl;
        }

    }
}
int main() {

    getSource();
    pretreatment();
    analyse();
    return 0;
}
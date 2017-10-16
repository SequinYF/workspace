#include "./lex.h"
vector<string>::iterator iter;
void getSource() {

    ifstream file;
    try {

        //open
        file.open(filePath);

        //size
        file.seekg(0, ios_base::end);
        long long filesize = file.tellg();
        if(filesize > buf.max_size()-SAFE) {
            throw EOVERFLOW;
        }
        file.seekg(0, ios_base::beg);

        //copy
        while(getline(file, buf)) {
            vfile.push_back(buf);
        }
    }catch(const int err) {

        //error
        switch(err) {
            case EOVERFLOW:
                cout << "EOVERFLOW" << endl;    break;
            case EACCES:
                cout << "EACCES" << endl;   break;
            default:break;
        }
        exit(1);
    }

    //close code file
    file.close();
}

void pretreatment() {

    //for every single line
    string str;
    for(iter = vfile.begin(); iter != vfile.end(); iter++) {

        char temp[40];  //temp array for store;
        string word;
        buf = *iter;    //one line of source code file string;
        int pos = 0, i = 0; //pretreatment source index and source code index;

        //whitespace
        while (buf[i] == ' ') i++;  //eliminate the fronts of whitespaces
        while (i < buf.length()) {

            //eliminate notes
            if (buf[i] == '/' && buf[i + 1] == '*') {
                i += 2;
                while (buf[i] != '*' && buf[i + 1] != '/') {
                    i++;
                }
                i++;
            }

            //push the pretreatment word
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
        //linebreak in case
        if(pos != 0) {
            temp[pos] = '\0';
            word = temp;
            source.push_back(word);
        }
    }
}


bool doList() {

    fstream lfile;
    lfile.open(listPath);
    string str;
    int index = 0;

    try{
        while(getline(lfile, str)) {
            if(index < SYMBOL) {
                list[str] = KEY + index;
            }
            else{
                list[str] = KEY + index;
            }
            index++;
        }
    }catch (int err){
        return false;
    }

    lfile.close();
    return true;
}

bool isNum(string str) {
    stringstream sin(str);
    double d;
    char c;
    if(!(sin >> d)) return false;
    if(sin >> c) return false;
    return true;
}


void analyse() {
    for(iter = source.begin(); iter != source.end(); iter++) {
        string temp = *iter;
        string ans;
        int index = 0;
        int flag = 0;
        char ans_c[temp.length()];
        for(int i = 0; i < temp.length(); i++) {
             if(isdigit(temp[i])){
                if(flag != NUMBER && flag != 0) {
                    ans_c[index] = '\0';
                    ans = ans_c;
                    ret.push(ans);
                    flag = NUMBER;
                    index = 0;
                    ans_c[index++] = temp[i];
                }
                else{
                    flag = NUMBER;
                    ans_c[index++] = temp[i];
                }
            }
            if(isalpha(temp[i])){

                if(flag != KEY && flag != 0) {
                    ans_c[index] = '\0';
                    ans = ans_c;
                    ret.push(ans);
                    flag = KEY;
                    index = 0;
                    ans_c[index++] = temp[i];
                }
                else{
                    flag = KEY;
                    ans_c[index++] = temp[i];
                }
            }
            else{
                if(flag != SYMBOL && flag != 0) {
                    ans_c[index] = '\0';
                    ans = ans_c;
                    ret.push(ans);
                    flag = SYMBOL;
                    index = 0;
                    ans_c[index++] = temp[i];
                }
                else{
                    flag = SYMBOL;
                    ans_c[index++] = temp[i];
                }
            }

        }
        ans_c[index] = '\0';
        ans = ans_c;
        ret.push(ans);
    }
}

void judge() {

    while(!ret.empty()) {
        string str;
        str = ret.front();
       // cout << str << endl;
        ret.pop();
        if(isNum(str)) {
            cout << "NUMBER: " << str << endl;
        }
        else if(list[str]){
            if(list[str] < SYMBOL) {
                cout << "KEY: "<< str << " -> " <<  list[str] << endl;
            }
            else{
                cout << "SYMBOL: " << str << " -> " << list[str] << endl;
            }
        }
        else {
            cout << "WORD: " << str << endl;
        }
    }

}

int main() {

    doList();
    getSource();
    pretreatment();
    analyse();
    judge();
    return 0;
}
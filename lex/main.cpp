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

    // import match criteria
    fstream lfile;
    lfile.open(listPath);
    string str;
    int index = 0;

    try{

        //number the key words and symbol
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

    //for each string
    for(iter = source.begin(); iter != source.end(); iter++) {
        string temp = *iter;
        //split result string
        string ans;
        int index = 0;
        //define every char
        int flag = 0;
        //for string into char[]
        char ans_c[temp.length()];

        //for each char
        for(int i = 0; i < temp.length(); i++) {

            //if a number
             if(isdigit(temp[i])){
                 //last char is not a number
                if(flag != NUMBER && flag != 0) {
                    //make the result string,
                    ans_c[index] = '\0';
                    ans = ans_c;
                    ret.push(ans);
                    //change the flag type
                    flag = NUMBER;
                    //init index
                    index = 0;
                    //new result string
                    ans_c[index++] = temp[i];
                }
                    //last char still a number
                else{
                    //append into result string
                    flag = NUMBER;
                    ans_c[index++] = temp[i];
                }
            }

            //if a letter
            if(isalpha(temp[i])){
                //last char is not a letter
                if(flag != KEY && flag != 0) {
                    //make the result string
                    ans_c[index] = '\0';
                    ans = ans_c;
                    ret.push(ans);
                    //change flag type
                    flag = KEY;
                    //init result string
                    index = 0;
                    ans_c[index++] = temp[i];
                }
                else{
                    //append
                    flag = KEY;
                    ans_c[index++] = temp[i];
                }
            }
            //if a symbol
            if(!isalpha(temp[i]) && !isdigit(temp[i])){
                //last char is not symbol
                if(flag != SYMBOL && flag != 0) {
                    //make the result string
                    ans_c[index] = '\0';
                    ans = ans_c;
                    ret.push(ans);
                    //change flag type
                    flag = SYMBOL;
                    //init result string
                    index = 0;
                    ans_c[index++] = temp[i];
                }
                else{
                    //append
                    flag = SYMBOL;
                   ans_c[index++] = temp[i];
                }
            }

        }
        //the last result string
        ans_c[index] = '\0';
        ans = ans_c;
        ret.push(ans);
    }
}


void symbol_judge(string str) {
    //for each symbol string
    for(int i = 0; i < str.length(); i++) {
        //case of += -= *= /= != ==
        if(str[i] == '+' || str[i] == '-' || str[i] == '*' \
 || str[i] == '/' || str[i] == '!' || str[i] == '=') {
            if(str[i+1] == '=' ) {
                cout << "SYMBOL: " << str << " -> " << str[i] << \
                            str[i+1] << endl;
                i += 2;
            }
        }
        //case of ++
        if(str[i] == '+' && str[i+1] == '+'){
            char t[str.length()+1];
            t[0] = str[i];
            t[1] = str[i+1];
            t[2] = '\0';
            cout << "SYMBOL: " << str[i] << str[i+1]<< " -> " << list[t] << endl;
            i += 2;
        }
        //case of --
        if(str[i] == '-' && str[i+1] == '-'){
            char t[str.length()+1];
            t[0] = str[i];
            t[1] = str[i+1];
            t[2] = '\0';
            cout << "SYMBOL: " << str[i] << str[i+1] << " -> " << list[t] << endl;
            i += 2;
        }
        //case of <<
        if(str[i] == '<' && str[i+1] == '<'){
            char t[str.length()+1];
            t[0] = str[i];
            t[1] = str[i+1];
            t[2] = '\0';
            cout << "SYMBOL: " << str[i] << str[i+1] << " -> " << list[t] << endl;
            i += 2;
        }
        //case of >>
        if(str[i] == '>' && str[i+1] == '>'){
            char t[str.length()+1];
            t[0] = str[i];
            t[1] = str[i+1];
            t[2] = '\0';
            cout << "SYMBOL: " << str[i] << str[i+1] << " -> " << list[t] << endl;
            i += 2;
        }
        // case of single symbol
        char t[str.length()+1];
        t[0] = str[i];
        t[2] = '\0';
        cout << "SYMBOL: " << str[i] << " -> " << list[t] << endl;
    }
}

void judge() {

    //for each result string
    while(!ret.empty()) {
        string str;
        str = ret.front();
        ret.pop();

        //is number string
        if(isNum(str)) {
            cout << "NUMBER: " << str << endl;
        }
            //can match ,is key word or symbol
        else if(list[str]){
            if(list[str] < SYMBOL) {
                cout << "KEY: "<< str << " -> " <<  list[str] << endl;
            }
            else{
                cout << "SYMBOL: " << str << " -> " << list[str] << endl;
            }
        }
            //cant match, is symbol or word
        else {
            //word
            if(isalpha(str[0]))
                cout << "WORD: " << str << endl;
                //symbol
            else{
               symbol_judge(str);
            }
        }
    }

}

int main() {
    doList();   //key words and symbol match
    getSource(); //open file
    pretreatment(); //eliminate white space and notes ,pick up vaild strings
    analyse(); //split each strings by num, symbol and alpha
    judge(); //get results
    return 0;
}
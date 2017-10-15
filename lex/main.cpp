#include <iostream>
#include <map>
#include <vector>
#include <fstream>
#define filePath "/Users/sequin_yf/Desktop/source.txt"
using namespace std;

//file infomation
struct {
    long len;
}fNode;

//pretreatment source
vector <string> source, vfile;
vector<string>::iterator iter;
//key value list
map <string, int> list;
//file buf;
string buf;
const char* cStr = buf.c_str();


void getSource() {

    ifstream file;
    cout << "1" << endl;
    try {
        //open
        file.open(filePath);

        //size
        file.seekg(0, ios_base::end);
        streampos fileSzie = file.tellg();
        fNode.len = fileSzie;
        file.seekg(0, ios_base::beg);

        //copy
        while(getline(file, buf)) {
            vfile.push_back(buf);
           // cout << buf << endl;
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
        string temp;
        buf = *iter;
        // cout << buf << endl;
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
            if (buf[i] == ' ' || buf[i] == '\n' || buf[i] == '\r') {
                cout << temp << endl;
                source.push_back(temp);
                pos = 0;
            }
            //whitespace in case
            while (buf[i] == ' ') i++;
            temp[pos] = buf[i++];
            cout << temp[pos] << endl;
            pos++;
        }
        if(pos != 0) {
            cout << temp << endl;
            source.push_back(temp);
        }
    }
}

int main() {

    getSource();
    pretreatment();

    return 0;
}
#include <iostream>
#include <fstream>
#include <string>
#include <cstring>

using namespace std;

struct Stack {
    string value;
    struct Stack *next; 
};
 
void push(Stack* &NEXT, string VALUE)
{
    Stack *MyStack = new Stack; 
    MyStack->value = VALUE; 
    MyStack->next = NEXT; 
    NEXT = MyStack; 
}
 
string pop(Stack* &NEXT)
{
    string temp = NEXT->value; 
    Stack *MyStack = NEXT; 
    NEXT = NEXT->next; 
    delete MyStack; 
    return temp; 
}

string gettop(Stack* &NEXT) {
    string tmp = NEXT->value;
    return tmp;
}

bool isOpen(string s) {
    if (s[1] != '/') return true;
    else return false;
}

int main(int argc, char *argv[])
{
    //if strcmp == 0 строки равны
    fstream fs;
    fs.open(argv[1], ios_base::in);
    if(!fs.is_open()) {
        cout << "Can't open file(s).\r\n";
        return -1;
    }
    Stack *p = 0;
    bool flag = false;
    while(flag != true) {
        string s = ""; // tag
        char c, ch;
        fs.get(c);
        //cout << c;
        if (fs.eof()) flag = true;
        if (flag == true) break;

        if (c == '<') { 
            s += c;
            do {
                fs.get(ch);
                s += ch;
            } while (ch != '>'); 
        }
        else continue;

        if (isOpen(s)) {
            push(p,s);
            continue;
        }
        else {
            string last = gettop(p);
            s.erase(1,1);
            if (last.compare(s) == 0) {
                pop(p);
            }
        }
    }
    if (p != 0) cout << "Incorrectly placed tags." << endl;
    else cout << "Everything looks fine." << endl;
    fs.close();
    return 0;
}
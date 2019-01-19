#include <iostream>
#include <string>
#include <fstream>
using namespace std;

string Bracket(int k, bool close = false)
{
    switch(k % 3) {
        case 1: return close ? ")" : "(";
        case 2: return close ? "]" : "[";
        case 0: return close ? "}" : "{";
    }
}

int main(int argc, char *argv[])
{
    fstream fs(argv[1], ios_base::in);
    fstream out(argv[2], ios_base::out);
    if (!fs.is_open()) {
        cout << "Can't open file." << endl;
        return 1;
    }
    while (!fs.eof()) {
        string s;
        getline(fs, s);
        int k = 0; //количество скобок
        for (size_t i = 0; i < s.length(); i++)
        {
            if (s[i] == '(') {
                k++;
                s.erase(i,1);
                s.insert(i, Bracket(k));
            } else
            if (s[i] == ')') {
                s.erase(i,1);
                s.insert(i, Bracket(k, true));
                k--;
            }
        }
        if (k == 0) out << s << endl;
        else cout << "Incorrect sequence of brackets." << endl;
    }

    fs.close();
    return 0;
}

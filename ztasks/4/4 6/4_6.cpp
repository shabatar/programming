#include <iostream>
#include <string>
#include <fstream>
#include <math.h>
using namespace std;

bool isWord(char c)
{
    if (c == '_') return true;
    if (c >= 'A' && c <= 'Z') return true;
    if (c >= 'a' && c <= 'z') return true;
    if (c >= '0' && c <= '9') return true;
    return false;
}

int main(int argc, char *argv[])
{
    fstream fs(argv[1], ios_base::in);
    if (!fs.is_open()) {
        cout << "Can't open file." << endl;
        return -1;
    }
    string str, s = "";
    string maxword = "";
    int maxnum = 1;
    while (!fs.eof()) {
        getline(fs, str);
        for (size_t i = 0; i < str.length(); ++i) {
            if (isWord(str[i])) s += str[i];
            else {
                if (s.compare(maxword) == 0) ++maxnum;
                if (s.length() > maxword.length()) { maxword = s; maxnum = 1; }
                s = "";
            }
        }
        s = "";
    }

    cout << "Longest Word: '" << maxword << "'" << endl;
    cout << "Appeared " << maxnum << " times in file." << endl;
    fs.close();
    return 0;
}

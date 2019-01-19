#include <iostream>
#include <string>
#include <fstream>
#include <math.h>

#define uint unsigned int

using namespace std;

bool isNum(char c) {
    if (c >= '0' && c <= '9')
        return true;
    return false;
}

int strToInt(string s) {
    int res = 0;
    for (int i = s.length()-1; i >= 0 ; i--) {
        if (!isNum(s[i])) return 0;
            res += int(s[i] - '0') * pow(10, s.length() - i - 1);
    }
    return res;
}

string intToStr(int i) {
    string res = "";

    while (i > 0) {
        res = char(i%10 + '0') + res;
        i /= 10;
    }

    return res;
}

string addBeforeFormat(string s, string sub)
{
    uint i;
    for (i = 0; i < s.length(); i++)
        if (s[i] == '.') break;

    s.insert(i, sub);
    return s;
}



int main()
{
    string name;

    cout << "Enter file name:\n";
    cin >> name;
    fstream f(&name[0], ios_base::out|ios_base::binary);

    if (!f.is_open())
    {
        cout << "Error reading";
        return 1;
    }

    fstream of;
    string s;

    int size;
    int i = 1;

    char *data;

    while(1)
    {
        s = "_part_" + intToStr(i);
        of.open(&addBeforeFormat(name, s)[0], ios_base::in|ios_base::binary);

        if (!of.is_open()) break;

        of.seekg(0, ios::end);
        size = of.tellg();

        of.seekg(0, ios::beg);

        data = new char[size];
        of.read(data, size);
        of.close();
        
        f.write(data, size);
        i++;
    }

    f.close();

    delete[] data;
    return 0;
}
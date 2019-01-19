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

string FormParts(string s, string sub)
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
    fstream f(&name[0], ios_base::in|ios_base::binary);

    if (!f.is_open())
    {
        cout << "Error reading";
        return 1;
    }

    string ns;
    int n;
    cout << "Enter byte(or kbyte witk 'K'):\n";
    cin >> ns;
    if (ns[ns.length()-1] != 'K') n = strToInt(ns);
    else {
        ns.erase(ns.length()-1, 1);
        n = strToInt(ns)*1024;
    }

    char *data = new char[n];

    fstream out;
    string s;
    int i = 1;

    f.seekg(0, ios::end);
    int size = f.tellg();
    f.seekg(0, ios::beg);

    int k, size_count = 0;

    while (!f.eof())
    {
        if (size - size_count <= 0) break;
        s = "_part_" + intToStr(i);
        out.open(&FormParts(name, s)[0], ios_base::out|ios_base::binary);

        k = min(n, size - size_count);
        f.read(data, k);
        out.write(data, k);
        out.close();
        i++;
        size_count += n;
    }


    f.close();
    delete[] data;
    return 0;
}
#include <iostream>
#include <string>
#include <fstream>
#include <math.h>
using namespace std;

bool isnum(char c) {
    if (c >= '0' && c <= '9')
        return true;
    return false;
}

int StrToInt(string);

bool dateIsValid(string s) {
    int daysInNotLeapYear[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    int daysInLeapYear[12] = {31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    if (s[2] != '.') return false;
    if (s[5] != '.') return false;
    for (int i = 1; i < 10; i++)
        if (!isnum(s[i]) && i != 2 && i != 5) return false;
    int day = StrToInt(s.substr(0, 2));
    int month = StrToInt(s.substr(3, 2));
    int year = StrToInt(s.substr(6, 4));
    bool isLeap = ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0);
    if (month < 1 || month > 12) return false;
    if (isLeap && day > daysInLeapYear[month - 1]) return false;
    if (!isLeap && day > daysInNotLeapYear[month - 1]) return false;
    return true;
}

int StrToInt(string s) {
    int res = 0;
    for (int i = s.length()-1; i >= 0 ; i--)
    {
        if (!isnum(s[i])) return 0;
        res += int(s[i] - '0') * pow(10, s.length() - i - 1);
    }
    return res;
}

string Roman(int n) {
    int preim[] = { 1000, 900, 500, 400, 100, 90, 50, 40, 10, 9, 5, 4, 1 };
    string im[] = { "M", "CM", "D", "CD", "C", "XC", "L", "XL", "X", "IX", "V", "IV", "I" };

    int i = 0;
    string res = "";

    while (n > 0) {
        if (preim[i] <= n) {
            n -= preim[i];
            res += im[i];
        } else i++;
    }

    return res;
}

int main(int argc, char *argv[])
{
    fstream fs;
    fs.open(argv[1], ios_base::in);
    if (!fs.is_open()) {
        cout << "Can't open file." << endl;
        return -1;
    }
    string s, v;
    s = "";
    while (!fs.eof()) {
        getline(fs, v);
        if (s.length() == 0) s = v;
        else s += '\n' + v;
    }
    fs.close();
    string year;
    for (int i = 0; i < s.length(); i++) {
        if (s[i] >= '0' && s[i] <= '9') {
            if (dateIsValid(s.substr(i, 10))) {
                year = Roman(StrToInt(s.substr(i+6, 4)));
                s.erase(i+6, 4);
                s.insert(i+6, year);
                i+=10;
            }
        }
    }
    fs.open(argv[1], ios_base::out);
    fs << s;
    fs.close();
    return 0;
}

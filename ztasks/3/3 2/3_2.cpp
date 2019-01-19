#include <iostream>
#include <string>
#include <math.h>
using namespace std;

int LetterToNumber(char c) {
    if (c >= 48 && c <= 57) return c-48;
    if (c >= 98 && c <= 122) return c-32-55;
    return c - 55;
}

char NumberToLetter(int a) {
    if (a < 10) a += 48;
    else a += 55;
    return a;
}

int main()
{
    string str;
    int i, num, ns1, ns2;

    cout << "Enter number, NS1 (0..16), NS2 (0..16): " << endl;
    cin >> str >> ns1 >> ns2;
    if(ns1 > 16 || ns2 > 16 || ns2 < 0 || ns1 < 0) {
        cout << "Wrong data." << endl;
        return -1;
    }
    num = 0;
    for (int i = str.length()-1; i >= 0 ; i--) {
        if (LetterToNumber(str[i]) > 15) { cout << "Wrong data." << endl; return 1;}
        num += LetterToNumber(str[i]) * pow(ns1,str.length()-i-1);
    }
    str = "";

    while (num >= ns2) {
        str += NumberToLetter(num % ns2);
        num /= ns2;
        i++;
    }
    str += NumberToLetter(num);

    for (i = str.length()-1; i >= 0; i--) cout << str[i];
    cout << endl;
    return 0;
}
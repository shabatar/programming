#include <iostream>
#include <string>
using namespace std;

int main()
{
    string str;
    cout << "Enter binary string:\n";
    cin >> str;

    int begin = 0, tmpb = 0;
    int length = 0, tmpl = 0;
    bool zero = false;

    for (size_t i = 0; i < str.length(); ++i) {
        if (str[i] != '1' && str[i] != '0') {
            cout << "Wrong data." << endl;
            return 1;
        }
        if (str[i] == '0') {
            if (!zero) {
                tmpb = i; tmpl = 1;
                zero = true;
            } else tmpl++;
        } 
        else {
            if (tmpl > length) {
                length = tmpl;
                begin = tmpb;
            }
            zero = false;
        }
    }

    if (tmpl > length) {
        length = tmpl;
        begin = tmpb;
    }

    cout << "Begin: " << begin+1 << ", Length: " << length << endl;

    return 0;
}
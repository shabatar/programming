#include <iostream>
#include <string>
using namespace std;

int main()
{
    int preim[] = { 1000, 900, 500, 400, 100, 90, 50, 40, 10, 9, 5, 4, 1 };
    string im[] = { "M", "CM", "D", "CD", "C", "XC", "L", "XL", "X", "IX", "V", "IV", "I" };

    int n, i = 0;
    string res = "";

    cout << "Enter decimal number (1..3999) :" << endl;
    cin >> n;
    if (n >= 4000) {
        cout << "Too big number." << endl;
        return -1;
    }
    while (n > 0) {
        if (preim[i] <= n) {
        n -= preim[i];
        res += im[i];
        } 
        else i++;
    }

    cout << "Number in Roman Numerals: " << endl;
    cout << res << endl;
    return 0;
}
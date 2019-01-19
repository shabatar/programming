#include <iostream>
#include <string>
using namespace std;

string BinaryNumber(int k) {
    string num = "0000";
    int i = 3;
    while (k >= 2) {
        num[i] = char(k%2 + 48); //цифры с нуля в ascii. 48 - 0, 49 - 1
        k /= 2;
        i--;
    }
    num[i] = char(k%2 + 48);
    return num;
}

int main()
{
    string num, var_s;
    int num_int;
    cout << "Enter decimal number:\n";
    cin >> num_int;
    num = "";
    while (num_int > 0) {
        var_s = num;
        num = BinaryNumber(num_int % 10) + "." + var_s;
        num_int /= 10;
    }
    num.erase(num.length()-1, 1);
    cout << num << endl;
    return 0;
}

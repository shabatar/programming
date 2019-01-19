#include <iostream>
#include <math.h>
using namespace std;

int main()
{
    double a, b, c;
    cout << "Enter coefficients of a quadric equation : " << endl;
    cin >> a >> b >> c; 
    if (a == 0) { cout << "\x1b[31mNot a quadric equation.\x1b[0m" << endl; return -1; }

    double D = b*b - 4*a*c;

    if (D == 0) {
        cout << "x = " << (-b/(2*a)) << endl;
    } 
    else if (D > 0) {
        cout << "x_1 = " << ((-b+sqrt(D))/(2*a)) << endl;
        cout << "x_2 = " << ((-b-sqrt(D))/(2*a)) << endl;
    } 
    else {
        cout << "Only complex roots. Show? (y/n) ";
        char c;
        cin >> c;
        if (c == 'y') {
            D *= -1;
            cout << "x_1 = " << (-b/(2*a)) << " + i*" << sqrt(D)/(2*a) << endl;
            cout << "x_2 = " << (-b/(2*a)) << " - i*" << sqrt(D)/(2*a) << endl;
        }
    }
    return 0;
}
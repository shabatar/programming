#include <iostream>
#include <cmath>
//#define _USE_MATH_DEFINES
using namespace std;


double DegToRad(double deg) {
    double rad = (deg*M_PI)/180;
    return rad;
}

double BigTo180(double deg) {
    while(abs(deg) >= 360) {
        if(deg > 0) deg -= 360;
        else deg += 360;
    }
    while(abs(deg) >= 180) {
        if(deg > 0) deg -= 180;
        else deg +=180;
        if(deg == 0) return 0;
        else deg *= -1;
    }
    return deg;
}

double sum(double x, int n) {
    double sum = 0;
    if (n == 1) return sin(x);
    for (int i = 1; i <= n; i++) {
        sum += sin(x);
        x = sin(x);
    }
    return sum;
}

int main()
{
    int n;
    double x;
    char d;
    cout << "Degrees or radians? (d/r)" << endl;
    cin >> d;
    if (d == 'd') {    
        cout << "Enter angle and n." << endl;
        cin >> x >> n;
        x = BigTo180(x);
        x = DegToRad(x);
    }
    else if (d == 'r') {
        cout << "Enter angle and n." << endl;
        cin >> x >> n;
    }
    else {
        cout << "Wrong answer." << endl;
        return 0;
    }
    if (n < 1) cout << "Incorrect data." << endl;
    else cout << sum(x, n) << endl;
    return 0;
}
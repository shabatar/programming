#include <iostream>
#include <math.h>
#include <fstream>
using namespace std;

double SumRow(double x, double e) 
{
    double sum = 0;
    double c = e + 1;
    int i, k;
    i = 0; k = 1;
    sum = 0;

    while (c > e) {
        c = pow(x-1,i+1)/(i+1);
        sum += c*k;
        k *= -1;
        i++;
        //cout << "value of c: " << c << endl;
    }
    return sum;
}

int main()
{
    fstream fs, fs1;
    fs.open("sumin.txt");
    fs1.open("sumout.txt",ios_base::out | ios_base::trunc);
    if(fs.is_open() && fs1.is_open()) {
        double x1, x2, e, dx;
        fs >> x1 >> x2;
        if (x1 > 2 || x2 > 2 || x1 <= 0 || x2 <= 0) {
            cout << "Incorrect data. Check your input file." << endl;
            return -1;
        }
        fs >> e >> dx;
        fs1 << " X \t SUM" << endl;
        do {
            fs1 << x1 << " \t " << SumRow(x1, e) << endl;
            x1 += dx;
        } while (x1 + dx < x2);
    }
    else {
        cout << "Can't open file(s)." << endl;
        return -1;
    }
    fs.close();
    fs1.close();
    return 0;
}

#include <iostream>
#include <math.h>
#include <fstream>
using namespace std;

int main()
{
    /* 
        input format:
        <credit> <percent> <n of years> <term in months>
        <custom payment>
    */
    fstream fs, fs1;
    fs.open("creditin.txt");
    fs1.open("creditout.txt",ios_base::out | ios_base::trunc);
    if(fs.is_open() && fs1.is_open()) {
        int g, m;
        double p, k, pay, custom;

        //Kredit, percent, god, month
        fs >> k >> p >> g >> m;
        pay =   k / (12*g/m);
        fs >> custom;
        if (custom < pay)
            cout << "Incorrect data. Check your input file." << endl;
        if (custom > k)
            cout << "Incorrect data. Check your input file." << endl;


        fs1 << "CASE A" << endl;

        double sum = 0;
        int i = 0;

        while (sum < k) {
            fs1 << i+1 << " " << pay + (k-sum)*p << endl;
            sum += pay;
            i++;
        }

        if (custom > pay && custom < k)  {
            fs1 << endl << "CASE B" << endl;
            sum = 0;
            i = 0;
            double l = custom;
            while (sum < k)
            {
                if (k - sum < custom) l = (k - sum);
                fs1 << i+1 << " " << l + (k-sum)*p << endl;
                sum += custom;
                i++;
            }
        }
    }
    else {
        cout << "Can't open file(s)." << endl;
        return -1;
    }
    fs.close();
    fs1.close();
    return 0;
    }
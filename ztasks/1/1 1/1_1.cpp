#include <iostream>
#include <stdlib.h>
#include <iomanip>
using namespace std;

int nd (int n)
{
    return n ? 1 + nd(n/10) : 0;
}

int main()
{
    int time[6];
    char ch;

    cout << "Enter first moment (hh:mm:ss) :" << endl;
    cin >> time[0] >> ch >> time[1] >> ch >> time[2];
    //Correctness test1
    if (time[0] >= 24 || time[0] < 0 || time[1] >= 60 ||
        time[1] < 0 || time[2] >= 60 || time[2] < 0 ||
        (nd(time[0]) + nd(time[1]) + nd(time[2])) > 6)
    {
        cout << "\x1b[31mIncorrect data.\x1b[0m" << endl;
        return -1;
    }

    cout << "Enter second moment (hh:mm:ss) :" << endl;
    cin >> time[3]>> ch >> time[4] >> ch >>  time[5];

    //Correctness test2
    if (time[3] >= 24 || time[3] < 0 || time[4] >= 60 ||
        time[4] < 0 || time[5] >= 60 || time[5] < 0 ||
        (nd(time[3]) + nd(time[4]) + nd(time[5])) > 6)
    {
        cout << "\x1b[31mIncorrect data.\x1b[0m" << endl;
        return -1;
    }


    int v = abs((time[0] - time[3])*3600 + (time[1] - time[4])*60 + (time[2] - time[5]));

    time[0] = v/3600;
    v %= 3600;
    time[1] = v/60;
    v %= 60;
    time[2] = v;

    cout << endl;
    cout << setw(2) << setfill('0') << time[0] << ":";
    cout << setw(2) << setfill('0') << time[1] << ":";
    cout << setw(2) << setfill('0') << time[2];
    cout << endl;
    return 0;
}

#include <iostream>
using namespace std;

int Josephus(int m, int n)
{
    if (n == 1) return 1;
    return (1 + (Josephus(m, n-1) + m-1) % n);
}

int main()
{
    int n = 20;
    int m, m1;
    cout << "Enter m: ";
    cin >> m;
    for (size_t i = 2; i < n; i ++) {
        if (Josephus(i,n) == 1) {
            m1 = i;
            break;
        }
    }
    cout << "Man #" << Josephus(m, n) << " survived.\r\n";
    cout << "First man would survive in case m equals " << m1 << ".\r\n";
    return 0;
}
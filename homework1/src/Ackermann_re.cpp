#include <iostream>
using namespace std;
int Ack(int m, int n) 
{
    if (m == 0)
        return n + 1;
    else if (n == 0)
        return Ack(m - 1, 1);
    else
        return Ack(m - 1, Ack(m, n - 1));
}
int main() 
{
    int m, n;
    cout << "輸入 m 和 n: ";
    cin >> m >> n;
    cout << "A(" << m << ", " << n << ") = " << Ack(m, n) << endl;
    return 0;
}



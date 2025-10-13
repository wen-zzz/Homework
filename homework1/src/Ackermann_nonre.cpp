#include <iostream>
#include <cmath>
using namespace std;
int Ack(int m, int n) {
    if (m == 0) return n + 1;
    else if (m == 1) return n + 2;
    else if (m == 2) return 2 * n + 3;
    else if (m == 3) return pow(2, n + 3) - 3;
    else if (m == 4 && n == 0) return 13;
    else
    {
        cout << "數值太大，無法處理。" << endl;
        return -1;
    }
}

int main() {
    int m, n;
    cout << "輸入 m 和 n: ";
    cin >> m >> n;
    int result = Ack(m, n);
    if (result != -1)
        cout << "Ackermann(" << m << ", " << n << ") = " << result << endl;
    return 0;
}



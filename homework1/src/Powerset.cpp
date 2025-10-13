#include <iostream>
using namespace std;

void powerSet(char* set, int n, int index) 
{
    static bool chosen[100] = { false }; 


    if (index == n) 
    {
        cout << "{ ";
        for (int i = 0; i < n; i++) 
        {
            if (chosen[i]) cout << set[i] << " ";
        }
        cout << "}" << endl;
        return;
    }


    chosen[index] = false;
    powerSet(set, n, index + 1);


    chosen[index] = true;
    powerSet(set, n, index + 1);
}

int main() 
{
    int n;
    cout << "輸入集合大小 n: ";
    cin >> n;
    char* set = new char[n];
    cout << "請輸入 " << n << " 個元素（例如 a b c）: ";
    for (int i = 0; i < n; i++) 
    {
        cin >> set[i];
    }
    cout << "\nPower set:" << endl;
    powerSet(set, n, 0);
    delete[] set;
    return 0;
}

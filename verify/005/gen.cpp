#include<bits/stdc++.h>
using namespace std;

int main() {
    srand(time(0));

    int T = 20;
    cout << T << endl;

    for(int i = 0; i < T; i++) {
        int n = rand() % 20 + 1; // 小范围
        cout << n << endl;
    }
}
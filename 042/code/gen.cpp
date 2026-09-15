#include <bits/stdc++.h>
using namespace std;
int main() {
    srand(time(0));
    int N = rand() % 20 + 3;
    cout << N << "\n";
    for (int i = 0; i < N; i++) {
        int len = rand() % 10 + 1;
        for (int j = 0; j < len; j++) cout << char('A' + rand() % 26);
        cout << "\n";
    }
}

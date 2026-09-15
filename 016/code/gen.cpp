#include <bits/stdc++.h>
using namespace std;

int main() {
    srand(time(0));
    int T = 5;
    cout << T << "\n";
    for (int t = 0; t < T; t++) {
        int a = rand() % 9 + 2;
        int b = rand() % 5 + 1;
        cout << a << " " << b << "\n";
    }
}

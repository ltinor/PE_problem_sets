#include <bits/stdc++.h>
using namespace std;

int main() {
    srand(time(0));
    int T = 5;
    cout << T << "\n";
    for (int t = 0; t < T; t++) {
        int n = rand() % 30 + 1;
        cout << n << "\n";
    }
}

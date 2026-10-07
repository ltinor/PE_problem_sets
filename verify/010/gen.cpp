#include <bits/stdc++.h>
using namespace std;

int main() {
    srand(time(0));

    int T = 10;
    cout << T << "\n";

    for(int i = 0; i < T; i++) {
        int K = rand() % 10000 + 1;
        cout << K << "\n";
    }

    return 0;
}
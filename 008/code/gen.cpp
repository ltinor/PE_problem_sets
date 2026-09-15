#include <bits/stdc++.h>
using namespace std;

int main() {
    srand(time(0));

    int T = 10;
    cout << T << endl;

    for(int t = 0; t < T; t++) {
        int L = rand() % 1000 + 1;        
        int K = rand() % min(L, 15) + 1; 
        cout << L << " " << K << endl;

        for(int i = 0; i < L; i++) {
            cout << rand() % 10;
        }
        cout << endl;
    }

    return 0;
}
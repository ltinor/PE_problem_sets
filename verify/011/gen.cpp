#include <bits/stdc++.h>
using namespace std;

mt19937 rng(time(0));

int randint(int l, int r) {
    return uniform_int_distribution<int>(l, r)(rng);
}

int main() {
    int T = 5; 
    cout << T << "\n";

    for(int t = 0; t < T; t++) {
        int m = randint(4, 6); 
        cout << m << "\n";

        for(int i = 0; i < m; i++) {
            for(int j = 0; j < m; j++) {
                int val = randint(-5, 5); 
                cout << val << (j == m - 1 ? '\n' : ' ');
            }
        }
    }
}
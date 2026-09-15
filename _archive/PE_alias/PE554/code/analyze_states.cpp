#include<bits/stdc++.h>
using namespace std;

bool attacks(int s1, int s2, int dr, int dc) {
    int r1 = s1 >> 1, c1 = s1 & 1;
    int r2 = s2 >> 1, c2 = s2 & 1;
    int cell_dr = 2*dr + r2 - r1;
    int cell_dc = 2*dc + c2 - c1;
    int adr = abs(cell_dr), adc = abs(cell_dc);
    if (adr <= 1 && adc <= 1 && (adr > 0 || adc > 0)) return true;
    if ((adr == 1 && adc == 2) || (adr == 2 && adc == 1)) return true;
    return false;
}

bool row_self_ok(int h, int n) {
    vector<int> r(n);
    for (int i = 0; i < n; i++) { r[i] = h % 4; h /= 4; }
    for (int c1 = 0; c1 < n; c1++) {
        for (int c2 = c1+1; c2 < n; c2++) {
            int dc = c2 - c1;
            if (dc <= 2 && attacks(r[c1], r[c2], 0, dc)) return false;
        }
    }
    return true;
}

int main() {
    for (int n = 1; n <= 5; n++) {
        int states = 1;
        for (int i = 0; i < n; i++) states *= 4;
        cout << "n=" << n << " valid row states:" << endl;
        for (int h = 0; h < states; h++) {
            if (row_self_ok(h, n)) {
                // Print as sequence of block states
                cout << "  ";
                int tmp = h;
                for (int i = 0; i < n; i++) {
                    cout << (tmp % 4);
                    tmp /= 4;
                }
                cout << endl;
            }
        }
    }
    return 0;
}

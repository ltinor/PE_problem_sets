#include<bits/stdc++.h>
using namespace std;
using ll = long long;

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

void decode(int h, int n, vector<int>& row) {
    for (int i = 0; i < n; i++) { row[i] = h % 4; h /= 4; }
}

bool compatible(int h1, int h2, int n) {
    vector<int> r1(n), r2(n);
    decode(h1, n, r1);
    decode(h2, n, r2);
    for (int c = 0; c < n; c++) {
        for (int pc = max(0, c-1); pc <= min(n-1, c+1); pc++) {
            if (attacks(r1[c], r2[pc], 1, pc-c)) return false;
        }
    }
    return true;
}

bool row_self_ok(int h, int n) {
    vector<int> r(n);
    decode(h, n, r);
    for (int c1 = 0; c1 < n; c1++) {
        for (int c2 = c1+1; c2 < n; c2++) {
            int dc = c2 - c1;
            if (dc <= 2 && attacks(r[c1], r[c2], 0, dc)) return false;
        }
    }
    return true;
}

int main() {
    for (int n = 1; n <= 7; n++) {
        int states = 1;
        for (int i = 0; i < n; i++) states *= 4;
        
        int valid_count = 0;
        for (int h = 0; h < states; h++) {
            if (row_self_ok(h, n)) valid_count++;
        }
        cout << "n=" << n << ": total states=" << states << ", valid row states=" << valid_count << endl;
    }
    return 0;
}

#include<bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    system("mkdir -p data");
    srand(time(0));

    vector<string> tc = {
        "2",   // 2-digit: digits 0 each twice? n=2 means one pair (digit 0)?
        "4",   // 4-digit: two pairs (0 and 1 each twice)
        "6",   // 6-digit: three pairs
        "PE"   // PE answer check
    };
    for (int i = 0; i < (int)tc.size(); i++) {
        char fn[32];
        sprintf(fn, "data/%02d.in", i+1);
        ofstream f(fn);
        f << tc[i] << "\n";
    }
}

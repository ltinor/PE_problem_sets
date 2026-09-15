#include <bits/stdc++.h>
using namespace std;
using ll = long long;
int main() {
    system("mkdir -p data");
    vector<ll> tests = {10, 50, 100, 500, 1000, 5000, 10000, 50000, 100000, 500000};
    for (int i = 0; i < 10; i++) {
        string fname = "data/" + (i < 9 ? "0" : "") + to_string(i + 1) + ".in";
        ofstream fout(fname);
        fout << tests[i] << "\n";
        fout.close();
    }
    return 0;
}

#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    system("mkdir -p data");
    srand(time(0));

    vector<ll> cases = {10, 100, 500, 1000, 5000,
                        10000, 100000, 1000000, 5000000, 10000000};

    for (int i = 0; i < 10; i++) {
        string fname = string("data/") + (i < 9 ? "0" : "") + to_string(i + 1) + ".in";
        ofstream fout(fname);
        fout << cases[i] << "\n";
        fout.close();
        cout << "Generated " << fname << " limit=" << cases[i] << "\n";
    }
    return 0;
}

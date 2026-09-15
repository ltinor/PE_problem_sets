#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    system("mkdir -p data");
    srand(time(0));

    vector<ll> cases(10);

    // 1-3: small K
    cases[0] = 1;
    cases[1] = 2;
    cases[2] = 3;

    // 4-6: medium
    cases[3] = 4;
    cases[4] = 5;
    cases[5] = 6;

    // 7-8: larger
    cases[6] = 7;
    cases[7] = 8;

    // 9-10: near max / max
    cases[8] = 10;
    cases[9] = 13;

    for (int i = 0; i < 10; i++) {
        string fname = string("data/") + (i < 9 ? "0" : "") + to_string(i + 1) + ".in";
        ofstream fout(fname);
        fout << cases[i] << "\n";
        fout.close();
        cout << "Generated " << fname << " K=" << cases[i] << "\n";
    }

    return 0;
}

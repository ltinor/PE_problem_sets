#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    system("mkdir -p data");
    srand(time(0));

    vector<pair<string,ll>> cases(10);

    // 1. sample: the example from PE
    cases[0] = {"DdDddUUdDD", 1000000LL};

    // 2-3. short sequences, small threshold
    cases[1] = {"D", 10LL};
    cases[2] = {"d", 10LL};

    // 4-5. slightly longer
    cases[3] = {"UDD", 50LL};
    cases[4] = {"DdD", 100LL};

    // 6-7. medium sequences
    cases[5] = {"UDDDUddd", 1000LL};
    cases[6] = {"DDUDDddDd", 100000LL};

    // 8. PE problem (large threshold 10^15)
    cases[7] = {"UDDDUdddDDUDDddDdDddDDUDDdUUDd", 1000000000000000LL};

    // 9-10. random
    cases[8] = {"DdDddU", 500LL};
    cases[9] = {"UUDDd", 200LL};

    for (int i = 0; i < 10; i++) {
        string fname = string("data/") + (i < 9 ? "0" : "") + to_string(i + 1) + ".in";
        ofstream fout(fname);
        fout << cases[i].first << " " << cases[i].second << "\n";
        fout.close();
        cout << "Generated " << fname << ": " << cases[i].first << " " << cases[i].second << "\n";
    }
    return 0;
}

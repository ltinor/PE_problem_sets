#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    system("mkdir -p data");
    srand(time(0));
    vector<pair<ll,ll>> tests = {
        {0, 100}, {100, 200}, {0, 300}, {500, 600},
        {0, 500}, {1000, 1500}, {2000, 2500}, {5000, 5500},
        {0, 1000}, {10000, 11000}
    };
    for (int i = 0; i < 10; i++) {
        string fname = "data/" + (i < 9 ? "0" : "") + to_string(i + 1) + ".in";
        ofstream fout(fname);
        fout << tests[i].first << " " << tests[i].second << "\n";
        fout.close();
        cout << "Generated " << fname << "\n";
    }
    return 0;
}

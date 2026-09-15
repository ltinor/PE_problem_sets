#include<bits/stdc++.h>
using namespace std;
#define ll long long

int main() {
    system("mkdir -p data");
    // D, K pairs (small enough for brute)
    vector<pair<ll,ll>> tests = {
        {1, 1}, {2, 1}, {2, 2}, {3, 1}, {3, 2},
        {4, 1}, {4, 2}, {5, 1}, {5, 2}, {6, 1}
    };
    for (int i = 0; i < 10; i++) {
        string fn = "data/" + string(i<9?"0":"") + to_string(i+1) + ".in";
        ofstream f(fn);
        f << tests[i].first << " " << tests[i].second << "\n";
        f.close();
        cout << "Generated " << fn << " D=" << tests[i].first << " K=" << tests[i].second << "\n";
    }
    return 0;
}

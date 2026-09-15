#include <bits/stdc++.h>
using namespace std;
#define ll long long

int main() {
    system("mkdir -p data");

    // Reduced data range: 1 <= N <= 60 (original PE asked fixed N=120).
    vector<ll> test_cases = {4, 10, 20, 30, 40, 50, 60, 6, 12, 8};

    for (int i = 0; i < 10; i++) {
        string filename = string("data/") + (i < 9 ? "0" : "") + to_string(i + 1) + ".in";
        ofstream fout(filename);
        fout << test_cases[i] << "\n";
        fout.close();
        cout << "Generated " << filename << " with N = " << test_cases[i] << "\n";
    }

    return 0;
}

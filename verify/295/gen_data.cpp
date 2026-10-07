#include <bits/stdc++.h>
using namespace std;
#define ll long long

int main() {
    system("mkdir -p data");

    // Reduced data set (N <= 200). The verification points are L(10)=30 and
    // L(100)=3442.
    vector<ll> test_cases = {1, 2, 3, 5, 10, 20, 50, 100, 150, 200};

    for (int i = 0; i < (int)test_cases.size(); i++) {
        string filename = string("data/") + (i < 9 ? "0" : "") + to_string(i + 1) + ".in";
        ofstream fout(filename);
        fout << test_cases[i] << "\n";
        fout.close();
        cout << "Generated " << filename << " with N = " << test_cases[i] << "\n";
    }

    return 0;
}

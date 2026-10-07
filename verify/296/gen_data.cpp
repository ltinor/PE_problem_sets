#include <bits/stdc++.h>
using namespace std;
#define ll long long

int main() {
    system("mkdir -p data");
    
    vector<ll> test_cases = {100000, 10, 50, 100, 200, 500, 1000, 2000, 5000, 10000};
    
    for (int i = 0; i < 10; i++) {
        string filename = string("data/") + (i < 9 ? "0" : "") + to_string(i + 1) + ".in";
        ofstream fout(filename);
        fout << test_cases[i] << "\n";
        fout.close();
        cout << "Generated " << filename << " with P = " << test_cases[i] << "\n";
    }
    
    return 0;
}

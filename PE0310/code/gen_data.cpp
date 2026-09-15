#include <bits/stdc++.h>
using namespace std;

int main() {
    system("mkdir -p data");
    srand(time(0));

    vector<long long> cases = {29, 5, 50, 100, 500, 1000, 5000, 10000, 50000, 100000};

    for (int i = 0; i < 10; i++) {
        string fname = string("data/") + (i < 9 ? "0" : "") + to_string(i + 1) + ".in";
        ofstream fout(fname);
        fout << cases[i] << "\n";
        fout.close();
        cout << "Generated " << fname << " N=" << cases[i] << "\n";
    }
    return 0;
}

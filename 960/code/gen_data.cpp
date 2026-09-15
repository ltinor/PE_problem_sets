#include <bits/stdc++.h>
using namespace std;

int main() {
    system("mkdir -p data");

    // Fixed test cases covering the reduced data range 1 <= n <= 12.
    // Cases 1-2 are the sample points (F(3)=12, F(4)=360).
    vector<int> tc = {3, 4, 1, 2, 5, 8, 10, 11, 12, 9};

    for (int i = 0; i < (int)tc.size(); ++i) {
        string filename = string("data/") + (i < 9 ? "0" : "") + to_string(i + 1) + ".in";
        ofstream fout(filename);
        fout << tc[i] << "\n";
        fout.close();
        cout << "Generated " << filename << " with n = " << tc[i] << "\n";
    }

    return 0;
}

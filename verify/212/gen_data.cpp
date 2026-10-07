#include<bits/stdc++.h>
using namespace std;

int main() {
    system("mkdir -p data");
    srand(time(0));

    vector<int> tests = {1, 5, 10, 20, 50, 100, 200, 500, 1000, 50000};
    // PE answer for K=50000: 328968937309

    for (int i = 0; i < 10; i++) {
        string fname = string("data/") + (i < 9 ? "0" : "") + to_string(i + 1) + ".in";
        ofstream fout(fname);
        fout << tests[i] << "\n";
        fout.close();
        cout << "Generated " << fname << " with K = " << tests[i] << "\n";
    }

    return 0;
}

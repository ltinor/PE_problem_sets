#include <bits/stdc++.h>
using namespace std;

int main() {
    system("mkdir -p data");
    srand(time(0));

    vector<int> tests = {10, 20, 50, 100, 200};
    for (int i = 0; i < (int)tests.size(); i++) {
        string fname = "data/" + (i < 9 ? "0" : "") + to_string(i + 1) + ".in";
        ofstream fout(fname);
        fout << tests[i] << "\n";
        fout.close();
        cout << "Generated " << fname << " with S=" << tests[i] << "\n";
    }
    // Additional random cases
    for (int i = tests.size(); i < 10; i++) {
        int S = (rand() % 95 + 1) * 2 + 10;
        string fname = "data/" + (i < 9 ? "0" : "") + to_string(i + 1) + ".in";
        ofstream fout(fname);
        fout << S << "\n";
        fout.close();
        cout << "Generated " << fname << " with S=" << S << "\n";
    }
    return 0;
}

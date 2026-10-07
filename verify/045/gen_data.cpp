#include <bits/stdc++.h>
using namespace std;

int main() {
    system("mkdir -p data");
    srand(time(0));

    vector<int> test_cases(10);

    // K ranges 1 to 3, repeat values to fill 10 cases
    int vals[] = {1, 2, 3, 2, 3, 1, 3, 2, 3, 1};
    for (int i = 0; i < 10; i++) {
        test_cases[i] = vals[i];
    }

    for (int i = 0; i < 10; i++) {
        string filename = string("data/") + (i < 9 ? "0" : "") + to_string(i + 1) + ".in";
        ofstream fout(filename);
        fout << test_cases[i] << "\n";
        fout.close();
        cout << "Generated " << filename << " with K = " << test_cases[i] << "\n";
    }

    return 0;
}

#include <bits/stdc++.h>
using namespace std;

int main() {
    srand(time(0));

    vector<int> test_cases = {2, 3, 5, 8, 10, 12, 13, 14, 15, 15};

    for (int i = 0; i < 10; i++) {
        string filename = string("data/") + (i < 9 ? "0" : "") + to_string(i + 1) + ".in";
        ofstream fout(filename);
        fout << test_cases[i] << "\n";
        fout.close();
        cout << "Generated " << filename << " with M = " << test_cases[i] << "\n";
    }

    return 0;
}

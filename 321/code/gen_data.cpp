#include<bits/stdc++.h>
using namespace std;

int main() {
    system("mkdir -p data");
    srand(time(0));

    vector<int> test_cases = {
        5,   // sample: first 5 terms sum = 99
        1,   // min
        10,  // medium
        20,  // medium
        30,  // large
        40,  // PE original
        2,   // tiny
        3,   // tiny
        15,  // medium
        25   // medium-large
    };

    for (int i = 0; i < 10; i++) {
        string filename = string("data/") + (i < 9 ? "0" : "") + to_string(i + 1) + ".in";
        ofstream fout(filename);
        fout << test_cases[i] << "\n";
        fout.close();
        cout << "Generated " << filename << " with K=" << test_cases[i] << "\n";
    }

    return 0;
}

#include <bits/stdc++.h>
using namespace std;

int main() {
    system("mkdir -p data");

    // PE 104 is a fixed-answer problem (no variable input)
    // Generate a single test case with dummy input
    for (int i = 0; i < 10; i++) {
        string filename = string("data/") + (i < 9 ? "0" : "") + to_string(i + 1) + ".in";
        ofstream fout(filename);
        fout << "0\n";
        fout.close();
        cout << "Generated " << filename << "\n";
    }

    return 0;
}

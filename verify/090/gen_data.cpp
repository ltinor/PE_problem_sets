#include <bits/stdc++.h>
using namespace std;

int main() {
    system("mkdir -p data");

    // Fixed-answer problem: just create one test case
    for (int i = 0; i < 10; i++) {
        string filename = string("data/") + (i < 9 ? "0" : "") + to_string(i + 1) + ".in";
        ofstream fout(filename);
        fout << "0\n";  // dummy input, answer is always 1217
        fout.close();
        cout << "Generated " << filename << "\n";
    }

    return 0;
}

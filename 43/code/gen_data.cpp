#include <bits/stdc++.h>
using namespace std;

int main() {
    system("mkdir -p data");

    // Only 1 test case - this is a verification problem
    string filename = "data/01.in";
    ofstream fout(filename);
    fout << 0 << "\n";  // ignored input
    fout.close();
    cout << "Generated " << filename << " (verification problem)\n";

    return 0;
}

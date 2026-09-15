#include <bits/stdc++.h>
using namespace std;

int main() {
    system("mkdir -p data");
    
    // Fixed-answer problem: all test cases just output dummy "1"
    // PE answer: 0.464399
    for (int i = 0; i < 10; i++) {
        string filename = string("data/") + (i < 9 ? "0" : "") + to_string(i + 1) + ".in";
        ofstream fout(filename);
        fout << "1\n";
        fout.close();
        cout << "Generated " << filename << " (dummy input)\n";
    }
    
    return 0;
}

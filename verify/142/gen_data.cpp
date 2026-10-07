#include<bits/stdc++.h>
using namespace std;

int main() {
    system("mkdir -p data");

    // Fixed answer problem — generate test cases
    for (int i = 0; i < 10; i++) {
        string filename = string("data/") + (i < 9 ? "0" : "") + to_string(i + 1) + ".in";
        ofstream fout(filename);
        fout << "1\n";  // dummy input
        fout.close();
        cout << "Generated " << filename << "\n";
    }

    return 0;
}

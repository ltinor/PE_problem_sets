#include <bits/stdc++.h>
using namespace std;

int main() {
    system("mkdir -p data");

    // All n from 1 to 7
    for (int i = 0; i < 7; i++) {
        string filename = string("data/0") + to_string(i + 1) + ".in";
        ofstream fout(filename);
        fout << (i + 1) << "\n";
        fout.close();
        cout << "Generated " << filename << " with n = " << (i+1) << "\n";
    }

    // 3 more test cases: repeating edge cases
    for (int i = 7; i < 10; i++) {
        int n = (i == 7) ? 3 : (i == 8) ? 6 : 7;
        string filename = string("data/") + (i < 9 ? "0" : "") + to_string(i + 1) + ".in";
        ofstream fout(filename);
        fout << n << "\n";
        fout.close();
        cout << "Generated " << filename << " with n = " << n << "\n";
    }

    return 0;
}

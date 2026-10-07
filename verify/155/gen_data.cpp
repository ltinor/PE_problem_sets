#include <bits/stdc++.h>
using namespace std;

int main() {
    system("mkdir -p data");
    
    // PE 155 answer: D(18) = 3857447
    // D(1)=1, D(2)=3, D(3)=7, D(4)=15, D(5)=31, D(6)=?
    vector<int> test_cases = {
        18,  // PE answer: 3857447
        1,
        2,
        3,
        4,
        5,
        6,
        8,
        10,
        12
    };
    
    for (int i = 0; i < 10; i++) {
        string filename = string("data/") + (i < 9 ? "0" : "") + to_string(i + 1) + ".in";
        ofstream fout(filename);
        fout << test_cases[i] << "\n";
        fout.close();
        cout << "Generated " << filename << " with N=" << test_cases[i] << "\n";
    }
    
    return 0;
}

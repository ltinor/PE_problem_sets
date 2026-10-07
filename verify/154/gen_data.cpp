#include <bits/stdc++.h>
using namespace std;

int main() {
    system("mkdir -p data");
    
    // PE 154 answer for N=200000: 479742450
    vector<int> test_cases = {
        200000,  // PE answer: 479742450
        0,
        1,
        2,
        5,
        10,
        20,
        50,
        100,
        200
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

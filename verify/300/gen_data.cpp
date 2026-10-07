#include <bits/stdc++.h>
using namespace std;

int main() {
    system("mkdir -p data");
    
    vector<int> test_cases = {15, 1, 2, 3, 4, 5, 6, 8, 10, 12};
    
    for (int i = 0; i < 10; i++) {
        string filename = string("data/") + (i < 9 ? "0" : "") + to_string(i + 1) + ".in";
        ofstream fout(filename);
        fout << test_cases[i] << "\n";
        fout.close();
        cout << "Generated " << filename << " with n = " << test_cases[i] << "\n";
    }
    
    return 0;
}

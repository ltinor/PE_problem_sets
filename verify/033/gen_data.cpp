#include <bits/stdc++.h>
using namespace std;

int main() {
    system("mkdir -p data");
    srand(time(0));

    // Answer is always 100, generate 10 test cases with dummy T values
    vector<int> test_cases = {1, 2, 3, 5, 10, 20, 50, 100, 1, 1};

    for (int i = 0; i < 10; i++) {
        string filename = string("data/") + (i < 9 ? "0" : "") + to_string(i + 1) + ".in";
        ofstream fout(filename);
        fout << test_cases[i] << "\n";
        fout.close();
        cout << "Generated " << filename << " with t = " << test_cases[i] << "\n";
    }

    return 0;
}

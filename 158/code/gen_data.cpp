#include <bits/stdc++.h>
using namespace std;

int main() {
    system("mkdir -p data");
    srand(time(0));

    // Fixed answer: always output 409511334375
    vector<int> test_cases = {1, 2, 3, 5, 10, 20, 26, 1, 1, 1};

    for (int i = 0; i < 10; i++) {
        string fname = string("data/") + (i < 9 ? "0" : "") + to_string(i + 1) + ".in";
        ofstream fout(fname);
        fout << test_cases[i] << "\n";
        fout.close();
        cout << "Generated " << fname << " with t = " << test_cases[i] << "\n";
    }

    return 0;
}

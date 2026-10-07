#include <bits/stdc++.h>
using namespace std;

int main() {
    system("mkdir -p data");
    srand(time(0));

    vector<int> test_cases(10);

    // 1: PE original → D=45
    test_cases[0] = 45;

    // 2-3: large angles (smaller search space)
    test_cases[1] = 80;
    test_cases[2] = 85;

    // 4-5: medium angles
    test_cases[3] = 60;
    test_cases[4] = 70;

    // 6-7: slightly larger than 45
    test_cases[5] = 50;
    test_cases[6] = 55;

    // 8: very large angle
    test_cases[7] = 89;

    // 9-10: original + one more
    test_cases[8] = 45;
    test_cases[9] = 30;

    for (int i = 0; i < 10; i++) {
        string filename = string("data/") + (i < 9 ? "0" : "") + to_string(i + 1) + ".in";
        ofstream fout(filename);
        fout << test_cases[i] << "\n";
        fout.close();
        cout << "Generated " << filename << " with D=" << test_cases[i] << "\n";
    }

    return 0;
}

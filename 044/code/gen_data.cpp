#include <bits/stdc++.h>
using namespace std;

int rand_int(int l, int r) {
    return l + rand() % (r - l + 1);
}

int main() {
    system("mkdir -p data");
    srand(time(0));

    vector<int> test_cases(10);

    // 1: sample (M=3000, answer = 5482660, original PE answer)
    test_cases[0] = 3000;

    // 2-3: smallest valid M range
    test_cases[1] = 2500;
    test_cases[2] = 2600;

    // 4-6: medium M
    for (int i = 3; i < 6; i++) {
        test_cases[i] = rand_int(2500, 2750);
    }

    // 7: max
    test_cases[6] = 3000;

    // 8: boundary (minimum known to work)
    test_cases[7] = 2500;

    // 9-10: random larger values
    for (int i = 8; i < 10; i++) {
        test_cases[i] = rand_int(2600, 3000);
    }

    for (int i = 0; i < 10; i++) {
        string filename = string("data/") + (i < 9 ? "0" : "") + to_string(i + 1) + ".in";
        ofstream fout(filename);
        fout << test_cases[i] << "\n";
        fout.close();
        cout << "Generated " << filename << " with M = " << test_cases[i] << "\n";
    }

    return 0;
}

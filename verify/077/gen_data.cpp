#include <bits/stdc++.h>
using namespace std;

int rand_int(int l, int r) {
    return l + rand() % (r - l + 1);
}

int main() {
    system("mkdir -p data");
    srand(time(0));

    vector<int> test_cases(10);

    // 1: sample - K=5 (answer: 11, since >5 ways needed)
    test_cases[0] = 5;

    // 2-3: small K
    test_cases[1] = rand_int(1, 50);
    test_cases[2] = rand_int(1, 100);

    // 4-6: medium K
    test_cases[3] = rand_int(100, 1000);
    test_cases[4] = rand_int(500, 2000);
    test_cases[5] = rand_int(1000, 3000);

    // 7: minimum boundary
    test_cases[6] = 1;

    // 8: maximum boundary
    test_cases[7] = 5000;

    // 9-10: random
    test_cases[8] = rand_int(2000, 4000);
    test_cases[9] = rand_int(3000, 4999);

    for (int i = 0; i < 10; i++) {
        string filename = string("data/") + (i < 9 ? "0" : "") + to_string(i + 1) + ".in";
        ofstream fout(filename);
        fout << test_cases[i] << "\n";
        fout.close();
        cout << "Generated " << filename << " with K = " << test_cases[i] << "\n";
    }

    return 0;
}

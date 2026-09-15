#include<bits/stdc++.h>
using namespace std;
#define ll long long

int main() {
    system("mkdir -p data");
    srand(time(0));

    struct Test { int D, K; };
    vector<Test> tests(10);

    // 1: PE original (D=16, K=6) -> answer: 542934735751917735
    tests[0] = {16, 6};

    // 2: given example (D=6, K=3) -> answer: 27280188
    tests[1] = {6, 3};

    // 3-4: tiny
    tests[2] = {2, 1};
    tests[3] = {3, 2};

    // 5-6: small
    tests[4] = {4, 2};
    tests[5] = {5, 2};

    // 7-8: medium
    tests[6] = {8, 3};
    tests[7] = {10, 3};

    // 9-10: larger
    tests[8] = {12, 4};
    tests[9] = {14, 5};

    for (int i = 0; i < 10; i++) {
        string filename = string("data/") + (i < 9 ? "0" : "") + to_string(i + 1) + ".in";
        ofstream fout(filename);
        fout << tests[i].D << " " << tests[i].K << "\n";
        fout.close();
        cout << "Generated " << filename << " with D=" << tests[i].D << " K=" << tests[i].K << "\n";
    }

    return 0;
}

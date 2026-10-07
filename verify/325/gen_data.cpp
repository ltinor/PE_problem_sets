#include<bits/stdc++.h>
using namespace std;
#define ll long long

int main() {
    system("mkdir -p data");
    srand(time(0));

    vector<string> tests(10);

    // 1: PE original
    tests[0] = "10000000000000000"; // 10^16

    // 2-5: verification
    tests[1] = "10";
    tests[2] = "10000";
    tests[3] = "20";
    tests[4] = "30";

    // 6-7: small
    tests[5] = "5";
    tests[6] = "8";

    // 8-10: moderate
    tests[7] = "50";
    tests[8] = "100";
    tests[9] = "200";

    for (int i = 0; i < 10; i++) {
        string filename = string("data/") + (i < 9 ? "0" : "") + to_string(i + 1) + ".in";
        ofstream fout(filename);
        fout << tests[i] << "\n";
        fout.close();
        cout << "Generated " << filename << "\n";
    }

    return 0;
}

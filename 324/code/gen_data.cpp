#include<bits/stdc++.h>
using namespace std;

int main() {
    system("mkdir -p data");
    srand(time(0));

    vector<string> tests(10);

    // 1: PE original: 10^10000
    tests[0] = "1" + string(10000, '0'); // 10^10000

    // 2-5: verification values from problem
    tests[1] = "2";
    tests[2] = "4";
    tests[3] = "10";
    tests[4] = "1000";

    // 6: 10^6
    tests[5] = "1000000";

    // 7-8: small random
    tests[6] = "3";
    tests[7] = "5";

    // 9-10: moderate
    tests[8] = "20";
    tests[9] = "50";

    for (int i = 0; i < 10; i++) {
        string filename = string("data/") + (i < 9 ? "0" : "") + to_string(i + 1) + ".in";
        ofstream fout(filename);
        fout << tests[i] << "\n";
        fout.close();
        cout << "Generated " << filename << "\n";
    }

    return 0;
}

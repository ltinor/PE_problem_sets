#include<bits/stdc++.h>
using namespace std;

double rand_double(double l, double r) {
    return l + (double)rand() / RAND_MAX * (r - l);
}

int main() {
    system("mkdir -p data");
    srand(time(0));

    struct Test { double h, v, g; };
    vector<Test> tests(10);

    // 1: PE original (h=100, v=20, g=9.81) -> answer: 1856532.8455
    tests[0] = {100, 20, 9.81};

    // 2-3: small
    tests[1] = {1, 1, 9.81};
    tests[2] = {5, 5, 9.81};

    // 4-5: medium
    tests[3] = {10, 10, 9.81};
    tests[4] = {50, 15, 9.81};

    // 6: different g (moon)
    tests[5] = {100, 20, 1.62};

    // 7-8: large
    tests[6] = {200, 30, 9.81};
    tests[7] = {500, 50, 9.81};

    // 9-10: random
    tests[8] = {rand_double(10, 100), rand_double(5, 40), 9.81};
    tests[9] = {rand_double(50, 150), rand_double(10, 25), 9.81};

    for (int i = 0; i < 10; i++) {
        string filename = string("data/") + (i < 9 ? "0" : "") + to_string(i + 1) + ".in";
        ofstream fout(filename);
        fout << fixed << setprecision(2) << tests[i].h << " " << tests[i].v << " " << tests[i].g << "\n";
        fout.close();
        cout << "Generated " << filename << "\n";
    }

    return 0;
}

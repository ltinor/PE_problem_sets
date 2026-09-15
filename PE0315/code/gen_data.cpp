#include <bits/stdc++.h>
using namespace std;

long long rand_ll(long long l, long long r) {
    return l + (long long)(rand()) * (long long)(rand()) % (r - l + 1);
}

int main() {
    system("mkdir -p data");
    srand(time(0));

    vector<pair<int,int>> test_cases(10);

    // 1. 样例: small primes
    test_cases[0] = {2, 20};

    // 2-3. 小区间
    test_cases[1] = {1, 30};
    test_cases[2] = {100, 200};

    // 4-5. 中等区间
    test_cases[3] = {1000, 2000};
    test_cases[4] = {100000, 110000};

    // 6-8. 大区间 (接近原题)
    test_cases[5] = {10000000, 10100000};
    test_cases[6] = {15000000, 15200000};
    test_cases[7] = {19900000, 20000000};

    // 9-10. 随机区间
    for (int i = 8; i < 10; i++) {
        int A = rand_ll(1, 20000000);
        int B = A + rand_ll(10000, 200000);
        if (B > 20000000) B = 20000000;
        test_cases[i] = {A, B};
    }

    for (int i = 0; i < 10; i++) {
        string fname = string("data/") + (i < 9 ? "0" : "") + to_string(i + 1) + ".in";
        ofstream fout(fname);
        fout << test_cases[i].first << " " << test_cases[i].second << "\n";
        fout.close();
        cout << "Generated " << fname << " with A=" << test_cases[i].first
             << " B=" << test_cases[i].second << "\n";
    }
    return 0;
}

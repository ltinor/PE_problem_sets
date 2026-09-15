#include <bits/stdc++.h>
using namespace std;

long long rand_ll(long long l, long long r) {
    return l + (long long)(rand()) * (long long)(rand()) % (r - l + 1);
}

int main() {
    system("mkdir -p data");
    srand(time(0));

    vector<pair<int,int>> test_cases(10);

    // PE answer (K=40,N=9,ans=843296) verified separately — not included in test data for speed
    // 1: sample
    test_cases[0] = {1, 1};

    // 2-6: small to medium
    test_cases[1] = {3, 2};
    test_cases[2] = {5, 3};
    test_cases[3] = {10, 5};
    test_cases[4] = {8, 4};
    test_cases[5] = {15, 6};

    // 7-10: moderate
    test_cases[6] = {20, 7};
    test_cases[7] = {20, 8};
    test_cases[8] = {20, 9};
    test_cases[9] = {(int)rand_ll(10, 20), (int)rand_ll(5, 9)};

    for (int i = 0; i < 10; i++) {
        string filename = string("data/") + (i < 9 ? "0" : "") + to_string(i + 1) + ".in";
        ofstream fout(filename);
        fout << test_cases[i].first << " " << test_cases[i].second << "\n";
        fout.close();
        cout << "Generated " << filename << " with K=" << test_cases[i].first << " N=" << test_cases[i].second << "\n";
    }

    return 0;
}

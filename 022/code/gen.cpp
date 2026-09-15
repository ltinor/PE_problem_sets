#include<bits/stdc++.h>
using namespace std;

long long rand_ll(long long l, long long r) {
    return l + (long long)rand() * rand() % (r - l + 1);
}

string rand_name(int len) {
    string s;
    for (int i = 0; i < len; i++) {
        s += (char)('A' + rand() % 26);
    }
    return s;
}

int main(int argc, char* argv[]) {
    srand(time(0));

    string mode = "small";
    if (argc > 1) mode = argv[1];

    int N;

    if (mode == "small") {
        N = rand_ll(1, 5);
    } else if (mode == "large") {
        N = rand_ll(1, 50);
    } else {
        N = 10;
    }

    assert(N >= 1 && N <= 50);

    cout << N << "\n";
    for (int i = 0; i < N; i++) {
        int len = rand_ll(2, 6);
        cout << rand_name(len) << "\n";
    }
}

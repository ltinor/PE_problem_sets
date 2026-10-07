#include<bits/stdc++.h>
using namespace std;

long long rand_ll(long long l, long long r) {
    return l + (long long)rand() * rand() % (r - l + 1);
}

int main(int argc, char* argv[]) {
    srand(time(0));

    string mode = "small";
    if (argc > 1) mode = argv[1];

    int m;
    if (mode == "small") {
        m = rand_ll(1, 20);
    } else if (mode == "large") {
        m = rand_ll(1, 1000);
    }

    assert(m >= 1 && m <= 1000);

    cout << "1\n" << m << "\n";
}

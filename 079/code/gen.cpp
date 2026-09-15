#include<bits/stdc++.h>
using namespace std;

int rand_int(int l, int r) {
    return l + rand() % (r - l + 1);
}

int main(int argc, char* argv[]) {
    srand(time(0));

    string mode = "small";
    if (argc > 1) mode = argv[1];

    int N;

    if (mode == "small") {
        N = rand_int(3, 10);
    } else if (mode == "large") {
        N = rand_int(40, 50);
    }

    cout << N << "\n";

    // Generate a random passcode with 5-8 digits
    int len = rand_int(3, 8);
    string passcode;
    set<char> used;
    for (int i = 0; i < len; i++) {
        char c;
        do {
            c = '0' + rand_int(0, 9);
        } while (used.count(c));
        used.insert(c);
        passcode += c;
    }

    // Generate N random 3-digit subsequences
    for (int i = 0; i < N; i++) {
        int a = rand_int(0, len - 3);
        int b = rand_int(a + 1, len - 2);
        int c = rand_int(b + 1, len - 1);
        cout << passcode[a] << passcode[b] << passcode[c] << "\n";
    }

    return 0;
}

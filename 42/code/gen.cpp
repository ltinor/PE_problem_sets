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
        N = rand_int(1, 100);
    } else {
        N = rand_int(500, 2000);
    }

    cout << N << "\n";
    for (int i = 0; i < N; i++) {
        int len = rand_int(1, 15);
        string word;
        for (int j = 0; j < len; j++) {
            word += (char)('A' + rand() % 26);
        }
        cout << word << "\n";
    }

    return 0;
}

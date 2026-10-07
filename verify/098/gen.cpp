#include<bits/stdc++.h>
using namespace std;

int rand_int(int l, int r) {
    return l + rand() % (r - l + 1);
}

string rand_word(int len) {
    string s;
    for (int i = 0; i < len; i++) {
        s += (char)('A' + rand_int(0, 25));
    }
    return s;
}

// Generate an anagram of s
string anagram(const string& s) {
    string t = s;
    static mt19937 rng(rand());
    shuffle(t.begin(), t.end(), rng);
    return t;
}

int main(int argc, char* argv[]) {
    srand(time(0));

    string mode = "small";
    if (argc > 1) mode = argv[1];

    if (mode == "small") {
        int N = rand_int(3, 20);
        cout << N << "\n";
        // Generate 2-3 anagram pairs
        int pairs = rand_int(1, 3);
        set<string> used;
        for (int p = 0; p < pairs; p++) {
            int len = rand_int(3, 5);
            string base;
            do {
                base = rand_word(len);
            } while (used.count(base));
            used.insert(base);
            cout << base << "\n";
            cout << anagram(base) << "\n";
            N -= 2;
        }
        // Fill rest with random words
        while (N > 0) {
            int len = rand_int(3, 5);
            string w = rand_word(len);
            if (!used.count(w)) {
                used.insert(w);
                cout << w << "\n";
                N--;
            }
        }
    } else {
        int N = rand_int(50, 200);
        cout << N << "\n";
        set<string> used;
        int pairs = rand_int(5, 15);
        for (int p = 0; p < pairs; p++) {
            int len = rand_int(3, 6);
            string base;
            do {
                base = rand_word(len);
            } while (used.count(base));
            used.insert(base);
            cout << base << "\n";
            cout << anagram(base) << "\n";
            N -= 2;
        }
        while (N > 0) {
            int len = rand_int(3, 6);
            string w = rand_word(len);
            if (!used.count(w)) {
                used.insert(w);
                cout << w << "\n";
                N--;
            }
        }
    }

    return 0;
}

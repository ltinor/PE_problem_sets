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

string anagram(const string& s) {
    string t = s;
    static mt19937 rng(rand());
    shuffle(t.begin(), t.end(), rng);
    return t;
}

void generate_test(ofstream& fout, int N, int min_len, int max_len, int min_pairs, int max_pairs) {
    fout << N << "\n";
    set<string> used;
    int pairs = rand_int(min_pairs, max_pairs);
    for (int p = 0; p < pairs && N >= 2; p++) {
        int len = rand_int(min_len, max_len);
        string base;
        do {
            base = rand_word(len);
        } while (used.count(base));
        used.insert(base);
        fout << base << "\n";
        fout << anagram(base) << "\n";
        N -= 2;
    }
    while (N > 0) {
        int len = rand_int(min_len, max_len);
        string w = rand_word(len);
        if (!used.count(w)) {
            used.insert(w);
            fout << w << "\n";
            N--;
        }
    }
}

int main() {
    system("mkdir -p data");
    srand(time(0));

    // 1: sample (CARE/RACE pair from original PE)
    {
        ofstream fout("data/01.in");
        fout << "4\nCARE\nRACE\nHELLO\nWORLD\n";
        fout.close();
        cout << "Generated data/01.in (sample)\n";
    }

    // 2: small test
    {
        ofstream fout("data/02.in");
        fout << "6\nACT\nCAT\nTAC\nDOG\nGOD\nXYZ\n";
        fout.close();
        cout << "Generated data/02.in (small anagrams)\n";
    }

    // 3-5: random small
    for (int i = 2; i < 5; i++) {
        string filename = string("data/0") + to_string(i + 1) + ".in";
        ofstream fout(filename);
        generate_test(fout, rand_int(10, 30), 3, 5, 2, 5);
        fout.close();
        cout << "Generated " << filename << "\n";
    }

    // 6-8: random medium
    for (int i = 5; i < 8; i++) {
        string filename = string("data/0") + to_string(i + 1) + ".in";
        ofstream fout(filename);
        generate_test(fout, rand_int(50, 200), 3, 6, 5, 15);
        fout.close();
        cout << "Generated " << filename << "\n";
    }

    // 9-10: boundary (no anagrams)
    {
        ofstream fout("data/09.in");
        fout << "10\n";
        for (int i = 0; i < 10; i++) {
            fout << rand_word(rand_int(3, 5)) << "\n";
        }
        fout.close();
        cout << "Generated data/09.in (no anagrams)\n";
    }

    {
        ofstream fout("data/10.in");
        generate_test(fout, 200, 4, 6, 10, 20);
        fout.close();
        cout << "Generated data/10.in (many anagrams)\n";
    }

    return 0;
}

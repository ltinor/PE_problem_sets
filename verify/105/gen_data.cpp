#include <bits/stdc++.h>
using namespace std;

int rand_int(int l, int r) {
    return l + rand() % (r - l + 1);
}

// Generate a known special sum set of size n (near-optimum heuristic)
vector<int> gen_special_set(int n) {
    vector<vector<int>> known = {
        {1}, {1,2}, {2,3,4}, {3,5,6,7}, {6,9,11,12,13},
        {11,18,19,20,22,25}, {20,31,38,39,40,42,45}
    };
    if (n <= 7) return known[n-1];
    auto prev = known[6];
    int b = prev[prev.size()/2];
    vector<int> res = {b};
    for (int x : prev) res.push_back(x + b);
    return res;
}

// Generate a random set (may or may not be special)
vector<int> gen_random_set(int m) {
    set<int> s;
    while ((int)s.size() < m) {
        s.insert(rand_int(1, 200));
    }
    return vector<int>(s.begin(), s.end());
}

int main() {
    system("mkdir -p data");
    srand(time(0));

    for (int case_idx = 0; case_idx < 10; case_idx++) {
        string filename = string("data/") + (case_idx < 9 ? "0" : "") + to_string(case_idx + 1) + ".in";
        ofstream fout(filename);

        int N = 0;
        vector<vector<int>> sets;

        if (case_idx == 0) {
            // Sample: the two examples from PE problem
            sets.push_back({81, 88, 75, 42, 87, 84, 86, 65});    // NOT special
            sets.push_back({157, 150, 164, 119, 79, 159, 161, 139, 158}); // IS special, sum=1286
            N = 2;
        } else if (case_idx == 1) {
            // Small: a few random small sets
            N = rand_int(3, 6);
            for (int i = 0; i < N; i++) sets.push_back(gen_random_set(rand_int(3, 6)));
        } else if (case_idx == 2) {
            // Mix of special and random sets
            N = 5;
            sets.push_back(gen_special_set(3));  // {2,3,4} - special
            sets.push_back(gen_random_set(4));
            sets.push_back(gen_special_set(5));  // {6,9,11,12,13} - special
            sets.push_back(gen_random_set(6));
            sets.push_back(gen_special_set(6));  // {11,18,19,20,22,25} - special
        } else if (case_idx <= 5) {
            // Medium random
            N = rand_int(5, 10);
            for (int i = 0; i < N; i++) sets.push_back(gen_random_set(rand_int(5, 8)));
        } else if (case_idx <= 7) {
            // Large random
            N = rand_int(15, 30);
            for (int i = 0; i < N; i++) sets.push_back(gen_random_set(rand_int(6, 10)));
        } else {
            // Large: ~50 random sets
            N = 50;
            for (int i = 0; i < N; i++) sets.push_back(gen_random_set(rand_int(6, 12)));
        }

        fout << N << "\n";
        for (auto& s : sets) {
            fout << s.size();
            for (int x : s) fout << " " << x;
            fout << "\n";
        }
        fout.close();
        cout << "Generated " << filename << " with " << N << " sets\n";
    }

    return 0;
}

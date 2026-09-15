#include <bits/stdc++.h>
using namespace std;

mt19937 rng(time(0)); 

int rand_int(int l, int r) {
    return uniform_int_distribution<int>(l, r)(rng);
}


void gen_case(const string &filename, const vector<int> &manual_data, int T_random = 0, int n_min = 1, int n_max = 10000000) {
    system("mkdir -p data");  
    string filepath = "data/" + filename;
    ofstream fout(filepath);

    int T = manual_data.size() + T_random;
    fout << T << '\n';

    for(int x : manual_data) fout << x << '\n';
    for(int i = 0; i < T_random; i++) fout << rand_int(n_min, n_max) << '\n';

    fout.close();
    cout << "Generated " << filepath << endl;
}

int main() {

    gen_case("1.in", {10}, 0, 1, 10);

    {
        vector<int> manual;
        for(int i = 1; i <= 1e4; i++) manual.push_back(i);
        gen_case("2.in", manual, 0, 1, 1e4);
    }

    {
        vector<int> manual;
        for(int i = 0; i < 1e4; i++) manual.push_back(1e5 - i);
        gen_case("3.in", manual, 0, 1, 1e5  );
    }
    for(int i = 4; i <= 9; i++) gen_case(to_string(i) + ".in", {}, 1e4, 1, 1e5);
    gen_case("10.in", {}, 1e4, 5e4, 1e5);

    return 0;
}
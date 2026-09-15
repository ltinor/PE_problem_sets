#include<bits/stdc++.h>
using namespace std;
using ll = long long;

ll rand_ll(ll l, ll r) {
    return l + (ll)rand() * rand() % (r - l + 1);
}

int main() {
    system("mkdir -p data");
    srand(time(0));
    
    vector<ll> test_cases(10);
    
    // 1: Sample - Q(8) = 2714886
    test_cases[0] = 8;
    
    // 2-3: Small
    for (int i = 1; i < 3; i++)
        test_cases[i] = rand_ll(1, 100);
    
    // 4-6: Medium-large
    for (int i = 3; i < 6; i++)
        test_cases[i] = rand_ll(1e6, 1e10);
    
    // 7-8: Boundary
    test_cases[6] = 1;
    test_cases[7] = 1000000000000LL;
    
    // 9-10: Random large
    for (int i = 8; i < 10; i++)
        test_cases[i] = rand_ll(1e10, 1e12);
    
    for (int i = 0; i < 10; i++) {
        string fname = "data/" + string(i < 9 ? "0" : "") + to_string(i + 1) + ".in";
        ofstream fout(fname);
        fout << test_cases[i] << "\n";
        fout.close();
        cout << "Generated " << fname << " N=" << test_cases[i] << "\n";
    }
    return 0;
}

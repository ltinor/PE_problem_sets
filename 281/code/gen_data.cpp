#include<bits/stdc++.h>
using namespace std;

int main() {
    system("mkdir -p data");
    
    vector<long long> tests = {
        1,      // only f(2,1)=1
        2,      // f(2,1)+f(2,2)=3, f(3,1)=2 → 1+2+2=5? Actually sum f≤2: f(2,1)=1, f(2,2)=2, f(3,1)=2 → sum=5
        5,
        10,
        20,
        50,
        100,
        1000,
        1000000000000000LL  // PE answer: 1485776387445626
    };
    
    for (int i = 0; i < (int)tests.size(); i++) {
        string fname = string("data/") + (i < 9 ? "0" : "") + to_string(i + 1) + ".in";
        ofstream fout(fname);
        fout << tests[i] << "\n";
        fout.close();
        cout << "Generated " << fname << "\n";
    }
    return 0;
}

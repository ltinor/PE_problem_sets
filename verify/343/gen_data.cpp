#include<bits/stdc++.h>
using namespace std;

int main() {
    system("mkdir -p data");
    
    // PE: K = 2*10^6, answer = 821533053
    // OJ: K up to 200000
    int cases[] = {10, 100, 500, 1000, 5000, 10000, 20000, 50000, 100000, 200000};
    
    for (int i = 0; i < 10; i++) {
        string fn = string("data/") + (i < 9 ? "0" : "") + to_string(i + 1) + ".in";
        ofstream f(fn);
        f << cases[i] << "\n";
        f.close();
        cout << "Generated " << fn << " K=" << cases[i] << "\n";
    }
    return 0;
}

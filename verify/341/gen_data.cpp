#include<bits/stdc++.h>
using namespace std;

int main() {
    system("mkdir -p data");
    
    // PE: N = 10^6, answer = 5609861067637700
    // OJ: N up to 3000
    int cases[] = {10, 20, 50, 100, 200, 500, 1000, 1500, 2000, 3000};
    
    for (int i = 0; i < 10; i++) {
        string fn = string("data/") + (i < 9 ? "0" : "") + to_string(i + 1) + ".in";
        ofstream f(fn);
        f << cases[i] << "\n";
        f.close();
        cout << "Generated " << fn << " N=" << cases[i] << "\n";
    }
    return 0;
}

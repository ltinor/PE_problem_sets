#include <bits/stdc++.h>
using namespace std;
int main(){
    system("mkdir -p data");
    // 01: sample / PE answer (K=5 -> 26033)
    ofstream("data/01.in") << "5\n";
    for(int K=2;K<=5;K++){
        string fn = string("data/") + (K<10?"0":"") + to_string(K) + ".in";
        ofstream f(fn);
        f << K << "\n";
    }
    for(int id=6;id<=10;id++){
        string fn = string("data/") + (id<10?"0":"") + to_string(id) + ".in";
        ofstream f(fn);
        f << (id%3+2) << "\n";  // mix of K=2,3,4
    }
}

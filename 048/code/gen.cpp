#include<bits/stdc++.h>
using namespace std;
#define ll long long

int main(int argc, char* argv[]){
    srand(time(0));
    
    string mode = "small";
    if(argc > 1) mode = argv[1];
    
    ll N;
    if(mode == "small"){
        N = rand() % 1000 + 1; // 1..1000, smaller range for brute
    } else {
        N = rand() % 100001 + 1; // 1..100k
    }
    
    cout << N << "\n";
    return 0;
}

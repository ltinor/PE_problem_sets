#include<bits/stdc++.h>
using namespace std;

int main(int argc, char* argv[]){
    srand(time(0));
    
    string mode = "small";
    if(argc > 1) mode = argv[1];
    
    int N;
    if(mode == "small"){
        N = rand() % 10000 + 2; // 2..10001
    } else {
        N = rand() % 100001 + 2; // 2..100001
    }
    
    cout << N << "\n";
    return 0;
}

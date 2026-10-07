#include<bits/stdc++.h>
using namespace std;

int main(int argc, char* argv[]){
    srand(time(0));
    
    string mode = "small";
    if(argc > 1) mode = argv[1];
    
    int K;
    if(mode == "small"){
        K = rand() % 4 + 1; // 1..4
    } else {
        K = rand() % 4 + 1;
    }
    
    cout << K << "\n";
    return 0;
}

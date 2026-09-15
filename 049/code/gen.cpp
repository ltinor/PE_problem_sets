#include<bits/stdc++.h>
using namespace std;

int main(int argc, char* argv[]){
    srand(time(0));
    
    string mode = "small";
    if(argc > 1) mode = argv[1];
    
    int D;
    // Only D=4 is practical for brute; D=5,6 for std only
    if(mode == "small"){
        D = 4 + rand() % 3; // 4, 5, or 6
    } else {
        D = 4 + rand() % 3;
    }
    
    cout << D << "\n";
    return 0;
}

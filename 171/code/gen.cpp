#include<bits/stdc++.h>
using namespace std;

int rand_int(int l, int r){
    return l + rand() % (r - l + 1);
}

int main(int argc, char* argv[]){
    srand(time(0));
    string mode = "small";
    if(argc > 1) mode = argv[1];

    int D;
    if(mode == "small"){
        D = rand_int(1, 6);
    } else {
        D = rand_int(7, 20);
    }
    cout << D << "\n";
}

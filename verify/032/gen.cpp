#include<bits/stdc++.h>
using namespace std;

int main(int argc, char* argv[]){
    srand(time(0));

    string mode = "small";
    if(argc > 1) mode = argv[1];

    int n;

    if(mode == "small"){
        // Small: N = 5, 6, 7
        n = 5 + rand() % 3;
    }
    else if(mode == "large"){
        n = 9;
    }
    else {
        n = 5 + rand() % 5;
    }

    assert(n >= 1 && n <= 9);

    cout << n << "\n";
}

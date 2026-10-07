#include<bits/stdc++.h>
using namespace std;

int rand_int(int l, int r){
    return l + rand() % (r - l + 1);
}

int main(int argc, char* argv[]){
    srand(time(0));

    string mode = "small";
    if(argc > 1) mode = argv[1];

    int n;

    if(mode == "small"){
        n = rand_int(1, 2000);
    }
    else if(mode == "large"){
        n = rand_int(1, 100000);
    }
    else {
        n = rand_int(1, 100000);
    }

    assert(n >= 1 && n <= 100000);

    cout << n << "\n";
}

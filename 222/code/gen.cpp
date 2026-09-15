#include<bits/stdc++.h>
using namespace std;

int rand_int(int l, int r) {
    return l + rand() % (r - l + 1);
}

int main(int argc, char* argv[]){
    srand(time(0));

    string mode = "small";
    if(argc > 1) mode = argv[1];

    int N, R;

    if(mode == "small"){
        N = rand_int(2, 8);
        R = rand_int(40, 60);
    } else if(mode == "large"){
        N = rand_int(10, 16);
        R = 50;
    }

    cout << N << " " << R << "\n";
    return 0;
}

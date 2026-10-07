#include<bits/stdc++.h>
using namespace std;

int rand_int(int l, int r){
    return l + rand() % (r - l + 1);
}

int main(int argc, char* argv[]){
    srand(time(0));

    string mode = "small";
    if(argc > 1) mode = argv[1];

    int R;
    if(mode == "small"){
        R = rand_int(2, 15);
    } else {
        R = rand_int(16, 100);
    }

    cout << R << "\n";
    for(int i = 0; i < R; i++){
        for(int j = 0; j <= i; j++){
            if(j > 0) cout << " ";
            cout << rand_int(0, 99);
        }
        cout << "\n";
    }
    return 0;
}

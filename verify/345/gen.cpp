#include<bits/stdc++.h>
using namespace std;

int rand_int(int l, int r) {
    return l + rand() % (r - l + 1);
}

int main(int argc, char* argv[]) {
    srand(time(0));
    
    string mode = "small";
    if (argc > 1) mode = argv[1];
    
    int n;
    if (mode == "small") {
        n = rand_int(3, 7);
    } else {
        n = rand_int(8, 15);
    }
    
    cout << n << "\n";
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << rand_int(1, 1000) << (j+1 < n ? " " : "\n");
        }
    }
    return 0;
}

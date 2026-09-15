#include<bits/stdc++.h>
using namespace std;

int rand_int(int l, int r) {
    return l + rand() % (r - l + 1);
}

int main(int argc, char* argv[]) {
    srand(time(0));
    string mode = "small";
    if (argc > 1) mode = argv[1];
    
    if (mode == "small") {
        int n = rand_int(5, 12);
        int c = rand_int(1, min(3, n-1));
        cout << n << " " << c << "\n";
    } else {
        int n = rand_int(10, 20);
        int c = rand_int(2, min(5, n-1));
        cout << n << " " << c << "\n";
    }
    return 0;
}

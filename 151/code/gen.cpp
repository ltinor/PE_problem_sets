#include<bits/stdc++.h>
using namespace std;

long long rand_ll(long long l, long long r) {
    return l + (long long)rand() * rand() % (r - l + 1);
}

int main(int argc, char* argv[]) {
    srand(time(0));
    
    string mode = "small";
    if (argc > 1) mode = argv[1];
    
    // Fixed-answer problem: output a dummy value
    int dummy = 1;
    
    if (mode == "small") {
        dummy = 1;
    } else if (mode == "large") {
        dummy = 1;
    }
    
    cout << dummy << "\n";
    return 0;
}

#include<bits/stdc++.h>
using namespace std;

long long rand_ll(long long l, long long r) {
    return l + (long long)rand() * rand() % (r - l + 1);
}

int main(int argc, char* argv[]) {
    srand(time(0));
    string mode = "small";
    if(argc > 1) mode = argv[1];

    int W, H;
    if(mode == "small"){
        W = rand_ll(2, 4);
        H = rand_ll(2, 4);
        while((W*H)%3 != 0){ W = rand_ll(2,4); H = rand_ll(2,4); }
    } else {
        W = rand_ll(5, 12);
        H = rand_ll(5, 12);
        while((W*H)%3 != 0){ W = rand_ll(5,12); H = rand_ll(5,12); }
    }

    cout << W << " " << H << "\n";
}

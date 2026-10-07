#include<bits/stdc++.h>
using namespace std;

int rand_int(int l, int r){
    return l + rand() % (r - l + 1);
}

int main(int argc, char* argv[]){
    srand(time(0));

    string mode = "small";
    if(argc > 1) mode = argv[1];

    int a, b, c, d;

    if(mode == "small"){
        // Small for brute force: total outcomes ≤ 6^6 ≈ 46656
        a = rand_int(1, 4);
        b = rand_int(2, 6);
        c = rand_int(1, 4);
        d = rand_int(2, 6);
    } else {
        a = rand_int(2, 10);
        b = rand_int(2, 20);
        c = rand_int(2, 10);
        d = rand_int(2, 20);
    }

    assert(a >= 1 && a <= 10);
    assert(b >= 2 && b <= 20);
    assert(c >= 1 && c <= 10);
    assert(d >= 2 && d <= 20);

    cout << a << " " << b << " " << c << " " << d << "\n";
}

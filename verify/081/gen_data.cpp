#include <bits/stdc++.h>
using namespace std;
#define ll long long

ll rand_ll(ll l, ll r) {
    return l + (ll)(rand()) * (ll)(rand()) % (r - l + 1);
}

void gen_one(ofstream &fout, int N) {
    fout << N << "\n";
    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++){
            fout << rand_ll(1, 9999);
            if(j < N - 1) fout << " ";
        }
        fout << "\n";
    }
}

int main() {
    system("mkdir -p data");
    srand(time(0));

    for(int i = 0; i < 10; i++){
        string filename = string("data/") + (i < 9 ? "0" : "") + to_string(i + 1) + ".in";
        ofstream fout(filename);

        if(i == 0){
            // sample: small 3x3
            gen_one(fout, 3);
        } else if(i == 1 || i == 2){
            // small: 2-5
            gen_one(fout, rand_ll(2, 5));
        } else if(i >= 3 && i <= 5){
            // medium: 10-30
            gen_one(fout, rand_ll(10, 30));
        } else if(i >= 6 && i <= 8){
            // large: 60-80
            gen_one(fout, rand_ll(60, 80));
        } else {
            // max: 80
            gen_one(fout, 80);
        }

        fout.close();
        cout << "Generated " << filename << "\n";
    }

    return 0;
}

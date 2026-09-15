#include <bits/stdc++.h>
using namespace std;

mt19937 rng(time(0));

int rand_int(int l, int r) {
    return uniform_int_distribution<int>(l, r)(rng);
}

void gen_case(const string &filename, const vector<int> &manual_data, int T_random = 0, int S_min = 1, int S_max = 1000) {
    system("mkdir -p data");  
    ofstream fout("data/" + filename);

    int T = manual_data.size() + T_random;
    fout << T << "\n";

    for(int s : manual_data) fout << s << "\n";

    for(int i = 0; i < T_random; i++) {
        int S;
        if(i % 2 == 0) {
            int a, b, c, m, n;
            while(true) {
                n = rand_int(1, 20);
                m = rand_int(n+1, n+20);
                a = m*m - n*n;
                b = 2*m*n;
                c = m*m + n*n;
                S = a + b + c;
                if(S <= S_max) break;
            }
        } else {
            S = rand_int(S_min, S_max);
            while(true) {
                bool found = false;
                for(int a=1; a<S/3; a++){
                    for(int b=a+1; b<S/2; b++){
                        int c = S - a - b;
                        if(c <= b) continue;
                        if(a*a + b*b == c*c){
                            found = true;
                            break;
                        }
                    }
                    if(found) break;
                }
                if(!found) break;
                S++;
            }
        }
        fout << S << "\n";
    }

    fout.close();
    cout << "Generated data/" << filename << endl;
}

int main() {
    gen_case("1.in", {12, 11}, 0, 1, 1000);

    gen_case("2.in", {1000}, 0, 1, 1000);

    for(int i = 3; i <= 5; i++){
        gen_case(to_string(i) + ".in", {}, 100, 1, 1000);
    }

    for(int i = 6; i <= 10; i++){
        gen_case(to_string(i) + ".in", {}, 1000, 1, 3000);
    }

    return 0;
}
#include <bits/stdc++.h>
using namespace std;

mt19937 rng(time(0));

int rand_int(int l, int r) {
    return uniform_int_distribution<int>(l, r)(rng);
}

struct ManualCase {
    int L, K;
    string S;  
};


void gen_case(const string &filename, const vector<ManualCase> &manual_cases, int T_random = 0, int L_min = 1, int L_max = 1000, int K_max = 100) {
    system("mkdir -p data");  
    string filepath = "data/" + filename;
    ofstream fout(filepath);

    int T = manual_cases.size() + T_random;
    fout << T << "\n";

    for(auto &c : manual_cases){
        fout << c.L << " " << c.K << "\n";
        fout << c.S << "\n";
    }

    for(int i = 0; i < T_random; i++){
        int L = rand_int(L_min, L_max);
        int K = rand_int(1, min(L, K_max));
        fout << L << " " << K << "\n";
        for(int j = 0; j < L; j++) fout << rand_int(0,9);
        fout << "\n";
    }

    fout.close();
    cout << "Generated " << filepath << endl;
}

int main() {
    vector<ManualCase> sample = {
        {10,2,"1234567890"},
        {5,3,"36791"},
    };
    gen_case("1.in", sample, 0);

    vector<ManualCase> zero_case = {
        {10,5,"0000000000"},
        {15,4,"102030405060708"},
        {12,3,"900800700600"},
        {1000,13,"7316717653133062491922511967442657474235534919493496983520312774506326239578318016984801869478851843858615607891129494954595017379583319528532088055111254069874715852386305071569329096329522744304355766896648950445244523161731856403098711121722383113622298934233803081353362766142828064444866452387493035890729629049156044077239071381051585930796086670172427121883998797908792274921901699720888093776657273330010533678812202354218097512545405947522435258490771167055601360483958644670632441572215539753697817977846174064955149290862569321978468622482839722413756570560574902614079729686524145351004748216637048440319989000889524345065854122758866688116427171479924442928230863465674813919123162824586178664583591245665294765456828489128831426076900422421902267105562632111110937054421750694165896040807198403850962455444362981230987879927244284909188845801561660979191338754992005240636899125607176060588611646710940507754100225698315520005593572972571636269561882670428252483600823257530420752963450"}
    };
    gen_case("2.in", zero_case, 0);

    vector<ManualCase> special_case = {};
    for(int i = 0; i < 1e4; i++) {
        string s = "";
        for(int j = 0; j < 1e3; j++) {
            if(j%15==0) s+="0";
            else s+=to_string(rand_int(0,9));
        }
        special_case.push_back({1000,15,s});
    }

    gen_case("3.in", special_case, 0);

    for(int i = 4; i <= 9; i++){
        gen_case(to_string(i) + ".in", {}, 10000, 100, 1000, 15);
    }

    gen_case("10.in", {}, 10000, 900, 1000, 15);

    return 0;
}
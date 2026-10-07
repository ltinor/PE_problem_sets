#include <bits/stdc++.h>
using namespace std;

int rand_int(int l, int r){
    return l + rand() % (r - l + 1);
}

string int_to_roman(int num){
    vector<pair<int, string>> vals = {
        {1000, "M"}, {900, "CM"}, {500, "D"}, {400, "CD"},
        {100, "C"}, {90, "XC"}, {50, "L"}, {40, "XL"},
        {10, "X"}, {9, "IX"}, {5, "V"}, {4, "IV"}, {1, "I"}
    };
    string res;
    for(auto &p : vals){
        while(num >= p.first){
            res += p.second;
            num -= p.first;
        }
    }
    return res;
}

// Generate a non-minimal roman numeral by adding extra Is
string make_non_minimal(int val){
    string minimal = int_to_roman(val);
    // Add some extra IIII or other redundancy
    string res = minimal;
    // Check if we can expand something
    // Replace some subtractive patterns with additive
    // IV -> IIII
    size_t pos;
    if((pos = res.find("IV")) != string::npos){
        res.replace(pos, 2, "IIII");
    }
    if((pos = res.find("IX")) != string::npos){
        res.replace(pos, 2, "VIIII");
    }
    // Sometimes add extra I's randomly at the end
    if(rand() % 3 == 0 && val % 10 != 4 && val % 10 != 9){
        int extra = rand() % 3 + 1;
        res += string(extra, 'I');
    }
    return res;
}

int main() {
    system("mkdir -p data");
    srand(time(0));

    for(int tc = 0; tc < 10; tc++){
        string filename = string("data/") + (tc < 9 ? "0" : "") + to_string(tc + 1) + ".in";
        ofstream fout(filename);

        int N;
        if(tc == 0){
            // Simple sample: 1 roman numeral
            N = 1;
            fout << N << "\n";
            fout << "XIIIIII\n"; // 16 in valid form, savings: 7-3=4
        } else if(tc == 1){
            // Multiple with known savings
            N = 5;
            fout << N << "\n";
            fout << "XIIIIII\n";  // 16, XIIIIII→XVI saves 4
            fout << "VIIII\n";    // 9, VIIII→IX saves 3
            fout << "IIII\n";     // 4, IIII→IV saves 2
            fout << "LXXXX\n";    // 90, LXXXX→XC saves 3
            fout << "XXXX\n";     // 40, XXXX→XL saves 2
            // Total saved: 4+3+2+3+2 = 14
        } else if(tc < 5){
            // Small tests
            N = rand_int(1, 10);
            fout << N << "\n";
            for(int i = 0; i < N; i++){
                int val = rand_int(1, 100);
                fout << int_to_roman(val) << "\n";
            }
        } else {
            // Larger random tests
            N = rand_int(100, 500);
            fout << N << "\n";
            for(int i = 0; i < N; i++){
                int val = rand_int(1, 3999);
                fout << int_to_roman(val) << "\n";
            }
        }
        fout.close();
        cout << "Generated " << filename << " with " << N << " numerals\n";
    }

    return 0;
}

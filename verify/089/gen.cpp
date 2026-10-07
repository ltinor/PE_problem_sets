#include<bits/stdc++.h>
using namespace std;

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

int rand_int(int l, int r){
    return l + rand() % (r - l + 1);
}

int main(int argc, char* argv[]){
    srand(time(0));

    string mode = "small";
    if(argc > 1) mode = argv[1];

    int N;
    if(mode == "small"){
        N = rand_int(1, 20);
    } else {
        N = rand_int(1, 1000);
    }

    cout << N << "\n";
    for(int i = 0; i < N; i++){
        int val = rand_int(1, 3999);
        cout << int_to_roman(val) << "\n";
    }
}

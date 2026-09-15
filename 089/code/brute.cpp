#include<bits/stdc++.h>
using namespace std;

int roman_to_int(const string &s){
    unordered_map<char, int> mp = {
        {'I', 1}, {'V', 5}, {'X', 10}, {'L', 50},
        {'C', 100}, {'D', 500}, {'M', 1000}
    };
    int res = 0;
    int n = s.size();
    for(int i = 0; i < n; i++){
        int val = mp[s[i]];
        if(i + 1 < n && val < mp[s[i+1]]){
            res -= val;
        } else {
            res += val;
        }
    }
    return res;
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

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    cin >> N;

    long long total_saved = 0;
    for(int i = 0; i < N; i++){
        string s;
        cin >> s;
        int val = roman_to_int(s);
        string minimal = int_to_roman(val);
        total_saved += s.size() - minimal.size();
    }

    cout << total_saved << "\n";
}

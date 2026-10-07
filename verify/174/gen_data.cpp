#include<bits/stdc++.h>
using namespace std;

int main(){
    system("mkdir -p data");

    vector<pair<int,int>> test_cases = {
        {8, 1},      // t=8 is L(1), only one type
        {32, 2},     // t=32 is L(2)
        {100, 5},
        {1000, 5},
        {10000, 5},
        {10000, 10},
        {100000, 10},
        {500000, 10},
        {1000000, 1}, // only L(1)
        {1000000, 10} // PE original
    };

    for(int i = 0; i < (int)test_cases.size(); i++){
        string fname = string("data/") + (i < 9 ? "0" : "") + to_string(i + 1) + ".in";
        ofstream fout(fname);
        fout << test_cases[i].first << " " << test_cases[i].second << "\n";
        fout.close();
        cout << "Generated " << fname << " with M=" << test_cases[i].first << " K=" << test_cases[i].second << "\n";
    }

    return 0;
}

#include<bits/stdc++.h>
using namespace std;

int main() {
    system("mkdir -p data");
    vector<int> tests = {1,2,4,8,16,32,3,5,10,20};
    for (int i = 0; i < 10; i++) {
        string fn = "data/" + string(i<9?"0":"") + to_string(i+1) + ".in";
        ofstream f(fn);
        f << tests[i] << "\n";
        f.close();
        cout << "Generated " << fn << " K=" << tests[i] << "\n";
    }
    return 0;
}

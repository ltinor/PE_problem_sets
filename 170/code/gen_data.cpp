#include<bits/stdc++.h>
using namespace std;

int main(){
    system("mkdir -p data");
    
    for(int i = 0; i < 10; i++){
        string fname = string("data/") + (i < 9 ? "0" : "") + to_string(i + 1) + ".in";
        ofstream fout(fname);
        fout << "1\n";
        fout.close();
        cout << "Generated " << fname << "\n";
    }
    
    return 0;
}

#include <bits/stdc++.h>
using namespace std;

bool check(int S, long long user_ans) {
    if(user_ans == 0) {
        for(int n = 1; n < S/2; n++) {
            for(int m = n+1;; m++) {
                int a = m*m - n*n;
                int b = 2*m*n;
                int c = m*m + n*n;
                int sum = a+b+c;
                if(sum > S) break;
                if(sum == S) return false;
            }
        }
        return true;
    } else {
        for(int n = 1; n < S/2; n++) {
            for(int m = n+1;; m++) {
                int a = m*m - n*n;
                int b = 2*m*n;
                int c = m*m + n*n;
                int sum = a+b+c;
                if(sum > S) break;
                if(sum == S && 1LL*a*b*c == user_ans) return true;
            }
        }
        return false;
    }
}

int main(int argc, char* argv[]) {
    if(argc < 3) {
        cerr << "Usage: spj input.txt output.txt\n";
        return 1;
    }

    ifstream fin(argv[1]);   
    ifstream fout(argv[2]);  

    if(!fin || !fout) {
        cerr << "Cannot open file\n";
        return 1;
    }

    int T;
    fin >> T;
    while(T--) {
        int S;
        fin >> S;

        long long user_ans;
        if(!(fout >> user_ans)) {
            cerr << "Wrong Answer: cannot read user output\n";
            return 1;
        }

        if(!check(S, user_ans)) {
            cerr << "Wrong Answer\n";
            return 1;
        }
    }

    cout << "Accepted\n";
    return 0;
}
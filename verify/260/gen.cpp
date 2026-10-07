#include <bits/stdc++.h>
using namespace std;
int main(int argc, char* argv[]) {
    srand(time(0));
    string m="small"; if(argc>1)m=argv[1];
    int N = (m=="small") ? (rand()%50+1) : (rand()%100+50);
    cout << N << "\n";
}

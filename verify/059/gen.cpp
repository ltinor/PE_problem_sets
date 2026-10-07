#include <bits/stdc++.h>
using namespace std;
int main(){srand(time(0));int N=rand()%50+5;cout<<N<<"\n";for(int i=0;i<N;i++)cout<<(rand()%128)<<" \n"[i==N-1];}
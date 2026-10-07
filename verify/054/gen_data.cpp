#include<bits/stdc++.h>
using namespace std;

string values="23456789TJQKA";
string suits_str="SHDC";

int main(){
    system("mkdir -p data");
    srand(time(0));

    vector<int> Ns={5, 1, 3, 10, 20, 50, 100, 1, 2, 7};

    mt19937 rng(rand());
    for(int t=0;t<10;t++){
        int N=Ns[t];
        string fname=string("data/")+(t<9?"0":"")+to_string(t+1)+".in";
        ofstream f(fname);
        f<<N<<"\n";
        for(int g=0;g<N;g++){
            vector<string> deck;
            for(int i=0;i<13;i++) for(int j=0;j<4;j++){
                deck.push_back(string(1,values[i])+suits_str[j]);
            }
            shuffle(deck.begin(),deck.end(),rng);
            for(int i=0;i<10;i++){
                f<<deck[i]<<(i==9?"\n":" ");
            }
        }
        f.close();
        cout<<"Generated "<<fname<<" with N="<<N<<"\n";
    }
    return 0;
}

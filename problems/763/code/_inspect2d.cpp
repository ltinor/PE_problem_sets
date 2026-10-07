#include <bits/stdc++.h>
using namespace std;
struct Cell { int x,y; };
bool operator<(Cell a, Cell b){ return tie(a.x,a.y) < tie(b.x,b.y); }
bool operator==(Cell a, Cell b){ return tie(a.x,a.y)==tie(b.x,b.y); }
string key(vector<Cell> v){ sort(v.begin(),v.end()); string s; for(auto c:v){s.append((char*)&c.x,4);s.append((char*)&c.y,4);} return s; }
vector<Cell> dec(const string& ks){ const char*p=ks.data(); vector<Cell> v(ks.size()/8); for(auto&c:v){memcpy(&c.x,p,4);p+=4;memcpy(&c.y,p,4);p+=4;} return v; }
int main(int argc,char**argv){
  int N=atoi(argv[1]);
  unordered_set<string> cur; cur.insert(key({{0,0}}));
  for(int step=0;step<N;step++){
    unordered_set<string> nxt;
    for(auto&ks:cur){ auto v=dec(ks); set<Cell> occ(v.begin(),v.end());
      for(auto c:v){ Cell a{c.x+1,c.y}, b{c.x,c.y+1};
        if(!occ.count(a)&&!occ.count(b)){ auto v2=v; for(size_t i=0;i<v2.size();i++)if(v2[i]==c){v2.erase(v2.begin()+i);break;} v2.push_back(a);v2.push_back(b); nxt.insert(key(v2)); }
      }
    }
    cur=nxt;
  }
  cout << "D2("<<N<<")="<<cur.size()<<"\n";
  // For each config, reconstruct merge tree and print internal nodes per depth
  int idx=0;
  for(auto&ks:cur){
    auto S=dec(ks);
    // reverse merge to find internal nodes (positions)
    vector<Cell> internal; // internal nodes = merged cells
    // simulate merges: repeatedly find (x+1,y),(x,y+1) both present
    multiset<Cell> ms(S.begin(),S.end());
    vector<Cell> leaf = S;
    while(true){
      bool merged=false;
      // find a merge
      set<Cell> occ(leaf.begin(),leaf.end());
      for(auto c: occ){ // candidate (x,y): need (x+1,y),(x,y+1)
        Cell a{c.x+1,c.y}, b{c.x,c.y+1};
        if(occ.count(a)&&occ.count(b)){
          internal.push_back(c);
          // remove a,b from leaf, add c
          vector<Cell> nleaf;
          for(auto e: leaf){ if(e==a||e==b){/*skip*/} else nleaf.push_back(e); }
          nleaf.push_back(c);
          leaf=nleaf; merged=true; break;
        }
      }
      if(!merged) break;
    }
    // group internal by depth
    map<int,vector<int>> dep;
    for(auto c: internal) dep[c.x+c.y].push_back(c.x);
    cout << "  config "<<idx++<<": leaves=";
    for(auto c:S) cout<<"("<<c.x<<","<<c.y<<")";
    cout<<"  internal-by-depth: ";
    for(auto&kv:dep){ sort(kv.second.begin(),kv.second.end()); cout<<" d"<<kv.first<<":{"; for(int x:kv.second)cout<<x<<","; cout<<"} "; }
    cout<<"\n";
  }
  return 0;
}

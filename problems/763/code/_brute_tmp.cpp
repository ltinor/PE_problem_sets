#include <bits/stdc++.h>
using namespace std;

struct Cell { int x,y,z; };
bool operator<(Cell a, Cell b){ return tie(a.x,a.y,a.z) < tie(b.x,b.y,b.z); }
bool operator==(Cell a, Cell b){ return tie(a.x,a.y,a.z)==tie(b.x,b.y,b.z); }

string key(vector<Cell> v){
  sort(v.begin(), v.end());
  string s; s.reserve(v.size()*12);
  for(auto c:v){ s.append((char*)&c.x,4); s.append((char*)&c.y,4); s.append((char*)&c.z,4); }
  return s;
}

vector<Cell> decode(const string& ks){
  const char* p = ks.data();
  vector<Cell> v(ks.size()/12);
  for(auto &c : v){ memcpy(&c.x,p,4);p+=4; memcpy(&c.y,p,4);p+=4; memcpy(&c.z,p,4);p+=4; }
  return v;
}

int main(int argc, char** argv){
  int N = atoi(argv[1]);
  unordered_set<string> cur;
  vector<Cell> init = {{0,0,0}};
  cur.insert(key(init));
  for(int step=0; step<N; step++){
    unordered_set<string> nxt;
    for(auto &ks : cur){
      vector<Cell> v = decode(ks);
      set<Cell> occ(v.begin(), v.end());
      for(auto c : v){
        Cell a{c.x+1,c.y,c.z}, b{c.x,c.y+1,c.z}, d{c.x,c.y,c.z+1};
        if(!occ.count(a) && !occ.count(b) && !occ.count(d)){
          vector<Cell> v2 = v;
          for(size_t i=0;i<v2.size();i++) if(v2[i]==c){ v2.erase(v2.begin()+i); break; }
          v2.push_back(a); v2.push_back(b); v2.push_back(d);
          nxt.insert(key(v2));
        }
      }
    }
    cur = nxt;
    cerr << "step " << step+1 << " : " << cur.size() << "\n";
  }
  cout << cur.size() << "\n";
  return 0;
}

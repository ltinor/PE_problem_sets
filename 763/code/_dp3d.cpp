#include <bits/stdc++.h>
using namespace std;

// 3D histogram DP. Node at depth d identified by (x,y) projection (z=d-x-y).
// Children of internal (x,y): (x+1,y), (x,y+1), (x,y).
// Leaves at same depth must be distinct (x,y). Normalize shift.

unordered_map<string, __int128> memo;

string norm(vector<pair<int,int>> v){
  if(v.empty()) return "";
  int mx = INT_MAX, my = INT_MAX;
  for(auto&p:v){ mx=min(mx,p.first); my=min(my,p.second); }
  sort(v.begin(), v.end());
  string s; s.reserve(v.size()*4);
  for(auto&p: v){
    int x = p.first - mx, y = p.second - my;
    s.push_back((char)(x&0xff)); s.push_back((char)((x>>8)&0xff));
    s.push_back((char)(y&0xff)); s.push_back((char)((y>>8)&0xff));
  }
  return s;
}

__int128 F(vector<pair<int,int>> M, int k){
  if(k == 0){
    sort(M.begin(), M.end());
    for(size_t i=1;i<M.size();i++) if(M[i]==M[i-1]) return 0;
    return 1;
  }
  string key = norm(M) + "#" + to_string(k);
  auto it = memo.find(key);
  if(it != memo.end()) return it->second;
  __int128 total = 0;
  // group by (x,y)
  map<pair<int,int>,int> cnt; for(auto&p:M) cnt[p]++;
  vector<pair<int,int>> vals; vector<int> mult;
  for(auto&q:cnt){ vals.push_back(q.first); mult.push_back(q.second); }
  int g = vals.size();
  vector<int> ic(g,0);
  function<void(int,int)> rec = [&](int gi, int used){
    if(used > k) return;
    if(gi == g){
      if(used == 0) return;
      vector<pair<int,int>> M2;
      for(int i=0;i<g;i++){
        int x=vals[i].first, y=vals[i].second;
        for(int t=0;t<ic[i];t++){
          M2.push_back({x+1,y});
          M2.push_back({x,y+1});
          M2.push_back({x,y});
        }
      }
      total += F(M2, k - used);
      return;
    }
    int m = mult[gi];
    int lo = max(0, m-1);
    for(int iv=lo; iv<=m; iv++){ ic[gi]=iv; rec(gi+1, used+iv); }
  };
  rec(0,0);
  memo[key] = total;
  return total;
}

int main(int argc, char** argv){
  int N = atoi(argv[1]);
  vector<pair<int,int>> M = {{0,0}};
  __int128 r = F(M, N);
  string s; __int128 x=r;
  if(x==0) s="0";
  while(x>0){ s.push_back('0'+ (int)(x%10)); x/=10; }
  reverse(s.begin(), s.end());
  cout << "3D DP N="<<N<<" -> "<<s<<"  states="<<memo.size()<<"\n";
  return 0;
}

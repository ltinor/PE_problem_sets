#include <bits/stdc++.h>
using namespace std;

// 2D histogram DP. State = normalized multiset of x-values (min shifted to 0).
// F(M, k) = ways to finish tree with k internal nodes remaining.

unordered_map<string, __int128> memo;
int MAXK = 0;

string norm(vector<int> v){
  sort(v.begin(), v.end());
  if(v.empty()) return "";
  int mn = v[0];
  for(auto &x : v) x -= mn;
  string s; s.reserve(v.size()*2);
  for(auto x: v){ s.push_back((char)(x&0xff)); s.push_back((char)((x>>8)&0xff)); }
  return s;
}
vector<int> denorm(const string& s){
  vector<int> v;
  for(size_t i=0;i<s.size();i+=2){ int x = (unsigned char)s[i] | ((unsigned char)s[i+1]<<8); v.push_back(x); }
  return v;
}

__int128 F(vector<int> M, int k){
  if(k == 0){
    // all leaves, must be distinct
    sort(M.begin(), M.end());
    for(size_t i=1;i<M.size();i++) if(M[i]==M[i-1]) return 0;
    return 1;
  }
  string key = norm(M) + "#" + to_string(k);
  auto it = memo.find(key);
  if(it != memo.end()) return it->second;
  __int128 total = 0;
  // choose internal subset I. leaves = M \ I must be distinct.
  // equivalently: for each value x with multiplicity m_x, leave at most 1, internal the rest (m_x-1 or m_x).
  int n = M.size();
  // group by value
  map<int,int> cnt; for(auto x:M) cnt[x]++;
  vector<int> vals; vector<int> mult; for(auto&p:cnt){ vals.push_back(p.first); mult.push_back(p.second); }
  int g = vals.size();
  // enumerate choices: for each group, internal count i_x in [max(0,m_x-1), m_x]
  // use recursion over groups
  vector<int> internal_choice(g, 0);
  function<void(int,int)> rec = [&](int gi, int used){
    if(used > k) return;
    if(gi == g){
      if(used == 0) return; // can't stop with k>0
      // build M' = children
      vector<int> M2;
      for(int i=0;i<g;i++){
        int x = vals[i];
        for(int t=0;t<internal_choice[i];t++){ M2.push_back(x); M2.push_back(x+1); }
      }
      total += F(M2, k - used);
      return;
    }
    int m = mult[gi];
    int lo = max(0, m-1);
    for(int iv = lo; iv <= m; iv++){
      internal_choice[gi] = iv;
      rec(gi+1, used + iv);
    }
  };
  rec(0, 0);
  memo[key] = total;
  return total;
}

int main(int argc, char** argv){
  int N = atoi(argv[1]); // N internal nodes
  vector<int> M = {0};
  __int128 r = F(M, N);
  // print as decimal
  string s;
  __int128 x = r;
  if(x==0) s="0";
  while(x>0){ s.push_back('0' + x%10); x/=10; }
  reverse(s.begin(), s.end());
  cout << "2D DP N="<<N<<" -> "<<s<<"  states="<<memo.size()<<"\n";
  return 0;
}

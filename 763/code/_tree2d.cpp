#include <bits/stdc++.h>
using namespace std;
// 2D tree model: full binary tree, each internal node has 2 children labeled x,y.
// Leaf position = (count_x, count_y). Count trees with N internal nodes and distinct leaf positions.

// generate all leaf position multisets reachable: return vector<map<pair<int,int>,int>> ... 
// Instead: recursive generation. Represent a tree's leaves as a multiset of positions.
// We'll generate all trees and dedupe by leaf-position-SET.

vector<vector<pair<int,int>>> generate(int internal_left, pair<int,int> pos){
  // returns list of leaf position sets for subtree rooted at pos with internal_left internal nodes
  if(internal_left == 0){
    return {{{pos}}}; // single leaf
  }
  vector<vector<pair<int,int>>> res;
  // allocate i internal nodes to x-child, (internal_left-1-i) to y-child
  for(int i=0;i<=internal_left-1;i++){
    int j = internal_left-1-i;
    auto L = generate(i, {pos.first+1, pos.second});
    auto R = generate(j, {pos.first, pos.second+1});
    for(auto &a: L) for(auto &b: R){
      vector<pair<int,int>> comb = a;
      comb.insert(comb.end(), b.begin(), b.end());
      res.push_back(comb);
    }
  }
  return res;
}

int main(int argc, char** argv){
  int N = atoi(argv[1]);
  auto trees = generate(N, {0,0});
  set<vector<pair<int,int>>> distinct;
  for(auto &t: trees){
    auto v = t; sort(v.begin(), v.end());
    // distinct positions?
    bool ok = true;
    for(size_t i=1;i<v.size();i++) if(v[i]==v[i-1]){ ok=false; break; }
    if(ok) distinct.insert(v);
  }
  cout << "2D tree model N="<<N<<" internal: total trees="<<trees.size()<<" distinct-leaf="<<distinct.size()<<"\n";
  return 0;
}

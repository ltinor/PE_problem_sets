#include<bits/stdc++.h>
using namespace std;
#define ll long long

// brute: same algorithm as std

bool is_pandigital(const string& s){
    if(s.size() != 10) return false;
    int mask = 0;
    for(char c : s){
        int d = c - '0';
        if(mask & (1 << d)) return false;
        mask |= (1 << d);
    }
    return mask == 1023;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int dummy; cin >> dummy;
    
    string best = "0000000000";
    
    for(int a = 1; a <= 99; a++){
        string a_str = to_string(a);
        {
            int mask = 0;
            bool ok = true;
            for(char c : a_str){
                int d = c - '0';
                if(mask & (1 << d)){ ok = false; break; }
                mask |= (1 << d);
            }
            if(!ok) continue;
        }
        
        int input_mask = 0;
        for(char c : a_str) input_mask |= (1 << (c - '0'));
        string input_str = a_str;
        
        vector<tuple<int, string, string>> candidates;
        for(int m = 1; ; m++){
            ll prod = (ll)a * m;
            string prod_str = to_string(prod);
            if(prod_str.size() > 10) break;
            
            string m_str = to_string(m);
            
            {
                int mask = 0;
                bool ok = true;
                for(char c : prod_str){
                    int d = c - '0';
                    if(mask & (1 << d)){ ok = false; break; }
                    mask |= (1 << d);
                }
                if(!ok) continue;
            }
            
            {
                int mask = 0;
                bool ok = true;
                for(char c : m_str){
                    int d = c - '0';
                    if(mask & (1 << d)){ ok = false; break; }
                    mask |= (1 << d);
                }
                if(!ok) continue;
            }
            
            candidates.push_back({m, prod_str, m_str});
        }
        
        if(candidates.size() < 2) continue;
        
        function<void(int, int, int, string, string)> dfs = 
        [&](int idx, int prod_mask, int inp_mask, string prod_str, string inp_str){
            if(prod_str.size() == 10){
                if(is_pandigital(prod_str) && is_pandigital(inp_str)){
                    if(prod_str > best) best = prod_str;
                }
                return;
            }
            if(prod_str.size() > 10) return;
            if(idx >= (int)candidates.size()) return;
            
            for(size_t i = idx; i < candidates.size(); i++){
                auto [m, p_str, m_str] = candidates[i];
                int p_mask = 0;
                for(char c : p_str) p_mask |= (1 << (c - '0'));
                int m_mask = 0;
                for(char c : m_str) m_mask |= (1 << (c - '0'));
                
                if(prod_mask & p_mask) continue;
                if(inp_mask & m_mask) continue;
                
                dfs(i + 1, prod_mask | p_mask, inp_mask | m_mask,
                    prod_str + p_str, inp_str + m_str);
            }
        };
        
        dfs(0, 0, input_mask, "", input_str);
    }
    
    cout << best << "\n";
}

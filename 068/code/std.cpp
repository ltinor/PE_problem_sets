#include<bits/stdc++.h>
using namespace std;
#define ll long long

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // 读取并忽略输入（固定答案题）
    string s; cin >> s;

    // 5-gon ring: 外圈5个数(a,b,c,d,e) + 内圈5个数(f,g,h,i,j)
    // 线1: a,f,g; 线2: b,g,h; 线3: c,h,i; 线4: d,i,j; 线5: e,j,f
    // 每条线和相等 = S
    // 从最小的外圈数开始，顺时针
    
    vector<int> nums = {1,2,3,4,5,6,7,8,9,10};
    string best = "";
    
    do {
        // 5条线: (0,5,6), (1,6,7), (2,7,8), (3,8,9), (4,9,5)
        // 其中 0-4 外圈, 5-9 内圈
        int a = nums[0], b = nums[1], c = nums[2], d = nums[3], e = nums[4];
        int f = nums[5], g = nums[6], h = nums[7], i = nums[8], j = nums[9];
        
        int s1 = a + f + g;
        int s2 = b + g + h;
        int s3 = c + h + i;
        int s4 = d + i + j;
        int s5 = e + j + f;
        
        if(s1 != s2 || s2 != s3 || s3 != s4 || s4 != s5) continue;
        
        // 外圈最小的是起始点，且10必须在16位串中（10是两位数）
        int outer[5] = {a, b, c, d, e};
        int min_outer = *min_element(outer, outer+5);
        int start = -1;
        for(int k = 0; k < 5; k++){
            if(outer[k] == min_outer){
                start = k;
                break;
            }
        }
        
        // 按顺时针生成串（start, start+1, ... mod 5）
        string cur = "";
        for(int k = 0; k < 5; k++){
            int idx = (start + k) % 5;
            if(idx == 0) cur += to_string(a) + to_string(f) + to_string(g);
            else if(idx == 1) cur += to_string(b) + to_string(g) + to_string(h);
            else if(idx == 2) cur += to_string(c) + to_string(h) + to_string(i);
            else if(idx == 3) cur += to_string(d) + to_string(i) + to_string(j);
            else cur += to_string(e) + to_string(j) + to_string(f);
        }
        
        // 只取16位数字串（10必须在外圈，如果10在内圈会产生17位串）
        if(cur.length() == 16 && cur > best){
            best = cur;
        }
    } while(next_permutation(nums.begin(), nums.end()));
    
    cout << best << "\n";
    return 0;
}

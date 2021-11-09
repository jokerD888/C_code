//1218. 最长定差子序列
//dp
//通过转移方程 dp[i]=dp[i-differenec]+1,来进行
#include<unordered_map>
class Solution {
public:
    int longestSubsequence(vector<int>& arr, int difference) {
        int ans = 0;
        unordered_map<int, int> dp;
        for (int v : arr) {
            dp[v] = dp[v - difference] + 1;
            ans = max(ans, dp[v]);
        }
        return ans;
    }
};
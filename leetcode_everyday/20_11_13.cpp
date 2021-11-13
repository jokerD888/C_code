
//375. 猜数字大小 II
//dp
class Solution {
public:
    int getMoneyAmount(int n) {
        vector<vector<int>> f(n + 1, vector<int>(n + 1));
        for (int i = n - 1; i >= 1; i--) {
            for (int j = i + 1; j <= n; j++) {
                int minCost = INT_MAX;
                for (int k = i; k < j; k++) {
                    int cost = k + max(f[i][k - 1], f[k + 1][j]);
                    minCost = min(minCost, cost);
                }
                f[i][j] = minCost;
            }
        }
        return f[1][n];

    }
};

//或
//dp[i][j]是说依次以从i到j的数字作为分割点(猜的数)，必定赢的游戏所用钱的最小值。
//i i+1 i+2 ... ... j-2 j-1 j
//以i + 1为分割点对应的：dp1 = max(dp[i][i], dp[i + 2][j]) + i + 1
//以j - 1为分割点对应的: dp2 = max(dp[i][j - 2], dp[j][j]) + j - 1
//特别地, 以i为分割点：dp0 = i + dp[i + 1][j]; 以j为分割点: dp3 = j + dp[i][j - 1]
//dp[i][j] = min(dp0, dp1, dp2, dp3)
//这道题由于需要用最少的金币通过游戏，所有二分法无法解题，需要穷举所有情况
//1.i==j,时只有一个数字，花销为0；
//2.i!=j,对于以端点分割来说，只需要计算左端点，即dp[i][j] = min(dp[i][j], i + dp[i + 1][j]); 因为j始终大于i,且dp[i][j-1]>=dp[i+1][j]
//3.对于每一个分割点，我们取它左右两边区间的最大值加上分割点本身作为取此分割点的dp[i][j]值
//4.对于每一个区间，我们取所有分割点的dp[i][j]的最小值作为dp[i][j]的真正的值

class Solution {
public:
    int getMoneyAmount(int n) {
        if (n == 1)
            return 0;
        //定义矩阵
        vector<vector<int>> dp(n + 1, vector<int>(n + 1));
        //初始化“\”
        for (int i = 0; i <= n; i++) {
            for (int j = 0; j <= n; j++) {
                dp[i][j] = INT_MAX;
            }
        }
        //定义基础值dp[i][i]
        for (int i = 0; i <= n; i++) {
            dp[i][i] = 0;
        }

        //按列来，从第2列开始
        for (int j = 2; j <= n; j++) {
            //按行来，从下往上
            for (int i = j - 1; i >= 1; i--) {
                //算除了两端的每一个分割点
                for (int k = i + 1; k <= j - 1; k++) {
                    dp[i][j] = min(k + max(dp[i][k - 1], dp[k + 1][j]), dp[i][j]);
                }
                //算左端点
                dp[i][j] = min(dp[i][j], i + dp[i + 1][j]);
            }
        }
        return dp[1][n];
    }
};
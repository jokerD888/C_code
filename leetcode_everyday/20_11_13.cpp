//375. 猜数字大小 II
//dp
//为了将支付的金额最小化，除了需要将每次支付的金额控制在较低值以外，还需要在猜数字的过程中缩小所选数字的范围。
//当猜了数字 x并且猜错时，会知道 xx 比所选数字大还是小。如果 x 比所选数字大，则任何比x 大的数字一定都比所选数字大，
//因此应该在比 x小的数字中继续猜数字。如果 x 比所选数字小，同理可知应该在比 xx 大的数字中继续猜数字。
//用f(i, j) 表示在范围[i, j] 内确保胜利的最少金额，目标是计算 f(1, n)。
//应考虑最坏情况，计算 f(1, n)f(1,n) 时应取上述两者的最大值 f(1, n) = x + max(f(1, x?1), f(x + 1, n))
//为了将确保胜利的金额最小化，需要遍历从 1 到 n 的所有可能的 x，使得 f(1,n) 的值最小
class Solution {
public:
    int getMoneyAmount(int n) {
        vector<vector<int>> f(n + 1, vector<int>(n + 1));
        for (int i = n - 1; i >= 1; i--) {
            for (int j = i + 1; j <= n; j++) {
                f[i][j] = j + f[i][j - 1];
                for (int k = i; k < j; k++) {
                    f[i][j] = min(f[i][j], k + max(f[i][k - 1], f[k + 1][j]));
                }
            }
        }
        return f[1][n];
    }
};

//效率优于上面
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

//下面的代码是从左往右按列，从下往上，进行数据的填充，上面的代码，从下往上按行，从左往右填充


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

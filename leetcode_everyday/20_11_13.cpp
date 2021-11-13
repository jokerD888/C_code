//375. �����ִ�С II
//dp
//Ϊ�˽�֧���Ľ����С����������Ҫ��ÿ��֧���Ľ������ڽϵ�ֵ���⣬����Ҫ�ڲ����ֵĹ�������С��ѡ���ֵķ�Χ��
//���������� x���Ҳ´�ʱ����֪�� xx ����ѡ���ִ���С����� x ����ѡ���ִ����κα�x �������һ��������ѡ���ִ�
//���Ӧ���ڱ� xС�������м��������֡���� x ����ѡ����С��ͬ���֪Ӧ���ڱ� xx ��������м��������֡�
//��f(i, j) ��ʾ�ڷ�Χ[i, j] ��ȷ��ʤ�������ٽ�Ŀ���Ǽ��� f(1, n)��
//Ӧ�������������� f(1, n)f(1,n) ʱӦȡ�������ߵ����ֵ f(1, n) = x + max(f(1, x?1), f(x + 1, n))
//Ϊ�˽�ȷ��ʤ���Ľ����С������Ҫ������ 1 �� n �����п��ܵ� x��ʹ�� f(1,n) ��ֵ��С
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

//Ч����������
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

//����Ĵ����Ǵ������Ұ��У��������ϣ��������ݵ���䣬����Ĵ��룬�������ϰ��У������������


//dp[i][j]��˵�����Դ�i��j��������Ϊ�ָ��(�µ���)���ض�Ӯ����Ϸ����Ǯ����Сֵ��
//i i+1 i+2 ... ... j-2 j-1 j
//��i + 1Ϊ�ָ���Ӧ�ģ�dp1 = max(dp[i][i], dp[i + 2][j]) + i + 1
//��j - 1Ϊ�ָ���Ӧ��: dp2 = max(dp[i][j - 2], dp[j][j]) + j - 1
//�ر��, ��iΪ�ָ�㣺dp0 = i + dp[i + 1][j]; ��jΪ�ָ��: dp3 = j + dp[i][j - 1]
//dp[i][j] = min(dp0, dp1, dp2, dp3)
//�����������Ҫ�����ٵĽ��ͨ����Ϸ�����ж��ַ��޷����⣬��Ҫ����������
//1.i==j,ʱֻ��һ�����֣�����Ϊ0��
//2.i!=j,�����Զ˵�ָ���˵��ֻ��Ҫ������˵㣬��dp[i][j] = min(dp[i][j], i + dp[i + 1][j]); ��Ϊjʼ�մ���i,��dp[i][j-1]>=dp[i+1][j]
//3.����ÿһ���ָ�㣬����ȡ������������������ֵ���Ϸָ�㱾����Ϊȡ�˷ָ���dp[i][j]ֵ
//4.����ÿһ�����䣬����ȡ���зָ���dp[i][j]����Сֵ��Ϊdp[i][j]��������ֵ

class Solution {
public:
    int getMoneyAmount(int n) {
        if (n == 1)
            return 0;
        //�������
        vector<vector<int>> dp(n + 1, vector<int>(n + 1));
        //��ʼ����\��
        for (int i = 0; i <= n; i++) {
            for (int j = 0; j <= n; j++) {
                dp[i][j] = INT_MAX;
            }
        }
        //�������ֵdp[i][i]
        for (int i = 0; i <= n; i++) {
            dp[i][i] = 0;
        }

        //���������ӵ�2�п�ʼ
        for (int j = 2; j <= n; j++) {
            //����������������
            for (int i = j - 1; i >= 1; i--) {
                //��������˵�ÿһ���ָ��
                for (int k = i + 1; k <= j - 1; k++) {
                    dp[i][j] = min(k + max(dp[i][k - 1], dp[k + 1][j]), dp[i][j]);
                }
                //����˵�
                dp[i][j] = min(dp[i][j], i + dp[i + 1][j]);
            }
        }
        return dp[1][n];
    }
};

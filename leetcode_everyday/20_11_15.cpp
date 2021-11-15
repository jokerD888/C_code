//319. 灯泡开关
//模拟
//堆区溢出
class Solution {
public:
    int bulbSwitch(int n) {
        vector<bool> light(n+1,false);

        for (int i = 1; i <= n+1; i++) {
            for (int j = 0; j <= n+1; j += i)
                light[j] = !light[j];
        }

        int ans = 0;
        for (int i = 1; i < n + 1; i++) {
            if (light[i])
                ans++;
        }

        return ans;
    }
};


//数学
//第i个灯泡的反转次数等于它所有因子（包括1和i）的个数，一开始的状态的灭的，
//只有反转奇数次才会变成亮的，所以只有因子个数为奇数的灯泡序号才会亮，只有平方数的因子数为奇数（比如6=1*6,2*3，它们的因子总是成对出现的，
//而4=1*4,2*2，只有平方数的平方根因子会只出现1次），所以最终答案等于n以内（包括n和1）的平方数数量，只要计算sqrt(n)即可
//由于sqrt涉及到浮动数运算，?为了保证不出现精度问题，我们可以计算 sqrt（n+0.5）这样可以保证计算出来的结果向下取整在 32 位整数范围内一定正确。
class Solution {
public:
    int bulbSwitch(int n) {
        return sqrt(n + 0.5);
    }
};



#include <iostream>
using namespace std;
#include<cmath>
#include<string>
#include <climits>
#include <numeric>
#include <vector>
#include <algorithm>
#include <utility>
#include <unordered_map>

//问题 o: 小H分糖果（动态规划）----------------------------------------------------------------
//
int main()
{
	int n;
	cin >> n;
	int score;
	vector<int> arr(n);
	for (int i = 0; i < n; ++i) {
		cin >> arr[i];
	}
	vector<int> candy(n, 1);	// candy[i]存储i位置同学获得的糖果数
	// 从左往右，只观察该同学的右边
	for (int i = 0; i < n - 1; ++i) {
		// 如果该同学分数大于右边的同学，那么该同学的糖果数至少比她多一个
		if (arr[i+1] > arr[i]) candy[i+1] =candy[i]+1;
	}
	// 从右往左，只观察该同学的左边
	for (int i = n - 1; i > 0; --i) {
		// 如果该同学分数大于左边的同学，那么该同学的糖果数至少比她多一个
		if (arr[i-1] > arr[i]) candy[i-1] =candy[i]+1;
	}
	cout << accumulate(candy.begin(), candy.end(),0);
	return 0;
}


//问题 n : 凑零钱（动态规划）----------------------------------------------------------------------

//// 回溯，枚举硬币是否使用
//bool DFS(int index, vector<int>& arr, int pay, vector<int>& ans) {
//	if (pay == 0) return true;
//	if (pay < 0 || index==arr.size())return false;
//
//	ans.push_back(arr[index]);
//	if (DFS(index+1,arr,pay-arr[index],ans)) {
//		return true;
//	}
//	ans.pop_back();
//	if (DFS(index+1,arr,pay,ans)) {
//		return true;
//	}
//	return false;
//}
//int main()
//{
//	int n, pay;
//	cin >> n >> pay;
//	vector<int> arr(n);
//	for (int i = 0; i < n; ++i) {
//		cin >> arr[i];
//	}
//	sort(arr.begin(), arr.end());
//	vector<int> ans;
//	DFS(0, arr, pay, ans);
//	if (ans.empty()) {
//		cout << "No Solution";
//	} else {
//		for (int i = 0; i < ans.size()-1; ++i) {
//			cout << ans[i] << " ";
//		}
//		cout << ans[ans.size() - 1];
//	}
//	return 0;
//}


//问题 m: 最大公共子序列（动态规划）--------------------------------------------------------------------
// 动态规划
int main()
{
	string str1, str2;
	cin >> str1 >> str2;
	int len1 = str1.size(), len2 = str2.size();
	vector<vector<int>> dp(len1, vector<int>(len2));
	// dp[i][j]表示 str1[0...i],str[0....j]最长公共子序列的长度
	// 每种dp[i][j]下的最长公共子序列共有四种情况，
	// 1) 最长公共子序列不以str1[i]和str2[j]结尾
	// 2）最长公共子序列不以str1[i]结尾，以str2[j]结尾
	// 3）最长公共子序列不以str2[j]结尾，以str1[i]结尾
	// 4) 最长公共子序列以str1[i]和str2[j]结尾

	dp[0][0] = str1[0] == str2[0] ? 1 : 0; // 首元素是否相等
	// 求第0列
	for (int i = 1; i < len1; ++i) {
		dp[i][0] = max(dp[i - 1][0], str1[i] == str2[0] ? 1 : 0);
	}
	// 求第0行
	for (int i = 1; i < len2; ++i) {
		dp[0][i] = max(dp[0][i - 1], str2[i] == str1[0] ? 1 : 0);
	}
	for (int i = 1; i < len1; ++i) {
		for (int j = 1; j < len2; ++j) {
			//情况2和3
			dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
			//情况4是有条件的且和情况1相斥，条件成立为情况4
			if (str1[i] == str2[j]) {
				dp[i][j] = max(dp[i][j], dp[i - 1][j - 1] + 1);
			}
			//条件不成立情况1,但这种情况在之前dp[i][j-1]往上以及dp[i-1][j]往左已被考虑，可以省略
		}
	}
	int ret = dp[len1 - 1][len2 - 1];
	string ans;

	// 根据动归的状态，来判断我们要求得的序列中的字符有哪些。
	int i = len1 - 1, j = len2 - 1;

	while (i && j) {
		if (str1[i] == str2[j]) {
			ans += str1[i];
			--i, --j;
		} else if (dp[i - 1][j] > dp[i][j - 1]) {
			--i;
		} else {
			--j;
		}
	}
	if (i > 0)	//str1还没根str2[0]比较完
		while (i >= 0) {
			if (str1[i--] == str2[j]) {
				ans += str2[j];
				break;
			}
		}
	if (j > 0)	//str2还没跟str1[0]比较完
		while (j >= 0) {
			if (str1[i] == str2[j--]) {
				ans += str1[i];
				break;
			}
		}
	// 或者不用以上两个if判断，对dp数组多开一行一列，第0行0列不处理，默认0,然后在上面的while判断中给为i>=0 && j>=0
	reverse(ans.begin(), ans.end());
	cout << ans << " " << ret;
	return 0;
}


//问题 l: 雷达侦测目标---------------------------------------------------------------------------------

//int main()
//{
//	int n, r;
//	cin >> n >> r;
//	int x, y;
//	int ans = 0;
//	for (int i = 0; i < n; ++i) {
//		cin >> x >> y;
//		if (x * x + y * y <= r * r) {
//			++ans;
//		}
//	}
//	cout << ans;
//	return 0;
//}

//问题 k : 选举先进个人----------------------------------------------------------------------------------
//int main()
//{
//	int n, k;
//	cin >> n >> k;
//	vector<pair<int,int>> arr(n + 1);
//	for (int i = 1; i <= n; ++i) {
//		cin >> arr[i].first;
//		arr[i].second = i;
//	}
//	sort(arr.begin() + 1, arr.end(), [](const pair<int, int>& a, const pair<int, int>& b){ return a.first > b.first; });
//	for (int i = 1; i <= k; ++i) {
//		cout << arr[i].second << " ";
//	}
//	return 0;
//}


//问题 j : 统计满足条件数的个数------------------------------------------------------------------------
//
//int main()
//{
//	int n, m;
//	cin >> n >> m;
//	int ans = 0;
//	for (int i = n; i <= m; ++i) {
//		if (i % 2 == 0 && i % 3 == 0 && i % 7 != 0) ++ans;
//	}
//	cout << ans << endl;
//	return 0;
//}

//问题 i: 闹铃何时会响？----------------------------------------------------------------------------
//int main()
//{
//	int start, end;
//	cin >> start >>end;
//	int ans = 0;
//	if (end < start) {
//		ans = 24 + end - start;
//	} else {
//		ans = end - start;
//	}
//	cout << ans << endl;
//	return 0;
//}


//问题 h : 求最大连续子序列之和------------------------------------------------------------------------
// 分治，线段树
//struct Status {
//	int lSum, rSum, mSum, iSum;
//	//对于一个区间 [l, r]，我们可以维护四个量：
//	//lSum 表示[l, r] 内以 l 为左端点的最大子段和
//	//rSum 表示[l, r] 内以 r 为右端点的最大子段和
//	//mSum 表示[l, r] 内的最大子段和
//	//iSum 表示[l, r] 的区间和
//};
//Status pushUp(Status l, Status r) {
//	//首先最好维护的是 iSum，区间 [l, r] 的 iSum 就等于「左子区间」的 iSum 加上「右子区间」的 iSum。
//	//对于[l, r] 的 lSum，存在两种可能，它要么等于「左子区间」的 lSum，要么等于「左子区间」的 iSum 加上「右子区间」的 lSum，二者取大。
//	//对于[l, r] 的 rSum，同理，它要么等于「右子区间」的 rSum，要么等于「右子区间」的 iSum 加上「左子区间」的 rSum，二者取大。
//	//当计算好上面的三个量之后，就很好计算[l, r] 的 mSum 了。我们可以考虑[l, r] 的 mSum 对应的区间是否跨越 m——它可能不跨越 m，
//	//也就是说[l, r] 的 mSum 可能是「左子区间」的 mSum 和 「右子区间」的 mSum 中的一个；它也可能跨越 m，可能是「左子区间」的 rSum 和 「右子区间」的 lSum 求和。三者取大。
//
//	int iSum = l.iSum + r.iSum;
//	int lSum = max(l.lSum, l.iSum + r.lSum);
//	int rSum = max(r.rSum, r.iSum + l.rSum);
//	int mSum = max(max(l.mSum, r.mSum), l.rSum + r.lSum);
//	return { lSum, rSum, mSum, iSum };
//};
//
//Status get(vector<int>& a, int l, int r) {
//	if (l == r) return { a[l], a[l], a[l], a[l] };
//	int m = (l + r) >> 1;
//	Status lSub = get(a, l, m);
//	Status rSub = get(a, m + 1, r);
//	return pushUp(lSub, rSub);
//}
//
//
//int main()
//{
//	int n;
//	while ((cin >> n) && n != 0) {
//		int tmp, sum=0;
//		int ans = INT_MIN;
//		vector<int> arr(n);
//		for (int i = 0; i < n; ++i) {
//			cin >> arr[i];
//		}
//	
//		cout << max(0,get(arr,0,arr.size()-1).mSum) << endl;
//	}
//	return 0;
//}

//动态规划
//用f[i]表示以第i个数a[i]结尾的最大子序列和。
//那么f[i]的状态转移方程也很好得出，对于a[i]是单独算还是加入前面的f[i - 1]，即：f[i] = max(f[i - 1] + a[i], a[i])
//int main()
//{
//	int n;
//	while ((cin >> n) && n != 0) {
//		int tmp, sum=0;
//		int ans = INT_MIN;
//		//那么对于第i个数来说，我们查看他之前的sum，
//		//如果sum<0，那么当前的最大连续子序列和就是它本身（舍弃前面的）；
//		//如果sum>0，那么当前的最大和就是sum+a[i]  （sum保留了）
//		for (int i = 0; i < n; ++i) {
//			cin >> tmp;
//			sum = max(sum + tmp, tmp);
//			ans = max(ans, sum);
//		}
//		ans = max(0, ans);
//		cout << ans << endl;
//	}
//	return 0;
//}

//贪心
//假设a[l]...a[r]的和为 sum
//如果 sum > 0，则说明 sum 对结果有增益效果，则 sum 保留
//如果 sum < 0，则说明 sum 对结果无增益效果，需要舍弃
//int main()
//{
//	int n;
//	while ((cin >> n) && n != 0) {
//		int tmp, sum=0;
//		int ans = INT_MIN;
//		//那么对于第i个数来说，我们查看他之前的sum，
//		//如果sum<0，那么当前的最大连续子序列和就是它本身（舍弃前面的）；
//		//如果sum>0，那么当前的最大和就是sum+a[i]  （sum保留了）
//		for (int i = 0; i < n; ++i) {
//			cin >> tmp;
//			if (sum >= 0) {
//				sum += tmp;
//			} else {	// 如果前面sum<0,那么前面的舍弃
//				sum=tmp;
//			}
//			ans = max(ans, sum);
//		}
//		ans = max(0, ans);
//		cout << ans << endl;
//	}
//	return 0;
//}

//前缀和+枚举起点终点
//int main()
//{
//	int n;
//	while ((cin >> n) && n != 0) {
//		vector<int> sum(n+1);
//		int tmp, all = 0;;
//
//		for (int i = 1; i <= n; ++i) {
//			cin >> tmp;
//			all += tmp;
//			sum[i] = all;
//		}
//		int ans = INT_MIN;
//		// 枚举可能的最大子序列的起点
//		for (int i = 0; i < n; ++i) {
//			// 枚举终点
//			for (int j = i+1; j <= n; ++j) {
//				ans = max(ans, sum[j] - sum[i]);
//			}
//		}
//		ans = max(0, ans);
//		cout << ans << endl;
//	}
//	return 0;
//}


//问题 g: 今年暑假不AC（第七讲）---------------------------------------------------------------------
// 最优解，以时间端的结束时间排序
//int main()
//{
//	int n;
//	while ((cin >> n) && n != 0) {
//		vector<pair<int, int>> arr(n);
//		for (int i = 0; i < n; ++i) {
//			cin >> arr[i].first >> arr[i].second;
//		}
//		sort(arr.begin(), arr.end(), [](const pair<int, int>& a, const pair<int, int>& b)
//			{return a.second < b.second; });
//		int cnt = 0;
//		int tiemEnd = -1;
//		for (int i = 0; i < arr.size(); ++i) {
//			if (tiemEnd <= arr[i].first) {
//				++cnt;
//				tiemEnd = arr[i].second;
//			}
//		}
//		cout << cnt << endl;
//	}
//	return 0;
//}

//// 暴力，以时间间隔从小到大排序，又因为时间范围在100内，可标记每个时间点，进行暴力尝试
//int main()
//{
//	int n;
//	while ((cin >> n) && n != 0) {
//		vector<pair<int, int>> arr(n);
//		for (int i = 0; i < n; ++i) {
//			cin >> arr[i].first >> arr[i].second;
//		}
//		sort(arr.begin(), arr.end(), [](const pair<int, int>& a, const pair<int, int>& b)
//			{return a.second - a.first < b.second - b.first; });
//		int cnt = 0;
//		int left = INT_MAX, right = INT_MIN;
//		vector<bool> vis(101);
//		for (int i = 0; i < n; ++i) {
//			bool accept = true;
//			for (int j = arr[i].first; j < arr[i].second; ++j) {
//				if (vis[j]) {
//					accept = false;
//					break;
//				}
//			}
//			if (!accept) continue;
//			fill(vis.begin() + arr[i].first, vis.begin() + arr[i].second, true);
//			++cnt;
//
//		}
//		cout << cnt << endl;
//	}
//	return 0;
//}



//问题 f: Moving Tables（第七讲）---------------------------------------------------------------------

//int main()
//{
//	int n;
//	cin >> n;
//	while (n--) {
//		int m;
//		cin >> m;
//		int from, to;
//		int time = 0;
//		vector<pair<int, int>> arr(m);
//		vector<bool> vis(m);
//		for (int i = 0; i < m; ++i) {
//			cin >> arr[i].first >> arr[i].second;
//		}
//		sort(arr.begin(), arr.end(), [](const pair<int, int>& a, const pair<int, int>& b)
//			{return a.second - a.first < b.second - b.first; });
//		int left, right;
//		for (int i = 0; i < m; ++i) {
//			if(vis[i]) continue;
//			left = arr[i].first;
//			right = arr[i].second;
//			vis[i] = true;
//			for (int j = i + 1; j < m; ++j) {
//				if (arr[j].second <= left || arr[j].first >= right) {
//					vis[j] = true;
//					left = min(left, arr[j].first);
//					right = max(right, arr[j].second);
//				}
//			}
//			time += 5;
//		}
//		cout << time << endl;
//
//	}
//	return 0;
//}


////问题 e: Let the Balloon Rise（第六讲）---------------------------------------------------------------
//int main()
//{
//	int n;
//	while (cin >> n) {
//		unordered_map<string, int> m;
//		string tmp;
//		for (int i = 0; i < n; ++i) {
//			cin >> tmp;
//			++m[tmp];
//		}
//		string ret;
//		int maxN = 0;
//		for (auto kv : m) {
//			if (kv.second > maxN) {
//				ret = kv.first;
//				maxN = kv.second;
//			}
//		}
//		cout << ret << endl;
//	}
//	return 0;
//}



//问题 d: Ignatius and the Princess IV（第六讲）-----------------------------------------------------

//int main()
//{
//	int n;
//
//	while (cin >> n) {
//		vector<int> arr(n);
//		unordered_map<int, int> m;
//		int tmp;
//		for (int i = 0; i < n; ++i) {
//			cin >> tmp;
//			++m[tmp];
//		}
//		int line = (n + 1) / 2;
//		for (auto kv : m) {
//			if (kv.second >= line) {
//				cout << kv.first << endl;
//				break;
//			}
//		}
//	}
//
//	return 0;
//}


//问题 c : 统计元音的次数（第六讲）---------------------------------------------------------------------
//int main()
//{
//	int n;
//	cin >> n;
//	string s;
//	getchar();
//	int a, b, c, d, e;
//	while (n--) {
//		a = b = c = d = e = 0;
//		getline(cin,s);
//		for (auto i : s) {
//			if (i == 'a') {
//				++a;
//			} else if(i=='e'){
//				++b;
//			} else if (i == 'i') {
//				++c;
//			} else if (i == 'o') {
//				++d;
//			} else if (i == 'u') {
//				++e;
//			}
//			
//		}
//		cout << "a:" << a << endl;
//		cout << "e:" << b << endl;
//		cout << "i:" << c << endl;
//		cout << "o:" << d << endl;
//		cout << "u:" << e << endl;
//		cout << endl;
//	}
//	return 0;
//}




//问题 b: 绝对值排序（第六讲）-------------------------------------------------------------------------

//int main()
//{
//	int n;
//	while ((cin >> n) && n != 0) {
//		vector<int> arr(n);
//		for (int i = 0; i < n; ++i) {
//			cin >> arr[i];
//		}
//		sort(arr.begin(), arr.end(), [](const int a, const int b) {return abs(a) > abs(b); });
//		for (auto i : arr) {
//			cout << i << " ";
//		}
//		cout << endl;
//	}
//	return 0;
//}




//问题 a: 困难的串问题（第五讲）---------------------------------------------------------------------


// 此问题类似于n皇后问题，我们只需判断当前皇后和前面的皇后是否冲突，而不必判断以前的皇后之间是否冲突（因为以前的已经判断过了）。
// 同样的道理，我们只需判断当前串的后缀，而非所有的字串。
//const int MAXN = 100;
//int n, L;	// 第n小，使用前L个大写字母
//int cnt;	// 记录当前是第几小的困难串
//int S[MAXN];	// 答案数组，用数字代表字母。0代表‘A’，依次类推
//
//bool DFS(int cur) {
//	if (cnt++ == n) {	//每当cnt+1必能增加一个合法字符，当cnt=n时即得到所求字符串
//		for (int i = 0; i < cur; ++i) {
//			cout << (char)(S[i] + 'A');
//		}
//		cout << endl;
//		return true;
//	}
//	for (int i = 0; i < L; ++i) {
//		// 枚举cur位置可能的字符
//		S[cur] = i;
//		bool isHard = true;
//		for (int j = 1; j * 2 <= cur + 1; ++j) {	//检查长度为j*2的后缀
//			bool equal = true;
//			for (int k = 0; k < j; ++k) {
//				if (S[cur - k] != S[cur - j - k]) {
//					equal = false;	//不相等，即暂时可判断为困难串
//					break;
//				}
//			}
//			// 若不是困难串，标记完即可跳出
//			if (equal) {
//				isHard = false;
//				break;
//			}
//		}
//		// 如果是困难串
//		if (isHard) {
//			// 如果当前串为困难的串，并且cnt!=n，继续递归，如果cnt=n，递归结束，直接退出
//			// 如果后序找到了困难串,一路return 会main 函数即可
//			if (DFS(cur + 1)) {
//				return true;
//			}
//		}
//	}
//	return false;
//}
//
//int main()
//{
//	while (cin >> n >> L) {
//
//		DFS(0);
//	}
//	return 0;
//}


//问题 Z: 素数环问题（第五讲）-----------------------------------------------------------------------------
//vector<bool> su(18);
//void check(vector<bool>& arr, int index,string s) {
//	int n = arr.size();
//	if (index > 2) {
//		int k = s[index - 3] - '0' + s[index-2] - '0';
//		if (!su[k]) return;
//	}
//	if (index == n) {
//		int k = s[0] - '0' + s[index-2] - '0';
//		if (su[k]) {
//			cout << s << endl;
//		}
//		return;
//	}
//	for (int i = 1; i < n; ++i) {
//		if (!arr[i]) {
//			arr[i] = true;
//			check(arr, index + 1, s + (char)(i + '0'));
//			arr[i] = false;
//		}
//	}
//}
//int main()
//{
//	int n;
//	
//	for (int i = 1; i <18; ++i) {
//		int q = sqrt(i);
//		int j;
//		for (j = 2; j <= q; ++j) {
//			if (i % j == 0)  break;
//		}
//		if (j > q) su[i] = true;
//	}
//	
//	while (cin >> n) {
//		vector<bool> arr(n + 1,false);	// arr[i]记录数字i是否被选过
//		arr[1] = true;
//		string s="1";
//		check(arr,2,s);
//	}
//	return 0;
//}
//




//问题 Y: 01背包问题（第五讲）----------------------------------------------------------------------------------------

//int main()
//{
//	int N, W;
//	while (cin >> N >> W) {
//		vector<int> weight(N);
//		for (int i = 0; i < N; ++i) {
//			cin >> weight[i];
//		}
//		vector<int> value(N);
//		for (int i = 0; i < N; ++i) {
//			cin >> value[i];
//		}
//
//		vector<int> dp(W + 1);
//		for (int i = 0; i < N; ++i) {
//			for (int rest = W; rest >= weight[i]; --rest) {
//				dp[rest] = max(dp[rest], dp[rest - weight[i]] + value[i]);
//			}
//		}
//		cout << dp[W] << endl;
//	}
//	return 0;
//}


//bool isValid(const vector<int>& vis,int r,int c) {
//	// 循环判断到前r行即可
//	for (int i = 0; i < r; ++i) {
//		// 如果成一列或成斜行，false
//		if (vis[i] == c || abs(r - i) == abs(c - vis[i])) {
//			return false;
//		}
//	}
//	return true;
//}
//int help(vector<int>& vis, int index) {
//	int n = vis.size();
//	if (index == n) {
//		return 1;
//	}
//	int ret = 0;
//	for (int i = 0; i < n; ++i) {
//		// 当前在i行，尝试i行所有列
//		if (isValid(vis,index,i)) {
//			vis[index] = i;
//			ret+=help(vis, index + 1);
//		}
//	}
//	return ret;
//}
//int NQueen(int n) {
//	vector<int> vis(n,0);
//	return help(vis, 0);
//}
//int main()
//{
//	int n;
//	while (cin >> n) {
//		cout << NQueen(n) << endl;	
//	}
//	return 0;
//}


//问题 W: 数字表达式问题（第四讲）-------------------------------------------------------------------------------

//int num[9], n, cnt;	// num读入的数字，n读入的数字个数，cnt解的个数
//char opera[8];	// 插入数字间的符合
//
//void count() {	//根据先‘ ’，再‘*’，最后‘+’‘-’的顺序进行计算
//	int sum;
//	vector<int>data,		//存进行过‘ ’运算的数据
//		new_data;			//存进行过‘*’运算之后的数据
//	vector<char>operate,	//存除‘ ’外的运算符
//		new_operate;		//存除‘ ’，‘*’以外的运算符
//	sum = num[0];			//处理操作符与数据之间的错位
//	// 整合数字和操作符号，取出所谓的‘ ’，并连接‘ ’左右的数字
//	for (int i = 0; i < n - 1; ++i) {
//		if (opera[i] == ' ') {
//			if (sum == 0)		//清除末尾有0但无‘ ’以外运算符的情况，违规情况，不能有前缀0
//				return;
//			sum = sum * 10 + num[i + 1];
//		} else {
//			data.push_back(sum);
//			operate.push_back(opera[i]);
//			sum = num[i + 1];
//		}
//	}
//	data.push_back(sum);	//存入最后一个划分好的数据
//
//	sum = data[0];
//	for (int i = 0; i < operate.size(); ++i) {
//		// 先进行乘法运算
//		if (operate[i] == '*')
//			sum *= data[i + 1];
//		else {
//			new_data.push_back(sum);
//			new_operate.push_back(operate[i]);
//			sum = data[i + 1];
//		}
//	}
//	new_data.push_back(sum);
//	//处理加减法
//	sum = new_data[0];
//	for (int i = 0; i < new_operate.size(); ++i)
//		if (new_operate[i] == '+')
//			sum += new_data[i + 1];
//		else
//			sum -= new_data[i + 1];
//
//	if (sum == 2000) {
//		for (int i = 0; i < operate.size(); ++i)
//			cout << data[i] << operate[i];
//		cout << data[operate.size()] << "=" << sum << endl;
//		cnt++;
//	}
//}
//
//// 共定义4中符号，‘ ’，‘+’，‘-’，‘*’，其中‘ ’是的含义是不做任何操作，单纯的连接前后数字
//// 递归枚举每个数字间隙的上述4种操作符。
//void put_operator(int x)
//{
//	if (x == n - 1)
//	{
//		count();
//		return;
//	}
//	opera[x] = '*';
//	put_operator(x + 1);
//	opera[x] = ' ';		//假定‘ ’为两位及两位以上数字之间的操作符
//	put_operator(x + 1);
//	opera[x] = '+';
//	put_operator(x + 1);
//	opera[x] = '-';
//	put_operator(x + 1);
//}
//
//int main() {
//	while (cin >> n) {
//		char c;	//用char可以一个一个读，方便
//		for (int i = 0; i < n; ++i) {
//			cin >> c;
//			num[i] = c - '0';
//		}
//		cnt = 0;
//		put_operator(0);
//		if (!cnt)
//			cout << "IMPOSSIBLE" << endl;
//	}
//	return 0;
//}


//int main()
//{
//	int n, m;
//	while (cin >> n >> m) {
//		bool flag = false;
//		for (int i = 0; i < n; ++i) {
//			if (i * 2 + (n - i) * 4 == m) {
//				cout << i << " " << (n-i) << endl;
//				flag = true;
//				break;
//			}
//		}
//		if (!flag) {
//			cout << "No answer" << endl;
//		}
//	}
//	return 0;
//}

//int main()
//{
//	int n;
//	while (cin >> n) {
//		long long ret = 1, ans = -1;
//		vector<int> arr(n);
//		for (int i = 0; i < n; ++i) {
//			cin >> arr[i];
//		}
//		// 枚举最大子序列的起点
//		for (int i = 0; i < n; ++i) {
//			ret = 1;
//			for (int j = i; j < n; ++j) {
//				ret *= arr[j];
//				ans = max(ans, ret);
//			}
//		}
//		if (ans < 0) {
//			cout << 0 << endl;
//		} else {
//			cout << ans << endl;
//		}
//	}
//
//	return 0;
//}


//int Gcd(int a, int b) { return b == 0 ? a : Gcd(b, a % b); }
//int main()
//{
//	int n;
//
//	while (cin >> n) {
//		int cnt = 0;
//		/*int m = n * (n + 1) / Gcd(n, n + 1);
//		for (int i = m; i >= n * 2; --i) {
//			for (int j = n; j <= n * 2; ++j) {
//				if (i * j % (i + j) == 0 && i * j / (i + j) == n) {
//					++cnt;
//				}
//			}
//		}
//		cout << cnt << endl;
//		for (int i = m; i >= n * 2; --i) {
//			for (int j = n; j <= n * 2; ++j) {
//				if (i * j % (i + j) == 0 && i * j / (i + j) == n) {
//					printf("1/%d = 1/%d + 1/%d\n", n, i, j);
//				}
//			}
//		}*/
//		//或
//		for (int i = n + 1; i <= 2 * n; ++i) {
//			int j = (n * i) / (i - n);
//			if (n * (i + j) == i * j) {
//				++cnt;
//			}
//		}
//		cout << cnt << endl;
//		for (int i = n + 1; i <= 2 * n; ++i) {
//			int j = (n * i) / (i - n);
//			if (n * (i + j) == i * j) {
//				printf("1/%d = 1/%d + 1/%d\n", n, j, i);
//			}
//		}
//	}
//	return 0;
//}


//
//bool check(int a,int b) {
//	vector<bool> arr(10, false);
//	if (b < 1e5) {
//		arr[0] = true;
//	}
//
//	while (a) {
//		if (arr[a % 10]) {
//			return false;
//		} else {
//			arr[a % 10] = true;
//		}
//		a /= 10;
//	}
//	while (b) {
//		if (arr[b % 10]) {
//			return false;
//		} else {
//			arr[b% 10] = true;
//		}
//		b /= 10;
//	}
//	return true;
//}
//int main()
//{
//	int n;
//	while (cin >> n) {
//		for (int i = 1234; n * i < 98765; ++i) {
//			if(n*i>98765) break;
//			if (check(i, n * i)) {
//				printf("%5d / %05d = %d\n", n * i, i, n);
//			}
//		}
//	}
//	return 0;
//}


//int main()
//{
//	int n, m;
//	while (cin >> n >> m) {
//		bool flag = false;
//		for (int i = 0; i <= m / 5; ++i) {
//			for (int j = 0; j <= m / 3 && m >= i + j; ++j) {
//				int k = m - i - j;
//				if (k % 3) continue;
//				if (i * 5 + j * 3 + k / 3 == n) {
//					cout << i << " " << j << " " << k << endl;
//					flag = true;
//				}
//			}
//		}
//		if (!flag) {
//			cout << "no answer" << endl;
//		}
//	}
//	return 0;
//}


//int medianOfMedians(vector<int> arr, int L, int R);
//// 快排
//vector<int> partition(vector<int>& arr, int L, int R, int pivot) {
//	int less = L - 1;
//	int more = R + 1;
//	int cur = L;
//	while (cur < more) {
//		if (arr[cur] < pivot) {
//			swap(arr[++less], arr[cur++]);
//		} else if (arr[cur] > pivot) {
//			swap(arr[cur], arr[--more]);
//		} else {
//			++cur;
//		}
//	}
//	return { less + 1,more - 1 };
//}
//// 插入排序，5个数据下，最优
//void insertionSort(vector<int>& arr, int L, int R) {
//	for (int i = L + 1; i <= R; ++i) {
//		for (int j = i - 1; j >= L && arr[j] > arr[j + 1]; --j) {
//			swap(arr[j], arr[j + 1]);
//		}
//	}
//}
//// 返回中位数
//int getMedian(vector<int>& arr, int L, int R) {
//	insertionSort(arr, L, R);
//	return arr[(L + R) / 2];
//}
//// arr[L..R] 如果排序的话，位于index位置的是什么（index一定再arr范围中）
//int bfprt(vector<int>& arr, int L, int R, int index) {
//	if (L == R) {
//		return arr[L];
//	}
//	int pivot = medianOfMedians(arr, L, R);
//	vector<int> rge = partition(arr, L, R, pivot);
//	if (index >= rge[0] && index <= rge[1]) {
//		return arr[index];
//	} else if (index < rge[0]) {
//		return bfprt(arr, L, rge[0] - 1, index);
//	} else {
//		return bfprt(arr, rge[1] + 1, R, index);
//	}
//}
//
//// arr[L...R] 五个数一组
//// 每个小组内部排序
//// 每个小组中位数拎出来，组成marr
//// marr中的中位数，返回
//int medianOfMedians(vector<int> arr, int L, int R) {
//	int size = R - L + 1;
//	// 有没有多余的一组（不够五个数）
//	int offset = size % 5 == 0 ? 0 : 1;
//	vector<int> marr(size / 5 + offset);
//	for (int team = 0; team < marr.size(); ++team) {
//		int teamFirst = L + team * 5;
//		marr[team] = getMedian(arr, teamFirst, min(R, teamFirst + 4));
//	}
//	return bfprt(marr, 0, marr.size() - 1, marr.size() / 2);
//}
//
//
//
//int minKth(vector<int> array, int k) {
//	return bfprt(array, 0, array.size() - 1, k - 1);
//}
//int main()
//{
//	int n, m,k;
//	cin >> n>>m>>k;
//	while (n--) {
//		vector<int> arr(m);
//		for (int i = 0; i < m; ++i) {
//			cin >> arr[i];
//		}
//		cout <<minKth(arr, k) << endl;
//		
//	}
//	return 0;
//}


//pair<int, int> FindMaxAndMin(const vector<int>& arr, int left, int right) {
//	if (left == right) {
//		return { arr[left],arr[left] };
//	}
//	int mid = left + (right - left) / 2;
//	auto ret1 = FindMaxAndMin(arr, left, mid);
//	auto ret2 = FindMaxAndMin(arr, mid + 1, right);
//	return { min(ret1.first,ret2.first),max(ret1.second,ret2.second) };
//
//}
//int main()
//{
//	int n, m;
//	cin >> n;
//	while (n--) {
//		cin >> m;
//		vector<int> arr(m);
//		for (int i = 0; i < m; ++i) {
//			cin >> arr[i];
//		}
//		auto ret = FindMaxAndMin(arr, 0, m - 1);
//		cout << ret.second << " " << ret.first << endl;
//	}
//	return 0;
//}


//long long Gcd(int a, int b) { return b == 0 ? a : Gcd(b, a % b); }
//int main()
//{
//	int n, a, b;
//	cin >> n;
//	while (n--) {
//		cin >> a >> b;
//		cout << (long long)a*b/Gcd(a, b) << endl;
//	}
//	return 0;
//}
//



//
//int Fibonacci(int n) {
//	int a = 1, b = 0, c;
//	while (n--) {
//		c = a + b;
//		a = b;
//		b = c;
//	}
//	return c;
//
//}
//int main()
//{
//	int n,tmp;
//	cin >> n;
//	while (n--) {
//		cin >> tmp;
//		cout << Fibonacci(tmp) << endl;
//	}
//	return 0;
//}



//int FindMax(const vector<int>& arr, int left,int right) {
//	if (left == right) {
//		return arr[left];
//	}
//	int mid = left + (right - left) / 2;
//	return max(FindMax(arr, left, mid), FindMax(arr, mid+1, right));
//}
//int main()
//{
//	int n,m;
//	cin >> n;
//	while (n--) {
//		cin >> m;
//		vector<int> arr(m);
//		for (int i = 0; i < m; ++i) {
//			cin >> arr[i];
//		}
//		int ret = INT_MAX;
//		cout << FindMax(arr, 0, m - 1) << endl;
//	}
//	return 0;
//}


//int main()
//{
//	int n, tmp;
//	cin >> n;
//	while (n--) {
//		long long sum = 1;
//		cin >> tmp;
//		for (int i = 1; i <= tmp; ++i) {
//			sum *= i;
//		}
//		cout << sum << endl;
//	}
//	return 0;
//}


//bool check(const vector<int>& arr) {
//	for (auto i : arr) {
//		if (i != 0) {
//			return true;
//		}
//	}
//	return false;
//}
//void Find(const vector<int>& arr, const vector<int>& comp) {
//	int a = 0, b = 0;
//	vector<bool> visSame(arr.size(), false);
//	vector<bool> vis(arr.size(), false);	// comp中标记已被筛出
//
//	for (int i = 0; i < arr.size(); ++i) {
//		if (arr[i] == comp[i]) {
//			++a;
//			vis[i] = visSame[i] = true;		//源组和比较组相同位置进行标记
//		}
//	}
//	for (int i = 0; i < arr.size(); ++i) {	// 枚举comp进行比较
//		if(visSame[i])continue;	// 有相同位置跳过
//		for (int j = 0; j < arr.size(); ++j) {	// 枚举arr比较
//			if(vis[j]) continue;	// 已被筛选过，跳过
//			if (comp[i] == arr[j]) {
//				++b;
//				vis[j] = true;	// 筛选出
//				break;	//找到匹配的，立即跳出
//			}
//		}
//	}
//	printf("(%d,%d)\n", a, b);
//}
//// 或
//void Find1(const vector<int>& arr, const vector<int>& comp) {
//	int a = 0, b = 0;
//	for (int i = 0; i < arr.size(); ++i) {
//		if (arr[i] == comp[i]) {
//			++a;
//		}
//	}
//	for (int j = 1; j <= 9; j++)
//	{
//		int c1 = 0, c2 = 0;
//		for (int i = 0; i < arr.size(); i++)
//		{
//			if (arr[i] == j) ++c1;
//			if (comp[i] == j) ++c2;
//		}
//		if (c1 < c2)
//			b = b + c1;
//		else
//			b = b + c2;
//	}
//	printf("(%d,%d)\n", a, b-a);
//}
//int main()
//{
//	int n;
//	cin >> n; 
//	int cnt = 0;
//	while (n) {
//		vector<int> arr(n);
//		vector<int> comp(n);
//
//		printf("Game %d:\n", ++cnt);
//		for (int i = 0; i < n; ++i) {
//			cin >> arr[i];
//		}
//		for (int i = 0; i < n; ++i) {
//			cin >> comp[i];
//		}
//		while (check(comp)) {
//			Find1(arr, comp);
//			for (int i = 0; i < n; ++i) {
//				cin >> comp[i];
//			}
//		}
//		cin >> n;
//	}
//	return 0;
//}


//int main()
//{
//	string s;
//	cin >> s;
//	int left = 0, right = 1, piovt = 1;
//	while (1) {
//		left = 0;
//		// 右指针右移动知道left和right指向的是相同字符
//		while (s[right] != s[left]) { ++right; }
//
//		piovt = right; 
//		while (s[right]==s[left] && left!=piovt) {
//			++right;
//			++left;
//		}
//
//		if (left == piovt) {
//			cout << piovt << endl;
//			break;
//		} else {
//			right = piovt + 1;
//		}
//
//	}
//	return 0;
//}


//void Print(int a, int b) {
//	printf("%5d\n", a);
//	printf("X%4d\n", b);
//	printf("-----\n");
//
//	printf("%5d\n", a * (b % 10));
//	printf("%4d\n", a * (b / 10));
//	printf("-----\n");
//	printf("%5d\n", a * b);
//}
//bool check(int n, vector<int>& arr) {
//	while (n) {
//		if (find(arr.begin(), arr.end(), n % 10) == arr.end()) return false;
//		n /= 10;
//	}
//	return true;
//}
//int main()
//{
//	int n;
//	cin >> n;
//	vector<int> arr;
//	while (n) {
//		arr.push_back(n % 10);
//		n /= 10;
//	}
//	int len = arr.size();
//	sort(arr.begin(), arr.end());		// 题目有些问题或OJ判题系统太垃圾，题目并未要求乘数是有序递增的，单不排序的话不能AC
//	int cnt = 0;
//	for (int i = 0; i < len; ++i) {
//		if (arr[i] == 0) continue;
//		for (int j = 0; j < len; ++j) {
//			for (int k = 0; k < len; ++k) {
//				for (int x = 0; x < len; ++x) {
//					if (arr[x] == 0) continue;
//					for (int y = 0; y < len; ++y) {
//						int a = arr[i] * 100 + arr[j] * 10 + arr[k];
//						int b = arr[x] * 10 + arr[y];
//						int ret = a * b;
//						if (check(ret, arr) && check(a * (b % 10), arr) && check(a * (b / 10), arr)) {
//							printf("<%d>\n", ++cnt);
//							Print(a, b);
//							printf("\n");
//						}
//					}
//				}
//			}
//		}
//	}
//	printf("The number of solutions=%d", cnt);
//	return 0;
//}


//int main()
//{
//	int n, k;
//	cin >> n >> k;
//	vector<bool> arr(n + 1, false);
//	for (int i = 1; i <= k; ++i) {
//		for (int j = i; j <= n; j += i) {
//			arr[j] = !arr[j];
//		}
//	}
//	for (int i = 1; i <= n; ++i) {
//		if (arr[i]) {
//			cout << i << " ";
//		}
//	}
//	return 0;
//}


//int main()
//{
//	int a, b, c;
//	int a1, b1, c1, i, cnt = 0;
//	while (cin >> a >> b >> c) {
//		for (i = 10; i <= 100; ++i) {
//			a1 = i % 3;
//			b1 = i % 5;
//			c1 = i % 7;
//			if (a1 == a && b1 == b && c1 == c) {
//				printf("Case %d: %d\n", ++cnt, i);
//				break;
//			}
//		}
//		if (i > 100) {
//			printf("Case %d: No answer\n", ++cnt);
//		}
//	}
//
//	return 0;
//}


////int dp[525610];
//int arr[1010];
//int brr[1010];
//int n, m;
//int ret = 0;
//int dp[1010][52561];	// dp[i][j]还要i个物品没决定，空间还剩下j能获得的最大金币
//void DFS(int index, int sum, int rest) {
//	if (rest < 0) {
//		return;
//	}
//	if (sum <= dp[index][rest]) {
//		return;
//	}
//	dp[index][rest]=max()
//	dp[index][rest] = sum;
//
//	DFS(index + 1, sum + brr[index], rest - arr[index]);
//	DFS(index + 1, sum, rest);
//}
//int main()
//{
//	cin >> n >> m;
//	for (int i = 0; i < n; ++i) {
//		cin >> arr[i];
//	}
//	for (int i = 0; i < n; ++i) {
//		cin >> brr[i];
//	}
//	for (int i = m; i >= 0; --i) {
//		if(int j=0;j)
//	}
//	memset(dp, 0x3f, sizeof(dp));
//	DFS(0, 0, m);
//	cout << dp[0][m];
//	return 0;
//}


//struct node {
//	int val;
//	node* left;
//	node* right;
//	node(int x):val(x),left(nullptr),right(nullptr){}
//};
//int z[21], x[21];
//node* build(int i) {
//	node* head = new node(x[i]);
//
//}
//int main()
//{
//	int n;
//	cin >> n;
//	for (int i = 0; i < n; ++i) {
//		cin >> z[i];
//	}
//	for (int i = 0; i < n; ++i) {
//		cin >> x[i];
//	}
//	reverse(x, x + n);
//	node* head = build(0);
//	return 0;
//}


//struct node {
//	string name;
//	int n;
//	unordered_set<int> se;
//	bool operator<(const node& a)const {
//		if (se.size() != a.se.size()) {
//			return se.size() > a.se.size();
//		}
//		return n < a.n;
//	}
//};
//int main()
//{
//	int n;
//	cin >> n;
//	vector<node> arr(n);
//	for (int i = 0; i < n; ++i) {
//		cin >> arr[i].name >> arr[i].n;
//		int tmp;
//		for (int j = 0; j < arr[i].n; ++j) {
//			cin >> tmp;
//			arr[i].se.insert(tmp);
//		}
//	}
//	sort(arr.begin(), arr.end());
//	if (arr.size() >= 3) {
//		cout << arr[0].name << " " << arr[1].name << " " << arr[2].name;
//	} else if (arr.size() == 2) {
//		cout << arr[0].name << " " << arr[1].name <<  " -";
//
//	} else if (arr.size() == 1) {
//		cout << arr[0].name << " - -";
//	} else {
//		cout << "- - -";
//	}
//	return 0;
//}




//int main()
//{
//	int N,S;
//	cin >> N >> S;
//	vector<string> arr(N);
//	vector<int> tmp(S);
//	for (int i = 0; i < N; ++i) {
//		cin >> arr[i];
//	}
//	int cnt = 0;
//	int a;
//	unordered_map<string, int> ans;
//	for (int i = 0; i < N / S; ++i) {
//		for (int j = 0; j < S; ++j) {
//			cin >> tmp[j];
//		}
//		for (int j = S-1; j >= 0; --j) {
//			ans[arr[cnt++]] = tmp[j];
//		}
//	}
//	int k;
//	cin >> k;
//	string p;
//	while (k--)
//	{
//		cin >> p;
//		auto it = ans.find(p);
//		if (it == ans.end()) {
//			cout << "Wrong Number" << endl;
//		} else {
//			cout << it->second << endl;
//		}
//	}
//	return 0;
//}


//bool issu(int n) {
//	if (n == 1) {
//		return false;
//	}
//	int q = sqrt(n);
//	for (int i = 2; i <= q; ++i) {
//		if (n % i == 0) {
//			return false;
//		}
//	}
//	return true;
//}
//int main()
//{
//	int m, n;
//	cin >> m >> n;
//	vector<int> arr;
//	for (int i = m; i <= n; ++i) {
//		if (issu(i)) {
//			arr.push_back(i);
//		}
//	}
//	int ret = 0;
//	int len = arr.size();
//	for (int i = 0; i < len; ++i) {
//		for (int j = i + 1; j < len; ++j) {
//			for (int k = j + 1; k < len; ++k) {
//				if (issu(arr[i] * arr[j] + arr[k]) && issu(arr[i] * arr[k] + arr[j]) && issu(arr[k] * arr[j] + arr[i])) {
//					++ret;
//				}
//			}
//		}
//	}
//	cout << ret;
//	return 0;
//}



//int arr[100][100];
//int ret[100];
//int main()
//{
//	int n, k, x;
//	cin >> n >> k >> x;
//	int sum = 0;
//	for (int i = 0; i < n; ++i) {
//		sum = 0;
//		for (int j = 0; j < n; ++j) {
//			cin >> arr[i][j];
//			sum += arr[i][j];
//		}
//		ret[i] = sum;
//	}
//	for (int j = 1; j < n; j += 2) {
//		ret[0] -= arr[0][j];
//		ret[0] += x;
//	}
//	for (int i = 1; i < n; ++i) {
//		sum = 0;
//		for (int j = 0; j < n; j += 2) {
//			sum += arr[i][j];
//		}
//		for (int j = 1; j < n; j += 4) {
//			sum += arr[i - 1][j];
//		}
//		for (int j = 3; j < n; j += 4) {
//			if (i < k) {
//				sum += x;
//			} else {
//				sum += arr[i - k][j];
//			}
//		}
//		ret[i] = sum;
//	}
//
//	for (int i = 0; i < n-1; ++i) {
//		cout << ret[i] << " ";
//	}
//	cout << ret[n - 1];
//	return 0;
//}


//int main()
//{
//	string s;
//	int n;
//	cin >> n;
//	while (n--) {
//		cin >> s;
//		if (s.empty()) {
//			cout << "Y" << endl;
//			continue;
//		}
//		char prev = s[0];
//		bool falg = false;
//		for (int i = 0; i < s.size()-1; ++i) {
//			if (islower(s[i])) {
//				if (isupper(s[i + 1]) && tolower(s[i+1])==s[i]|| s[i + 1] == s[i] - 1) {
//				} else {
//					falg = true;
//					break;
//				}
//			} else {
//				if (islower(s[i + 1]) && toupper(s[i + 1]) == s[i] || s[i + 1] == s[i] + 1) {
//				}else{
//					falg = true;
//					break;
//				}
//			}			
//		}
//		if (falg) {
//			cout << "N" << endl;
//		} else {
//			cout << "Y" << endl;
//		}
//	}
//	return 0;
//}

//
//#include <iostream>
//using namespace std;
//int f(int n) {
//	int ret = 0;
//	while (n) {
//		ret += n % 10;
//		n /= 10;
//	}
//	return ret;
//}
//int main()
//{
//	int n,ret,i;
//	cin >> n;
//	while (n--) {
//		cin >> ret;
//		int same = f(ret * 2);
//		for (i = 3; i <= 9; ++i) {
//			if (same != f(ret * i)) {
//				break;
//			}
//		}
//		if (i > 9) {
//			cout << same << endl;
//		} else {
//			cout << "NO" << endl;
//		}
//
//	}
//	return 0;
//}
//
//#include <iostream>
//using namespace std;
//int main()
//{
//	int n;
//	cin >> n;
//	int sex, h, w;
//	while (n--) {
//		cin >> sex >> h >> w;
//		int hx = 130, wx = 27;
//		if (sex == 0) {
//			hx = 129;
//			wx = 25;
//		}
//		if (h < hx) {
//			cout << "duo chi yu! ";
//		} else if(h>hx){
//			cout << "ni li hai! ";
//		} else {
//			cout << "wan mei! ";
//		}
//
//		if (w < wx) {
//			cout << "duo chi rou!";
//		} else if (w > wx) {
//			cout << "shao chi rou!";
//		} else {
//			cout << "wan mei!";
//		}
//		cout << endl;
//	}
//	return 0;
//}

//#include <iostream>
//using namespace std;
//int main()
//{
//	double a,c;
//	int b;
//	cin >> a >> b >> c;
//	double ret;
//	ret = b == 0 ? a * 2.455 : a * 1.26;
//	printf("%.2lf ", ret);
//	if (ret >= c) {
//		printf("T_T");
//	} else {
//		printf("^_^");
//	}
//
//	return 0;
//}

//#include <iostream>
//using namespace std;
//int main()
//{
//	int a, b;
// 	cin >> a >> b;
//	cout << a+b-1;
//}

//#include <iostream>
//using namespace std;
//int main()
//{
//	int n;
//	scanf("%d", &n);
//	//cout << "print(" << n << ")";
//	printf("print(%d)", n);
//	return 0;
//}

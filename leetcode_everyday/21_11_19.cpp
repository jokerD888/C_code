
//397. 整数替换
#include<unordered_map>
//递归枚举
//递归枚举所有情况，偶数只有/2一种情况，奇数+1或-1,奇数操作完后必/2，此两步可合一
//为避免溢出，用n/2,n/2+1,替代(n-1)/2,(n+1)/2,注意此时的n为奇数
class Solution {
public:
	int integerReplacement(int n) {
		if (n == 1) {
			return 0;
		}
		if (n % 2 == 0) {
			return 1 + integerReplacement(n / 2);
		}
		return 2 + min(integerReplacement(n / 2), integerReplacement(n / 2 + 1));
	}
};



//在上述递归过程中，会有一些无效的递归，此前已经计算过相同的递归途径，用一map将其记录下来，即可省去大量递归
class Solution {
private:
	unordered_map<int, int> memo;

public:
	int integerReplacement(int n) {
		if (n == 1) {
			return 0;
		}

		//查找递归是否已记录
		if (memo.count(n)) {
			return memo[n];
		}

		if (n % 2 == 0) {
			return memo[n] = 1 + integerReplacement(n / 2);
		}
		return memo[n] = 2 + min(integerReplacement(n / 2), integerReplacement(n / 2 + 1));
	}
};



//贪心
//较于上法，时间效率相同，但可空间可达到O(1)
//当 n 为偶数时，我们只有唯一的方法将 n 替换为 n/2 
//当 n 为奇数时，n 除以4 的余数要么为1，要么为3。
//	如果为1，可以断定，应将n变为(n-1)/2,而(n-1)/2又是奇数，
//		如果下一步进行?1 再除以2得到 （n-1)/4?,那么从 (n-1)/2可以除以2 ，得到同样的结果；
//		如果下一步进行+1 再除以2得到 （n+3)/4?,那么从 (n-1)/2可以除以2再+1， 得到同样的结果；
//  因此，此种情况下，将n变为(n-1)/2总不会劣于（n+1)/2
//	如果为3，同理可得，应将n变为(n+1)/2
class Solution {
public:
	int integerReplacement(int n) {
		int ans = 0;
		while (n != 1) {
			//偶数
			if (n % 2 == 0) {
				++ans;
				n /= 2;
			} else if (n % 4 == 1) {	
				ans += 2;
				n /= 2;
			} else {
				if (n == 3) {
					ans += 2;
					n = 1;
				} else {
					ans += 2;
					n = n / 2 + 1;
				}
			}
		}
		return ans;
	}
};


#include<queue>
//841. 钥匙和房间
//dfs
class Solution {
public:
    bool canVisitAllRooms(vector<vector<int>>& rooms) {
        vector<bool> visited(rooms.size(),false);
        dfs(rooms, visited,0);
        for (auto i : visited) {
            if (!i)
                return false;
        }
        return true;
    }

    void dfs(vector<vector<int>>& rooms, vector<bool>& visited, int index) {
        if (visited[index])
            return;
        visited[index] = true;
        for (int i = 0; i < rooms[index].size(); i++) {
            dfs(rooms, visited, rooms[index][i]);
        }
        return;
    }
};

//官解
class Solution {
public:
    vector<int> vis;
    int num;

    void dfs(vector<vector<int>>& rooms, int x) {
        vis[x] = true;
        num++;
        for (auto& it : rooms[x]) {
            if (!vis[it]) {
                dfs(rooms, it);
            }
        }
    }

    bool canVisitAllRooms(vector<vector<int>>& rooms) {
        int n = rooms.size();
        num = 0;
        vis.resize(n);
        dfs(rooms, 0);
        return num == n;
    }
};

//bfs
class Solution {
public:
    bool canVisitAllRooms(vector<vector<int>>& rooms) {
        vector<bool> visited(rooms.size(), false);
        queue<int> roomQueue;
        visited[0] = true;
        roomQueue.push(0);
        while (!roomQueue.empty()) {
            int index = roomQueue.front();
            roomQueue.pop();
            for (auto &r : rooms[index]) {
                if (!visited[r]) {
                    visited[r] = true;
                    roomQueue.push(r);
                }
            }
        }
        for (auto i : visited) {
            if (!i)
                return false;
        }
        return true;
    }
};

//官解
class Solution {
public:
    bool canVisitAllRooms(vector<vector<int>>& rooms) {
        int n = rooms.size(), num = 0;
        vector<int> vis(n);
        queue<int> que;
        vis[0] = true;
        que.emplace(0);
        while (!que.empty()) {
            int x = que.front();
            que.pop();
            num++;
            for (auto& it : rooms[x]) {
                if (!vis[it]) {
                    vis[it] = true;
                    que.emplace(it);
                }
            }
        }
        return num == n;
    }
};

//可借鉴官解的num来记录能进入的房间数，可避免对visited的遍历


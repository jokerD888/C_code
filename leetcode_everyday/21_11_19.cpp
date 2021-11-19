
//397. �����滻
#include<unordered_map>
//�ݹ�ö��
//�ݹ�ö�����������ż��ֻ��/2һ�����������+1��-1,������������/2���������ɺ�һ
//Ϊ�����������n/2,n/2+1,���(n-1)/2,(n+1)/2,ע���ʱ��nΪ����
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



//�������ݹ�����У�����һЩ��Ч�ĵݹ飬��ǰ�Ѿ��������ͬ�ĵݹ�;������һmap�����¼����������ʡȥ�����ݹ�
class Solution {
private:
	unordered_map<int, int> memo;

public:
	int integerReplacement(int n) {
		if (n == 1) {
			return 0;
		}

		//���ҵݹ��Ƿ��Ѽ�¼
		if (memo.count(n)) {
			return memo[n];
		}

		if (n % 2 == 0) {
			return memo[n] = 1 + integerReplacement(n / 2);
		}
		return memo[n] = 2 + min(integerReplacement(n / 2), integerReplacement(n / 2 + 1));
	}
};



//̰��
//�����Ϸ���ʱ��Ч����ͬ�����ɿռ�ɴﵽO(1)
//�� n Ϊż��ʱ������ֻ��Ψһ�ķ����� n �滻Ϊ n/2 
//�� n Ϊ����ʱ��n ����4 ������ҪôΪ1��ҪôΪ3��
//	���Ϊ1�����Զ϶���Ӧ��n��Ϊ(n-1)/2,��(n-1)/2����������
//		�����һ������?1 �ٳ���2�õ� ��n-1)/4?,��ô�� (n-1)/2���Գ���2 ���õ�ͬ���Ľ����
//		�����һ������+1 �ٳ���2�õ� ��n+3)/4?,��ô�� (n-1)/2���Գ���2��+1�� �õ�ͬ���Ľ����
//  ��ˣ���������£���n��Ϊ(n-1)/2�ܲ������ڣ�n+1)/2
//	���Ϊ3��ͬ��ɵã�Ӧ��n��Ϊ(n+1)/2
class Solution {
public:
	int integerReplacement(int n) {
		int ans = 0;
		while (n != 1) {
			//ż��
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
//841. Կ�׺ͷ���
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

//�ٽ�
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

//�ٽ�
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

//�ɽ���ٽ��num����¼�ܽ���ķ��������ɱ����visited�ı���


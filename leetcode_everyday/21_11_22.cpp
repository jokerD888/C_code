
//662. �����������
#include<queue>
#include<map>
 struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode* left, TreeNode* right) : val(x), left(left), right(right) {}
    
};
 //������ȱ���-----------------------------------------------------------------------------
 ////��pair��ÿ���ڵ�һ��pos���浱ǰ�ڵ�����ȫ���������ǲ��������������R * 2 - L * 2��������R * 2 + 1 - L * 2,
//�ҵ�ͬһ������ߵĽڵ�posΪL,���ұߵĽڵ�posΪR,��ȼ�ΪR-L+1��
 ////��ĳ����ʱ�̵�nodeQueue�Ĵ�С�����ֲ�ͬ�Ĳ���
 class Solution {
 public:
     int widthOfBinaryTree(TreeNode* root) {
         queue<pair<TreeNode*, int>> nodeQueue;
         nodeQueue.push(make_pair(root, 0));
         int ans = 0;
         while (!nodeQueue.empty()) {
             int size = nodeQueue.size(), L = nodeQueue.front().second, R;
             while (size--) {
                 TreeNode* node = nodeQueue.front().first;
                 R = nodeQueue.front().second;
                 nodeQueue.pop();
                 if (node->left) {
                     nodeQueue.push(make_pair(node->left, R * 2 - L * 2));
                 }
                 if (node->right) {
                     nodeQueue.push(make_pair(node->right, R * 2 + 1 - L * 2));
                 }
             }
             ans = max(ans, R - L + 1);
         }
         return ans;
     }
 };
 //�������棬�����ǽ�val��ֵ�滻Ϊ��pos
 class Solution {
 public:
     int widthOfBinaryTree(TreeNode* root) {
         if (root == nullptr)
             return 0;
         int res = 0;
         queue<TreeNode* >Q;
         root->val = 0;
         Q.push(root);
         while (!Q.empty()) {
             res = max(res, Q.back()->val - Q.front()->val + 1);
             int width = Q.size();
             int offset = Q.front()->val;
             while (width--) {
                 TreeNode* curr = Q.front();
                 Q.pop();
                 curr->val -= offset;
                 if (curr->left) {
                     curr->left->val = curr->val * 2;
                     Q.push(curr->left);
                 }
                 if (curr->right) {
                     curr->right->val = curr->val * 2 + 1;
                     Q.push(curr->right);
                 }
             }
         }
         return res;
     }
 };

 //��
 class Solution {
 public:

     struct AnnotatedNote {
         TreeNode* node;
         int depth, pos;
         AnnotatedNote(TreeNode* n, int d, int p) :node(n), depth(d), pos(p) {}
     };
     int widthOfBinaryTree(TreeNode* root) {
         queue<AnnotatedNote> nodeQueue;
         nodeQueue.push(AnnotatedNote(root, 0, 0));
         int curDepth = 0, ans = 0;
         int L = 0;
         while (!nodeQueue.empty()) {
             AnnotatedNote cur = nodeQueue.front();
             nodeQueue.pop();
             int R = cur.pos;
             if (curDepth != cur.depth) {
                 curDepth = cur.depth;
                 L = cur.pos;
             }
             if (cur.node->left) {
                 nodeQueue.push(AnnotatedNote(cur.node->left, cur.depth + 1, R * 2 - L * 2));
             }
             if (cur.node->right) {
                 nodeQueue.push(AnnotatedNote(cur.node->right, cur.depth + 1, R * 2 + 1 - L * 2));
             }
            ans = max(ans, R - L + 1);
         }
         return ans;
     }
 };

//�ٽ�JAVAд���������һ�����������
 class Solution {
 public:

     struct AnnotatedNote {
         TreeNode* node;
         int depth;
         long long pos;
         AnnotatedNote(TreeNode* n, int d, int p) :node(n), depth(d), pos(p) {}
     };

     int widthOfBinaryTree(TreeNode* root) {
         queue<AnnotatedNote> nodeQueue;
         nodeQueue.push(AnnotatedNote(root, 0, 0));
         int curDepth = 0;
         long long ans = 0,left=0;
         while (!nodeQueue.empty()) {
             AnnotatedNote cur = nodeQueue.front();
             nodeQueue.pop();
             if (cur.node) {
                 nodeQueue.push(AnnotatedNote(cur.node->left, cur.depth + 1, cur.pos * 2));
                 nodeQueue.push(AnnotatedNote(cur.node->right, cur.depth + 1, cur.pos * 2 + 1));
                 if (curDepth != cur.depth) {
                     curDepth = cur.depth;
                     left = cur.pos;
                 }
                 ans = max(ans, cur.pos - left + 1);

             }
         }
         return ans;
     }
 };







//��ϣ
//�˷����Ȳ����ѿսڵ��������
class Solution {
public:
    int widthOfBinaryTree(TreeNode* root) {
        if (!root)
            return 0;

        queue<TreeNode*> nodeQueue;
        nodeQueue.push(root);
        map<TreeNode*, int> levelMap;
        levelMap.emplace(root, 1);
        int curLevel = 1;   //��ǰ����
        int curLevelNodes = 0;  //��ǰ�����ڵ�
        int cntMax = INT_MIN;   //�������ֵ
        while (!nodeQueue.empty()) {
            TreeNode* cur = nodeQueue.front();
            nodeQueue.pop();
            int curNodeLevel = levelMap[cur];
            if (curNodeLevel == curLevel) {
                curLevelNodes++;
            } else {
                cntMax = max(cntMax,curLevelNodes);
                curLevel++;
                curLevelNodes = 1;
            }
            if (cur->left) {
                levelMap.emplace(cur->left, curNodeLevel + 1);
                nodeQueue.push(cur->left);
            }
            if (cur->right) {
                levelMap.emplace(cur->right, curNodeLevel + 1);
                nodeQueue.push(cur->right);
            }
        }
        cntMax= cntMax = max(cntMax, curLevelNodes);
        return cntMax;
    }
};


//�����������
#include<map>
class Solution {
public:
    int ans;
    map<int, int> left;
    int widthOfBinaryTree(TreeNode* root) {
        ans = 0;
        dfs(root, 0, 0);
        return ans;
    }
    void dfs(TreeNode* root, int depth, int pos) {
        if (!root)
            return;
        if(left.find(depth)==left.end())
            left[depth]= pos;
        ans = max(ans, pos - left[depth] + 1);
        dfs(root->left, depth + 1, 2 * pos);
        dfs(root->right, depth + 1, 2 * pos + 1);
    }
};



int main(void)
{

    TreeNode* root = new TreeNode{ 0 };
    TreeNode* real = root;
    root->left = new TreeNode{ 1 };
    root->right = new TreeNode{ 2 };

    TreeNode* tmp = root->right;
    root = root->left;
    root->left = new TreeNode{ 3 };
    root->right = new TreeNode{ 4 };

    root = tmp;
    root->left = new TreeNode{ 5 };
    root->right = new TreeNode{ 6 };
    root = real;
    
    Solution s;
    s.widthOfBinaryTree(root);


    return 0;
}

//113. ·���ܺ� II
#include<queue>
 struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode* left, TreeNode* right) : val(x), left(left), right(right) {}
    
};
//
////dfs 
//������ȱ����ͻ��ݣ����α�����ÿ��Ҷ�ӣ���Ҷ�Ӻ�Ƚ�����·���Ƿ����targetSum
 class Solution {
 public:
     vector<vector<int>> ret;
     vector<int> path;

     void dfs(TreeNode* root, int targetSum) {
         if (root == nullptr) {
             return;
         }
         path.emplace_back(root->val);
         targetSum -= root->val;
         //������Ҷ�ӽڵ㣬���Ҿ���·��������ĿҪ��
         if (root->left == nullptr && root->right == nullptr && targetSum == 0) {
             //����·�����뵽������
             ret.emplace_back(path);
         }
         dfs(root->left, targetSum);
         dfs(root->right, targetSum);
         path.pop_back();
     }

     vector<vector<int>> pathSum(TreeNode* root, int targetSum) {
         dfs(root, targetSum);
         return ret;
     }
 };

 //bfs
 //����unordered_map parent��¼�ڵ��ϵ����Ϊkey,��Ϊvalue
 //����que_sum��¼ÿ���ڵ㼰��֮ǰ·���ϵĽڵ�value�ܺͣ�һ��������Ҷ�ӽڵ㣬�Ͷ�������ڵ�que_sum��Ŀ�������Ĵ�С�������жϲ���
 //�����Ǵ�β��ͷ���в��룬�����ڲ���ret֮ǰ�����tmp���з�ת
#include<unordered_map>
 class Solution {
 public:
     vector<vector<int>> ret;
     unordered_map<TreeNode*, TreeNode*> parent;

     void getPath(TreeNode* node) {
         vector<int> tmp;
         while (node != nullptr) {
             tmp.emplace_back(node->val);
             node = parent[node];
         }
         reverse(tmp.begin(), tmp.end());
         ret.emplace_back(tmp);
     }

     vector<vector<int>> pathSum(TreeNode* root, int targetSum) {
         if (root == nullptr) {
             return ret;
         }

         queue<TreeNode*> que_node;
         queue<int> que_sum;
         que_node.emplace(root);
         que_sum.emplace(0);

         while (!que_node.empty()) {
             TreeNode* node = que_node.front();
             que_node.pop();
             int rec = que_sum.front() + node->val;
             que_sum.pop();

             if (node->left == nullptr && node->right == nullptr) {
                 if (rec == targetSum) {
                     getPath(node);
                 }
             } else {
                 if (node->left != nullptr) {
                     parent[node->left] = node;
                     que_node.emplace(node->left);
                     que_sum.emplace(rec);
                 }
                 if (node->right != nullptr) {
                     parent[node->right] = node;
                     que_node.emplace(node->right);
                     que_sum.emplace(rec);
                 }
             }
         }
         return ret;
     }
 };

 
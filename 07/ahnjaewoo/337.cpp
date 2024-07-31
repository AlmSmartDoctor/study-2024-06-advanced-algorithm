/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution {
public:
    struct SearchResult {
        int val;
        int root_robbed;
        int child_max;
    };

    SearchResult search(TreeNode* root) {
        SearchResult result;
        if (root->left == NULL && root->right == NULL) {
            result.val = root->val;
            result.root_robbed = 1;
            result.child_max = 0;
            return result;
        }
        else if (root->left == NULL) {
            SearchResult right_result = search(root->right);
            result.child_max = right_result.val;
            if (right_result.child_max + root->val > right_result.val) {
                result.val = right_result.child_max + root->val;
            }
            else {
                result.val = right_result.val;
            }
        }
        else if (root->right == NULL) {
            SearchResult left_result = search(root->left);
            result.child_max = left_result.val;
            if (left_result.child_max + root->val > left_result.val) {
                result.val = left_result.child_max + root->val;
            }
            else {
                result.val = left_result.val;
            }
        }
        else {
            SearchResult left_result = search(root->left);
            SearchResult right_result = search(root->right);
            int child = left_result.val + right_result.val;
            int new_val = root->val + left_result.child_max + right_result.child_max;
            result.child_max = child;
            if (new_val > child) {
                result.val = new_val;
            }
            else {
                result.val = child;
            }
        }
        return result;
    }

    int rob(TreeNode* root) {
        SearchResult result = search(root);
        return result.val;
        // return root->left->left == NULL ? 1 : 2;
    }
};
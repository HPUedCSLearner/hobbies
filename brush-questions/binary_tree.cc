
// [BST 节点删除]
class Solution {
    TreeNode* getMin(TreeNode* root) { // 寻找BST的最小节点
        while (root->left != nullptr) root = root->left;
        return root; // 1、此时root指向此BST的最小值; 2、此时，root->left == nullptr;
    }
public:
    TreeNode* deleteNode(TreeNode* root, int key) {
        if (root == nullptr) return nullptr;
        if (root->val == key) {
            // 情况一 ：要删除的目标节点 没有两个孩子节点
            if (root->right == nullptr) return root->left;
            if (root->left == nullptr) return root->right;

            // 情况二 ：要删除的目标节点 有两个孩子节点 （ 【策略】：用右子树的最小节点，代替目标节点）
            TreeNode* rightMin = getMin(root->right); // 找到待替换的目标节点
            root->right = deleteNode(root->right, rightMin->val); // 此时属于是删除的第一种情况，只是会释放这个节点的指针链接

            rightMin->right = root->right;
            rightMin->left = root->left;
            delete root; // 实际项目中，注意要删除节点占用的空间，否则会内存泄漏
            root = rightMin;
            return root;
        }
        if (key > root->val) root->right = deleteNode(root->right, key);
        if (key < root->val) root->left = deleteNode(root->left, key);
        return root; // 返回这颗BST的根节点
    }
};




/*************************************************************************
	> File Name: 6.BST.cpp
	> Author:赵睿 
	> Mail: 1767153298@qq.com
	> Created Time: 2020年08月08日 星期六 21时18分28秒
 ************************************************************************/

#include<iostream>
using namespace std;

template<typename ValueType>
class TreeNode {
public:
    TreeNode();
    TreeNode(ValueType val);

    ValueType val;
    TreeNode *left;
    TreeNode *right;
};

template<typename ValueType>
class Tree {
public:
    typedef TreeNode<ValueType> NodeType;
    Tree();
    NodeType *insert_node(NodeType *root, ValueType val);
    NodeType *predecesser(NodeType *root); 
    NodeType *erase_node(NodeType *root, ValueType val); 
    void show(NodeType *root);

    friend int main();
    friend TreeNode<ValueType>::TreeNode();
    NodeType *__root;
};


template<typename ValueType>
TreeNode<ValueType>::TreeNode() 
: left(nullptr)
, right(nullptr) {}

template<typename ValueType>
TreeNode<ValueType>::TreeNode(ValueType val)
: val(val)
, left(nullptr)
, right(nullptr) {}

template<typename ValueType>
Tree<ValueType>::Tree() 
: __root(nullptr) {} 

template<typename ValueType>
typename Tree<ValueType>::NodeType *Tree<ValueType>::insert_node(NodeType *root, ValueType val) {
    if (root == nullptr) return new NodeType(val);
    if (root->val == val) return root;
    if (root->val < val) 
        root->right = insert_node(root->right, val);
    else 
        root->left = insert_node(root->left, val);
    return root; 
}

template<typename ValueType>
typename Tree<ValueType>::NodeType *Tree<ValueType>:: predecesser(typename Tree<ValueType>::NodeType *root) {
    NodeType *temp = root->left;
    while (temp->right != nullptr) {
        temp = temp->right;
    }
    return temp;
}

template<typename ValueType>
typename Tree<ValueType>::NodeType *Tree<ValueType>::erase_node(typename Tree<ValueType>::NodeType *root, ValueType val) {
    if (root == nullptr) return root;
    if (root->val < val) {
        root->right = erase_node(root->right, val);
    } else if (root->val > val) {
        root->left = erase_node(root->left, val);
    } else {
        if ((root->left == nullptr) || (root->right == nullptr)) {
            NodeType *temp = (root->left == nullptr) ? root->right : root->left;
            delete root;
            return temp;
        }
        NodeType *pre = predecesser(root);
        root->val = pre->val;
        root->left = erase_node(root->left, pre->val);
    }
    return root; 
}

template<typename ValueType>
void Tree<ValueType>::show(typename Tree<ValueType>::NodeType *root) {
    if (root == nullptr) return ;
    show(root->left);
    cout << root->val << " ";
    show(root->right);
}

int main() {
    Tree<int> tree;
    tree.__root = tree.insert_node(tree.__root, 10);
    tree.__root = tree.insert_node(tree.__root, 9);
    tree.__root = tree.insert_node(tree.__root, 8);
    tree.__root = tree.insert_node(tree.__root, 7);
    tree.__root = tree.insert_node(tree.__root, 6);
    tree.__root = tree.insert_node(tree.__root, 5);
    tree.show(tree.__root);
    cout << endl;
    return 0;
}

#ifndef _BINTREE_H
#define _BINTREE_H

#include <iostream>
#include <string>
#include <stack>
#include <vector>
#include <queue>

using std::cin;
using std::cout;
using std::endl;
using std::istream;
using std::ostream;
using std::string;
using std::stack;
using std::vector;
using std::queue;

template <class T>
class TreeNode {
public:
    TreeNode(const T& d) {data = d;}
    T data;
    TreeNode<T>* left = nullptr;
    TreeNode<T>* right = nullptr;
};

template <class T>
class BinTree {
public:
    // BinTree(const T& d);
    // void buildTreeFromPostfix(string postfix);
    void buildTreeFromArray(vector<T> arr);             // build tree from array
    void buildTreeFromPostfix(string postfix);                            // Only available when T is char
    string getPostfixExpression(TreeNode<T>* root) const;                 // Only available when T is char
    string getPrefixExpression(TreeNode<T>* root) const;                  // Only available when T is char
    string getLevelOrderExpression() const;                               // Only available when T is char
    TreeNode<T>* root = nullptr;
    void showTree(TreeNode<T>* root, ostream& out, int level) const;
    void swapSubTree(TreeNode<T>* root);
    int getLeafNum() const;
    int getWidth() const;
};


// 从后缀表达式创建表达式树
template <>
void BinTree<char>::buildTreeFromPostfix(string postfix) {
    stack<TreeNode<char>* > s;
    for(int i = 0; i < postfix.length(); i++) {
        char ch = postfix[i];
        if(ch == '+' || ch == '-' || ch == '*' || ch == '/') {
            TreeNode<char>* right = s.top();                    // 新树的右子树
            if(s.empty()) {throw "Invalid expression";}
            s.pop();
            TreeNode<char>* left = s.top();                     // 新树的左子树
            if(s.empty()) {throw "Invalid expression";}
            s.pop();
            TreeNode<char>* node = new TreeNode<char>(ch);      // 新树的根节点
            node->left = left; node->right = right;
            s.push(node);                                       // 新树入栈
        } else {
            s.push(new TreeNode<char>(postfix[i]));
        }
    }
    TreeNode<char>* root = s.top();
    s.pop();
    if(!s.empty()) {throw "Invalid expression";}
    this->root = root;
}

template <>
string BinTree<char>::getPostfixExpression(TreeNode<char>* root) const {
    string result = "";
    if(root == nullptr) {return "";}
    result += getPostfixExpression(root->left);                 // 访问左子树
    result += getPostfixExpression(root->right);                // 访问右子树
    string s; s.push_back(root->data);                          // 访问当前节点                    
    result += s;                            
    return result;                                              // 返回结果
}

template <>
void BinTree<char>::showTree(TreeNode<char>* root, ostream& out, int level) const {
    if(root == nullptr) {return;}
    showTree(root->right, out, level+1);
    out << endl;
    for(int i=0; i<level; i++) {out << "  ";}
    out << root->data;
    showTree(root->left, out, level+1);
}

template <class T>
void BinTree<T>::buildTreeFromArray(vector<T> arr) {
    int len = arr.size();
    int firstLeafNodeIndex = (len+1)/2;
    vector<TreeNode<T>* > nodes(len);
    for(int i=0; i<len; i++) {
        nodes[i] = new TreeNode<T>(arr[i]);
    }
    for(int i=0; i<firstLeafNodeIndex; i++) {
        nodes[i]->left = 2*i+1 > len-1 ? nullptr : nodes.at(2*i+1);
        nodes[i]->right = 2*i+2 > len-1 ? nullptr : nodes.at(2*i+2);
    }
    root = nodes[0];
}

template <>
string BinTree<char>::getLevelOrderExpression() const {
    // int pushNum = 1;
    string result = "";
    queue<TreeNode<char>* > bfsQueue;
    bfsQueue.push(root);
    // for(int i=0; i<pushNum; i++) {
    //     if(bfsQueue.front() == nullptr) {
    //         bfsQueue.pop(); pushNum --; continue;
    //     }
    //     bfsQueue.push(bfsQueue.front()->left);
    //     bfsQueue.push(bfsQueue.front()->right);
    //     pushNum += 2;
    //     string str; str.push_back(bfsQueue.front()->data);
    //     result += str;
    //     bfsQueue.pop();
    //     pushNum --;
    // }
    while(!bfsQueue.empty()) {
        if(bfsQueue.front() == nullptr) {
            bfsQueue.pop();
            continue;
        }
        bfsQueue.push(bfsQueue.front()->left);
        bfsQueue.push(bfsQueue.front()->right);
        string str; str.push_back(bfsQueue.front()->data);
        result += str;
        bfsQueue.pop();
    }
    return result;
}

template <class T>
void BinTree<T>::swapSubTree(TreeNode<T>* root) {
    if(root == nullptr) {return;}
    swapSubTree(root->left);
    swapSubTree(root->right);
    TreeNode<char>* temp = root->left;
    root->left = root->right;
    root->right = temp;
}

template <class T>
int BinTree<T>::getLeafNum() const {
    int leafNum = 0;
    queue<TreeNode<T>* > bfsQueue;
    bfsQueue.push(root);
    while(!bfsQueue.empty()) {              
        TreeNode<T>* node = bfsQueue.front();
        bfsQueue.pop();
        if(node->left == nullptr && node->right == nullptr) {
            leafNum ++;
        } else {
            if(node->left != nullptr) {bfsQueue.push(node->left);}
            if(node->right != nullptr) {bfsQueue.push(node->right);}
        }
    }
    return leafNum;
}

template <class T>
int BinTree<T>::getWidth() const {
    int width = 0;
    queue<TreeNode<T>* > bfsQueue;
    bfsQueue.push(root);
    while(!bfsQueue.empty()) {
        int currentLevelNum = bfsQueue.size();                  // 当前层的节点个数
        int loopTime = currentLevelNum;
        while(loopTime --) {                                    // 确保当前层的节点全部出队
            TreeNode<T>* ptr = bfsQueue.front();
            bfsQueue.pop();
            if(ptr->left != nullptr) {bfsQueue.push(ptr->left);}
            if(ptr->right != nullptr) {bfsQueue.push(ptr->right);}
        }
        width = width > currentLevelNum ? width : currentLevelNum;
    }
    return width;
}

#endif
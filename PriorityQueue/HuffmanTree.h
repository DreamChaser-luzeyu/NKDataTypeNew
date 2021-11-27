#ifndef _HUFFMANTREE_H
#define _HUFFMANTREE_H

#include <iostream>
#include <vector>
#include <list>
#include <string>
#include <map>
#include <limits.h>

using std::istream;
using std::ostream;
using std::vector;
using std::list;
using std::string;
using std::map;
using std::endl;

template <class T>
class TreeNode {
public:
    T val;
    TreeNode<T>* left = nullptr;
    TreeNode<T>* right = nullptr;
    int weight;
};

template <class T>
class HuffmanTree {
public:
    TreeNode<T>* root = nullptr;
    void buildTree(list<TreeNode<T>* > arr, const T& zero);
    void buildTreeUsingHeap(vector<TreeNode<T>* > arr, const T& zero);
    void showTree(TreeNode<T>* root, ostream& out, int level) const;
    void buildDic();
    void buildDic(TreeNode<T>* root, string str);
    string encode(const vector<T>& arr) const;
    void decode(string bin, vector<T>& vals) const;
    void showDic(ostream& out) const;
private:
    map<T, string> dic;
    bool isValidCode(string bin) const;
};

template <class T> 
void HuffmanTree<T>::buildTree(list<TreeNode<T>* > arr, const T& zero) {
    TreeNode<T>* maxWeightPtr = new TreeNode<T>; 
    maxWeightPtr->weight = INT_MAX; maxWeightPtr->val = "max";
    while(arr.size() != 1) {                        // 建树，直到只剩一个节点，即为根节点
                                                    // 链表中每次只减少一个节点
        TreeNode<T>* minPtr1 = maxWeightPtr;
        TreeNode<T>* minPtr2 = maxWeightPtr;
        for(TreeNode<T>* ptr : arr) {               
            if(ptr->weight < minPtr1->weight) {
                minPtr2 = minPtr1;                  // 权重倒数第二小的节点(权重最小的节点上一次的值)
                minPtr1 = ptr;                      // 权重最小的节点
            } else if(ptr->weight < minPtr2->weight) {
                minPtr2 = ptr;
            }
        }
        arr.remove(minPtr1);
        arr.remove(minPtr2);
        TreeNode<T>* newNode = new TreeNode<T>; 
        newNode->left = minPtr1; newNode->right = minPtr2;
        newNode->weight = minPtr1->weight + minPtr2->weight;
        newNode->val = zero;
        arr.push_back(newNode);
    }
    root = arr.front();
    delete maxWeightPtr;
}

// template <class T> 
// void HuffmanTree<T>::buildTreeUsingHeap(vector<TreeNode<T>* > arr, const T& zero) {
//     TreeNode<T>* maxWeightPtr = new TreeNode<T>; maxWeightPtr->weight = INT_MAX;
//     // TreeNode<T>* minPtr1 = maxWeightPtr;
//     // TreeNode<T>* minPtr2 = maxWeightPtr;
//     while(arr.size() != 1) {                        // 建树，直到只剩一个节点，即为根节点
//                                                     // 链表中每次只减少一个节点
//         TreeNode<T>* minPtr1 = maxWeightPtr;
//         TreeNode<T>* minPtr2 = maxWeightPtr;
//         for(TreeNode<T>* ptr : arr) {               
//             if(ptr->weight < minPtr1->weight) {
//                 minPtr2 = minPtr1;                  // 权重倒数第二小的节点(权重最小的节点上一次的值)
//                 minPtr1 = ptr;                      // 权重最小的节点
//             } else if(ptr->weight < minPtr2->weight) {
//                 minPtr2 = ptr;
//             }
//         }
//         arr.remove(minPtr1);
//         arr.remove(minPtr2);
//         TreeNode<T>* newNode = new TreeNode<T>; 
//         newNode->left = minPtr1; newNode->right = minPtr2;
//         newNode->weight = minPtr1->weight + minPtr2->weight;
//         arr.push_back(newNode);
//     }
//     root = arr.front();
//     delete maxWeightPtr;
// }

template <class T>
void HuffmanTree<T>::showTree(TreeNode<T>* root, ostream& out, int level) const {
    if(root == nullptr) {return;}
    showTree(root->right, out, level+1);
    out << endl;
    for(int i=0; i<level; i++) {out << "             ";}
    out << "<" << root->val << "," << root->weight << ">";
    showTree(root->left, out, level+1);
}

template <class T>
void HuffmanTree<T>::buildDic() {
    buildDic(root, "");
}

// left - 0 , right - 1
template <class T>
void HuffmanTree<T>::buildDic(TreeNode<T>* root, string str) {
    if(root == nullptr) {return;}
    if(root->left == nullptr && root->right == nullptr) {       // is leaf node
        dic[root->val] = str;
    }
    buildDic(root->left, str + "0");
    buildDic(root->right, str + "1");
}

template <class T>
string HuffmanTree<T>::encode(const vector<T>& arr) const {
    string result = "";
    for(int i=0; i<(int)arr.size(); i++) {
        result += dic.at(arr.at(i));
    }
    return result;
}

template <class T>
bool HuffmanTree<T>::isValidCode(string bin) const {
    for(std::pair<T, string> p : dic) {
        if(p.second == bin) {return true;}
    }
    return false;
}

template <class T>
void HuffmanTree<T>::decode(string bin, vector<T>& vals) const {
    map<T, string> revDic;
    for(std::pair<T, string> p : dic) {
        revDic[p.second] = p.first;
    }
    int cur0 = 0;
    int cur1 = 0;
    for(; cur1<=(int)bin.size(); cur1++) {
        string codeNow = bin.substr(cur0, cur1-cur0);       // 截取的是[cur0, cur1)
        if(isValidCode(codeNow)) {
            vals.push_back(revDic.at(codeNow));
            cur0 = cur1;
        }
    }
}

template <class T>
void HuffmanTree<T>::showDic(ostream& out) const {
    for(std::pair<T, string> p : dic) {
        out << p.first << "\t <--> \t" << p.second;
        out << endl;
    }
}

#endif
#ifndef AVLTREE_H
#define AVLTREE_H

#include <iostream>

using std::istream;
using std::ostream;
using std::endl;

enum TYPE{LL, LR, RR, RL};

template <class K, class V>
class AVLNode {
public:
    K weight;
    V element;
    AVLNode<K, V>* left;
    AVLNode<K, V>* right;
    int bf = 0;
};

template <class K, class V>
class AVLTree {
    typedef AVLNode<K, V>* PNODE;
public:
    AVLNode<K, V>* root = nullptr;
    void insert(AVLNode<K, V>* node);
    AVLNode<K, V>* find(K key);

private:
    bool insertBST(PNODE node, PNODE& pa, PNODE& ppa);                                 // return if the height of a tree changed
    TYPE getType(PNODE pa);
    void updateBF(PNODE pa, PNODE node);
    void processLL(PNODE x, PNODE px);
    void processLR(PNODE x, PNODE px);
    void processRR(AVLNode<K, V>* x, AVLNode<K, V>* px);
    void processRL(AVLNode<K, V>* x, AVLNode<K, V>* px);
};

template <class K, class V>
void AVLTree<K, V>::insert(AVLNode<K, V>* node) {
    PNODE pa = nullptr;  // node a
    PNODE ppa = nullptr; // parent of pa

    // Get a, pa, isTaller and insert as BST
    bool isTaller = insertBST(node, pa, ppa);

    // 没变高，不影响AVL平衡
    if(!isTaller) {return;}
    // 变高了，先更新平衡因子，为“旋转”做准备
    else {updateBF(pa, node);}

    // Maybe node_a does not exist, for example, everything is balanced
    // 只在插入根节点时成立：树变高，且不存在a
    if(pa == nullptr) {std::cout << "balance ? " << endl; return;}

    // 进行旋转
    TYPE type = getType(pa);
    switch(type){
        case LL:
            processLL(pa, ppa);
            break;
        case LR:
            processLR(pa, ppa);
            break;
        case RR:
            processRR(pa, ppa);
            break;
        case RL:
            processRL(pa, ppa);
            break;
    }
}

template <class K, class V>
bool AVLTree<K, V>::insertBST(PNODE node, PNODE& pa, PNODE& ppa) {  // 同时还插入了平衡因子
    bool isTaller;
    if(root == nullptr) {root = node; return true;}                 // 插入根节点
    PNODE pp = nullptr;
    PNODE p = node;
    while(p) {
        if((p->bf == 1) || (p->bf == -1)) {pa = p; ppa = pp;}     // get node A
        pp = p;                                            // update parent of p
        if(node->weight < p->weight) {p = p->left;}
        else if(node->weight > p->weight) {p = p->right;}
        else {p->element = node->element; return false;}      // 重复的Key 总之在这里要return
    }

    // 没变高的情况， 只调整父节点平衡因子
    if(node->element < pp->element) {
        pp->left = node;
        isTaller = (pp->right) == nullptr;                  // if no brother, then tree higher
    }
    else {
        pp->right = node;
        isTaller = (pp->left) == nullptr;
    }

    // 调整父节点平衡因子
    if(!isTaller) {pp->bf = 0;}
    return isTaller;
}

template <class K, class V>
TYPE AVLTree<K, V>::getType(PNODE pa) {
    TYPE type; 
    if(pa->bf == 2) {
        if(pa->left == nullptr) {throw "getType : pa->left is nullptr";}
        if(pa->left->bf == 1) {type = LL;} 
        else if(pa->left->bf == -1){type = LR;} 
        else {throw "getType : pa->bf->left error";}
    } else if(pa->bf == -2){
        if(pa->right == nullptr) {throw "getType : pa->right is nullptr";}
        if(pa->right->bf == 1) {type = RL;} 
        else if(pa->right->bf == -1){type = RR;} 
        else {throw "getType : pa->bf->right error";}
    } else {throw "getType : pa->bf error";}
    return type;
}

template <class K, class V>
void AVLTree<K, V>::processLL(PNODE x, PNODE px) {
    PNODE xl, xr, xll, xlr;
    xl = x->left; xr = x->right;
    xll = xl->left; xlr = xlr->right;
    if(px != nullptr) {
        if(xl->weight < px->weight) {px->left = xl;}
        else {px->right = xl;}
    }
    x->left = xlr;
    x->right = xr;
    xl->left = xll;
}

template <class K, class V>
void AVLTree<K, V>::processRR(PNODE x, PNODE px) {
    PNODE xl, xr, xll, xlr;
    xl = x->left; xr = x->right;
    xll = xl->left; xlr = xlr->right;
    if(px != nullptr) {
        if(xl->weight < px->weight) {px->left = xl;}
        else {px->right = xl;}
    }
    x->left = xlr;
    x->right = xr;
    xl->left = xll;
}

template <class K, class V>
void AVLTree<K, V>::processLR(PNODE x, PNODE px) {
    PNODE xl, xr, xll, xlr;
    xl = x->left; xr = x->right;
    xll = xl->left; xlr = xlr->right;
    if(px != nullptr) {
        if(xlr->weight < px->weight) {px->left = xlr;}
        else {px->right = xlr;}
    }
    xl->left = xll;
    xl->right = xlr->left;
    x->left = xlr->right;
}
 

#endif
#ifndef AVLTREE_H
#define AVLTREE_H

#include <iostream>

using std::istream;
using std::ostream;
using std::endl;

enum TYPE{LL, LR, RR, RL, SKIP};

template <class K, class V>
class AVLNode {
public:
    K weight;
    V element;
    AVLNode<K, V>* left;
    AVLNode<K, V>* right;
    int bf = 0;
    friend ostream& operator<<(ostream& out, AVLNode<K, V> node) {
        out << "<" << node.weight << "," << node.element << ">";
        return out;
    }
};

template <class K, class V>
class AVLTree {
    typedef AVLNode<K, V>* PNODE;
public:
    AVLNode<K, V>* root = nullptr;
    void insert(AVLNode<K, V>* node);
    bool find(K key, PNODE& p, PNODE& pp);
    void showTree(ostream& out) const;
private:
    bool insertBST(PNODE node, PNODE& pa, PNODE& ppa);      // return if the height of a tree changed
                                                            // 通过引用获得a节点及其父节点
    TYPE getType(PNODE pa);
    void updateBF(PNODE pa, PNODE node);
    void processLL(PNODE x, PNODE px);
    void processLR(PNODE x, PNODE px);
    void processRR(AVLNode<K, V>* x, AVLNode<K, V>* px);
    void processRL(AVLNode<K, V>* x, AVLNode<K, V>* px);
    void showTree(PNODE root, ostream& out, int level) const;
};

template <class K, class V>
void AVLTree<K, V>::insert(AVLNode<K, V>* node) {
    PNODE pa = nullptr;  // node a
    PNODE ppa = nullptr; // parent of pa

    // Get a, pa, isTaller and insert as BST
    bool isTaller = insertBST(node, pa, ppa);

    // if(pa != nullptr)
    // {std::cout << "a node : " << *pa << endl;}

    // 没变高，不影响AVL平衡
    if(!isTaller) {/*std::cout << "Not taller" << endl;*/ return;}
    // 变高了，先更新平衡因子，为“旋转”做准备
    else {updateBF(pa, node);}

    // Maybe node_a does not exist, for example, everything is balanced
    // 只在插入根节点时成立：树变高，且不存在a
    if(pa == nullptr) {/*std::cout << "Cannot find node A" << endl;*/ return;}

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
bool AVLTree<K, V>::find(K key, PNODE& p, PNODE& pp) {
    p = root;
    while(p != nullptr) {
        pp = p;
        if(p->weight == key) {return true;}
        if(p->weight < key) {p = p->right;}
        else {p = p->left;}
    }
    return false;
}

template <class K, class V>
void AVLTree<K, V>::showTree(ostream& out) const {
    showTree(root, out, 0);
}

template <class K, class V>
bool AVLTree<K, V>::insertBST(PNODE node, PNODE& pa, PNODE& ppa) {  // 同时还插入了平衡因子
    bool isTaller;
    if(root == nullptr) {root = node; return true;}                 // 插入根节点
    PNODE pp = nullptr;
    PNODE p = root;

    while(p != nullptr) {                                           // 找到要插入位置的parent
        if((p->bf == 1) || (p->bf == -1)) {pa = p; ppa = pp;}       // get node A
        pp = p;                                                     // update parent of p
        if(node->weight < p->weight) {p = p->left;}
        else if(node->weight > p->weight) {p = p->right;}
        else {p->element = node->element; return false;}            // 重复的Key 总之在这里要return
    }

    // 判断树是否变高
    isTaller = pp->bf == 0;                             // better implement
    // 进行插入节点操作
    // 没变高的情况， 只调整父节点平衡因子
    if(node->weight < pp->weight) {
        pp->left = node;
        // isTaller = (pp->right) == nullptr;                  // if no brother, then tree higher
        if(!isTaller) {pp->bf ++;}                          // if tree is not taller, then bf ++
    }
    else {
        pp->right = node;
        if(!isTaller) {pp->bf --;}
    }

    return isTaller;
}

template <class K, class V>
TYPE AVLTree<K, V>::getType(PNODE pa) {
    if(pa == nullptr) {return SKIP;}
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
    } else {/*throw "getType : pa->bf error";*/ return SKIP;}
    return type;
}

template <class K, class V>
void AVLTree<K, V>::updateBF(PNODE beginNode, PNODE node) {
    PNODE p = beginNode;
    if(beginNode == nullptr) {p = root;}
    // K weight = beginNode->weight;
    while(p != node) {
        if(node->weight < p->weight) {             // node inserted at p->left, height ++, bf ++
            p->bf ++;
            p = p->left;
        } else {
            p->bf --;
            p = p->right;
        }
        // pp = p;
        // weight = pp->weight;
    }
}

template <class K, class V>
void AVLTree<K, V>::processLL(PNODE x, PNODE px) {
    PNODE xl, xr, xll, xlr;
    xl = x->left; xr = x->right;
    xll = xl->left; xlr = xl->right;
    if(px != nullptr) {
        if(xl->weight < px->weight) {px->left = xl;}
        else {px->right = xl;}
    } else {root = xl;} 
    x->left = xlr;
    xl->right = x;

    xl->bf = 0; x->bf = 0;
}

template <class K, class V>
void AVLTree<K, V>::processRR(PNODE x, PNODE px) {
    PNODE xl, xr, xrl, xrr;
    xl = x->left; xr = x->right;
    xrl = xr->left; xrr = xr->right;
    if(px != nullptr) {
        if(xr->weight < px->weight) {px->left = xr;}
        else {px->right = xr;}
    } else {root = xr;}
    x->right = xrl;
    xr->left = x;

    xr->bf = 0; x->bf = 0;
}

template <class K, class V>
void AVLTree<K, V>::processLR(PNODE x, PNODE px) {
    PNODE xl, xr, xll, xlr, xlrr, xlrl;
    xl = x->left; xr = x->right;
    xll = xl->left; xlr = xl->right;
    xlrr = xlr->right; xlrl = xlr->left;
    if(px != nullptr) {
        if(xlr->weight < px->weight) {px->left = xlr;}
        else {px->right = xlr;}
    } else {root = xlr;}
    // xl->left = xll;
    xlr->left = xl;
    xlr->right = x;
    xl->right = xlrl;
    x->left = xlrr;

    switch(xlr->bf) {
        case -1:
            xl->bf = 1; x->bf = 0; xlr->bf = 0;
            break;
        case 0:
            xl->bf = 0; x->bf = 0; xlr->bf = 0;
            break;
        case 1:
            xl->bf = 0; x->bf = -1; xlr->bf = 0;
            break;
    }
}

template <class K, class V>
void AVLTree<K, V>::processRL(PNODE x, PNODE px) {
    PNODE xl, xr, xrl, xrr, xrll, xrlr;
    xl = x->left; xr = x->right;
    xrl = xr->left; xrr = xr->right;
    xrll = xrl->left; xrlr = xrl->right;
    if(px != nullptr) {
        if(xrl->weight < px->weight) {px->left = xrl;}
        else {px->right = xrl;}
    } else {root = xrl;}
    
    xrl->right = xr;
    xrl->left = x;
    // xr->right = xrr;
    xr->left = xrlr;
    x->right = xrll;
    switch(xrl->bf) {
        case -1:
            xr->bf = 0; x->bf = 1; xrl->bf = 0;
            break;
        case 0:
            xr->bf = 0; x->bf = 0; xrl->bf = 0;
            break;
        case 1:
            xr->bf = -1; x->bf = 0; xrl->bf = 0;
            break;
    }
}

template <class K, class V>
void AVLTree<K, V>::showTree(PNODE root, ostream& out, int level) const {
    if(root == nullptr) {return;}
    showTree(root->right, out, level+1);
    out << endl;
    for(int i=0; i<level; i++) {out << "        ";}
    out << "<" << root->weight << "," << root->element << "," << root->bf << ">";
    showTree(root->left, out, level+1); 
}
 

#endif
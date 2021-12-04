#include <iostream>
#include <string>
#include <queue>
#include "../BinSearchTree/AVLTree.h"

using std::istream;
using std::ostream;
using std::endl;
using std::string;
using std::queue;


/*
test LL

test RR

test RL

test LR


*/

/*
测试树1
insert 1 1
insert 5 5
insert 10 10 
insert 3 3
insert 2 2
insert 15 15
insert 9 9
insert 13 13
insert 14 14
insert -2 -2
insert -3 -3
*/

/*
测试树2
insert 5 5
insert 3 3 insert 8 8
insert 2 2 insert 4 4 insert 7 7 insert 9 9
insert 1 1 insert 6 6 insert 10 10
*/



template <class K, class V>
int findHeight(AVLNode<K, V>* beginNode) {      // O(log n)
    int height = 0;
    while(beginNode != nullptr) {
        if(beginNode->bf >= 0) {
            beginNode = beginNode->left;
        } else {
            beginNode = beginNode->right;
        }
        height ++;
    }
    return height;
}

template <class K, class V>
AVLNode<K, V>* findNearestLeaf(AVLNode<K, V>* root) {
    queue<AVLNode<K, V>* > q;
    q.push(root);
    while(!q.empty()) {
        int sizeNow = q.size();
        for(int i=0; i<sizeNow; i++) {
            AVLNode<K, V>* front = q.front();
            q.pop();
            if(front == nullptr) {continue;}
            if(front->left == nullptr && front->right == nullptr) {
                return front;
            }
            q.push(front->left);
            q.push(front->right);
        }
    }
    return nullptr;
}


template <class K, class V>
void avlCmd(istream& in, ostream& out) {
    typedef AVLNode<K, V>* PNODE;
    out << "insert [key] [val]" << endl
        << "find [key]" << endl
        << "height" << endl
        << "showTree" << endl;
    AVLTree<K, V> avlTree;
    while(true) {
        string cmd; in >> cmd;
        if(cmd == "insert"){
            K key; V val; in >> key >> val;
            AVLNode<K, V>* node = new AVLNode<K, V>;
            node->weight = key; node->element = val;
            avlTree.insert(node);
        }else if(cmd == "find") {
            K key; in >> key; PNODE p; PNODE pp;
            if(avlTree.find(key, p, pp)) {
                out << *p;
            } else {
                out << "Not found, available parent : " << *pp;
            }
        } else if(cmd == "showTree") {
            avlTree.showTree(out);
            out << endl;
        } else if(cmd == "height") {
            out << "Height of AVL : " << findHeight<K, V>(avlTree.root);
            out << endl;
        } else if(cmd == "findNearest") {
            PNODE ptr = findNearestLeaf(avlTree.root);
            if(ptr == nullptr) {out << "Error" << endl;}
            out << *ptr << endl;
        } else {
            out << "Wrong command" << endl;
        }
    }
}

int main() {
    avlCmd<int, string>(std::cin, std::cout);
    return 0;
}
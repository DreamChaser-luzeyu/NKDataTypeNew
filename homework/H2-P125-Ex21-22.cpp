#include <iostream>
#include <string>
#include "../LinearList/DoublyLinkedList.cpp"
using std::cin;
using std::cout;
using std::endl;
using std::string;

/*
考虑到带头节点的双向循环链表相比于普通双向链表性能优势仅仅体现在
indexOf()函数上，为提高代码的可复用性，其他功能仍按照普通双向链
表实现。
基于此，我添加了indexOfCirculatedWithHead()成员函数，但在本题
中并未使用。
../test/DoublyLinkedListTest.cpp文件演示了indexOfCirculatedWithHead()
函数的使用。
*/

template<class T>
class ExtendedDoublyChain : public DoublyChainList<T> {
public:
    void split(ExtendedDoublyChain<T>& a, ExtendedDoublyChain<T>& b);
    void split_no_extra_mem(ExtendedDoublyChain<T>& a, ExtendedDoublyChain<T>& b);
};

template <class T>
void ExtendedDoublyChain<T>::split(ExtendedDoublyChain<T>& a, ExtendedDoublyChain<T>& b) {
    int index_a = 0;
    int index_b = 0;
    for(int i=0; i<this->listSize; i++){
        if(i%2 == 0){
            b.insert(index_b, this->get(i));
            index_b ++;
        } else {
            a.insert(index_a, this->get(i));
            index_a ++;
        }
    }
}

template <class T>
void ExtendedDoublyChain<T>::split_no_extra_mem(ExtendedDoublyChain<T>& a, ExtendedDoublyChain<T>& b) {
    int index_a = 0;
    int index_b = 0;
    int times = this->listSize;
    for(int i=0; i<times; i++){
        DoublyChainNode<T>* srcNode = this->firstNode;
        this->firstNode = this->firstNode->next;
        this->listSize --;
        if(i%2 == 0){
            b.insertNode(index_b, srcNode);
            if(this->firstNode != nullptr) {
                this->firstNode->previous = nullptr;
            }
            index_b ++;
        } else {
            a.insertNode(index_a, srcNode);
            if(this->firstNode != nullptr) {
                this->firstNode->previous = nullptr;
            }
            index_a ++;
        }
    }
    this->lastNode = nullptr;
}

int main() {
    ExtendedDoublyChain<string> src, a, b;
    src.insert(0, "str0"); src.insert(1, "str1");
    src.insert(2, "str2"); src.insert(3, "str3");
    src.insert(4, "str4"); src.insert(5, "str5");
    
    src.split(a, b);
    a.output(cout);
    b.output(cout);
    src.output(cout);
    // int p; cin >> p;
    system("pause");
    return 0;
}
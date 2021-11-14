#ifndef _HEAPARRAYREP_H
#define _HEAPARRAYREP_H
#include <vector>
#include <iostream>

using std::vector;
using std::cin;
using std::cout;
using std::endl;
using std::ostream;

template <class T>
void mySwap(T& a, T& b) {
    T t;
    t = a; a = b; b = t;    
}




template <class T>
class MyMaxHeap {
public:
    MyMaxHeap(const vector<T>& src);
    void insert(const T& elem);
    void erase(const T& elem);
    T* sort();                  // 升序
    T* sort(int);               // 降序
    void buildHeap();
    void outputArray(ostream& out);
private:
    // void buildMaxHeap();
    // void buildMinHeap();
    int getParentIndex(int nodeIndex) const;
    int getChildIndex(int nodeIndex) const;         // left child index
    int getFirstLeafNodeIndex() const;
    bool isMaxHeap(int beginIndex) const;
    // int sinkElem(int nodeIndex);                    // returns the dst index, if swapped
                                                    // only swap once
    int getMaxChildIndex(int parentIndex) const;           // returns the reference of the larger child
    // int indexNow = 0;
    vector<T> data;
};

template <class T>
void MyMaxHeap<T>::insert(const T& elem) {          // 复杂度：O(log n), O(height)
    int indexNow = data.size();
    data.push_back(elem);
    if(indexNow == 0) {                             // 插入根节点时无需比较
        return;
    }
    int parentIndex = getParentIndex(indexNow);     // 获取父节点下标
    while(data.at(indexNow) > data.at(parentIndex)) {   // 比父节点大就循环
        mySwap(data[indexNow], data[parentIndex]);  //跟父节点交换
        indexNow = parentIndex;                     // 更新当前下标
        if(indexNow == 0) {break;}                  // 已经到了根节点，不能再上了
        parentIndex = getParentIndex(indexNow);     // 更新父节点下标
    }
}

template <class T>
MyMaxHeap<T>::MyMaxHeap(const vector<T>& src) {
    data = src;
}

template <class T>
void MyMaxHeap<T>::buildHeap() {                    // O(n)
    int beginIndex = getFirstLeafNodeIndex() - 1;   // 从最后一个非叶子节点（从左往右数）开始遍历
    for(int indexNow = beginIndex; indexNow >= 0; indexNow --) { // 当前下标为indexNow
        int judgeIndex = indexNow;                  // judgeIndex是要判断的下标
        // T temp = data[judgeIndex];
        while(!isMaxHeap(judgeIndex)) {             // 判断judgeIndex的【元子树】是否满足最大堆
            int dstIndex = getMaxChildIndex(judgeIndex);    // dstIndex是要交换到的目标下标
            mySwap(data[judgeIndex], data[dstIndex]);       // 交换到目标下标
            judgeIndex = dstIndex;                          // 更新需要判断的位置
        }
    }
}

bool isMaxHeap

// 过度解耦，无法优化
// template <class T>
// void MyMaxHeap<T>::buildHeap() {                    // O(n)
//     int beginIndex = getFirstLeafNodeIndex() - 1;   // 从最后一个非叶子节点（从左往右数）开始遍历
//     for(int indexNow = beginIndex; indexNow >= 0; indexNow --) { // 当前下标为indexNow
//         int judgeIndex = indexNow;                  // judgeIndex是要判断的下标
//         T temp = data[judgeIndex];                  // 先保存当前节点
//         while(!isMaxHeap(judgeIndex)) {             // 判断judgeIndex的【元子树】是否满足最大堆
//             int dstIndex = getMaxChildIndex(judgeIndex);    // dstIndex是要交换到的目标下标
//             // mySwap(data[judgeIndex], data[dstIndex]);       // 交换到目标下标
//             data[judgeIndex] = data[dstIndex];              // 把最大的子节点赋值给父亲节点
//             judgeIndex = dstIndex;                          // 更新需要判断的位置
//         }
//         data[judgeIndex] = temp;//
//     }
// }

template <class T>
void MyMaxHeap<T>::outputArray(ostream& out) {// 这是一个输出函数，可以输出数组的内容
    out << "Array : ";
    for(int i=0; i<(int)data.size(); i++) {
        out << data.at(i) << " ";
    }
    out << endl;
}


template <class T>
void MyMaxHeap<T>::erase(const T& elem) {

}

template <class T>
int MyMaxHeap<T>::getParentIndex(int nodeIndex) const {// 获取父节点下标
    if(nodeIndex < 0) {
        throw "getParentIndex() : Invalid index";
    }
    if(nodeIndex == 0) {
        throw "getParentIndex() : No parent : root node";
    }
    return (nodeIndex+1)/2 - 1;
}

template <class T>
int MyMaxHeap<T>::getChildIndex(int nodeIndex) const {// 获取左子节点下标
    if(nodeIndex >= getFirstLeafNodeIndex()) {
        throw "getChildIndex : Do not have child : leaf node";
    }
    if(nodeIndex < 0) {
        throw "getChildIndex : Invalid index";
    }
    return 2*nodeIndex + 1;    
}

template <class T>
int MyMaxHeap<T>::getFirstLeafNodeIndex() const {// 获取从前往后第一个叶子节点的下标
    int size = data.size();
    return (size+1) / 2;
}

template <class T>
bool MyMaxHeap<T>::isMaxHeap(int beginIndex) const {// 判断beginIndex的【元子树】是否满足最大堆
    if(beginIndex >= getFirstLeafNodeIndex()) {return true;}
    T maxChild = data.at(getMaxChildIndex(beginIndex));
    T elemNow = data.at(beginIndex);
    if(elemNow >= maxChild) {return true;}
    return false;
}

template <class T>
int MyMaxHeap<T>::getMaxChildIndex(int parentIndex) const {// 获取beginIndex的最大子节点下标
    int maxIndex = data.size() - 1;
    int leftChildIndex = getChildIndex(parentIndex) <= maxIndex ? 
                         getChildIndex(parentIndex) : -1;
    int rightChildIndex = leftChildIndex+1 <= maxIndex ? 
                          leftChildIndex+1 : -1;
    if(leftChildIndex == -1) {
        throw "getMaxChildIndex() : No child : leaf node";
    }
    if(rightChildIndex == -1) {
        return leftChildIndex;
    }
    const T& leftChild = data[leftChildIndex];
    const T& rightChild = data[rightChildIndex];
    return leftChild > rightChild ? leftChildIndex : rightChildIndex;
}

#endif
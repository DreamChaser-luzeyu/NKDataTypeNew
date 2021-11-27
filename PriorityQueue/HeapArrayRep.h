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
    void push(const T& elem);
    void pop();
    T* sort();                  // 升序
    T* sort(int);               // 降序
    void buildHeap();
    void buildHeapOptimized(int sortedNum);
    void outputArray(ostream& out);
private:
    // void buildMaxHeap();
    // void buildMinHeap();
    int getParentIndex(int nodeIndex) const;
    int getChildIndex(int nodeIndex) const;         // left child index
    int getFirstLeafNodeIndex() const;
    int getFirstLeafNodeIndex(int n) const;
    bool isMaxHeap(int beginIndex) const;
    bool isMaxHeap(int beginIndex, const T& temp) const;
    // int sinkElem(int nodeIndex);                    // returns the dst index, if swapped
                                                    // only swap once
    int getMaxChildIndex(int parentIndex) const;           // returns the reference of the larger child
    // int indexNow = 0;
    vector<T> data;
};

template <class T>
void MyMaxHeap<T>::push(const T& elem) {          // 复杂度：O(log n), O(height)
    data.push_back(elem);
    int indexNow = data.size() - 1;               // 当前下标为新push_back的元素所在下标
    T temp = data[indexNow];
    int parentIndex = getParentIndex(indexNow);   // 获取父节点下标
    while(temp > data.at(parentIndex)) {          // 比父节点大就循环
                                                  // 进行「上浮」操作，即找到满足要求的目标下标  
        data[indexNow] = data[parentIndex];
        indexNow = getParentIndex(indexNow);
        parentIndex = getParentIndex(indexNow);
        if(indexNow == 0) {break;}
    }
    data[indexNow] = temp;
}

template <class T>
void MyMaxHeap<T>::pop() {
    int lastElemIndex = this->validSize;
    int indexNow;
    T temp = data[lastElemIndex];               // 保存最后一个节点        
    data[lastElemIndex] = data[1];              // 把根节点赋值给最后一个节点
    validSize --;                               // 此时最后一个节点已经不属于这个堆了
    // data[1] = temp;                             // 把最后一个节点写到根节点（其实就是根节点与最后一个节点交换）
    for(indexNow = 1; !isMaxHeap(indexNow, temp);) {
        int maxChildIndex = getMaxChildIndex(indexNow);
        data[indexNow] = data[maxChildIndex];
        indexNow = maxChildIndex;
    }
                                                // 一旦以最后一个元素为根节点的「元子树」满足最大堆，就跳出循环
                                                // 循环结束后，以indexNow为下标，以temp为值的「元子树」满足最大堆
    data[indexNow] = temp;                      // 找到「下沉」操作的目标位置，放入原最后一个节点
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

template <class T>
void MyMaxHeap<T>::buildHeapOptimized(int sortedNum) {
    int beginIndex = getFirstLeafNodeIndex(sortedNum) - 1;   // 从最后一个非叶子节点（从左往右数）开始遍历
    // bool flag = false;                                       // 是否已经存储临时变量
    for(int indexNow = beginIndex; indexNow >= 0; indexNow --) { // 当前下标为indexNow
        int dstIndex = indexNow;   
        T temp = data[dstIndex];                // 存储首先被覆盖的元素
        while(!isMaxHeap(dstIndex, temp)) {               // 判断以temp为根节点的【元子树】是否满足最大堆
            int srcIndex = getMaxChildIndex(dstIndex);    // 获取dstIndex对应的最大子节点下标
            data[dstIndex] = data[srcIndex];              // 把最大孩子覆盖给dstIndex
            dstIndex = srcIndex;                          // 更新需要判断的位置
        }
        data[dstIndex] = temp;                            // 把临时变量赋值给最终位置 
    }
}

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
    return size / 2;
}

template <class T>
int MyMaxHeap<T>::getFirstLeafNodeIndex(int n) const {// 获取从前往后第一个叶子节点的下标
                                                      // 已经删去最后一个元素
    int size = data.size() - n;
    return size / 2;
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
bool MyMaxHeap<T>::isMaxHeap(int beginIndex, const T& temp) const {// 判断beginIndex的【元子树】是否满足最大堆
    if(beginIndex >= getFirstLeafNodeIndex()) {return true;}
    T maxChild = data.at(getMaxChildIndex(beginIndex));
    if(temp >= maxChild) {return true;}
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
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
    MyMaxHeap(const vector<T>& src, const T& maxElem, const T& minElem);
    void push(const T& elem);
    void pop();
    T popRemove();
    T* sort();                  // 升序
    T* sort(int);               // 降序
    void buildHeapOptimized(int sortedNum);
    void outputArray(ostream& out);
private:
    int getParentIndex(int nodeIndex) const;
    int getChildIndex(int nodeIndex) const;         // left child index
    int getFirstLeafNodeIndex() const;
    int getFirstLeafNodeIndex(int n) const;
    bool isMaxHeap(int beginIndex) const;
    bool isMaxHeap(int beginIndex, const T& temp) const;
    int getMaxChildIndex(int parentIndex) const;           // returns the reference of the larger child
    vector<T> data;
    int validSize;
    T maxElem;
    T minElem;
    int sortedNum = 0;
};

template <class T>                                // 从下往上走
void MyMaxHeap<T>::push(const T& elem) {          // 复杂度：O(log n), O(height)
    data[validSize + 1] = elem;
    data.push_back(minElem);
    data.push_back(minElem);
    validSize ++;
    int indexNow = validSize;
    T temp = data[indexNow];
    int parentIndex = getParentIndex(indexNow);     // 获取父节点下标
    while(temp > data.at(parentIndex)) {            // 比父节点大就循环
        data[indexNow] = data[parentIndex];
        indexNow = getParentIndex(indexNow);
        parentIndex = getParentIndex(indexNow);
        // if(indexNow == 0) {break;}               // 因为有了maxElem作为根节点，所以无需判断
    }
    data[indexNow] = temp;
    
}

template <class T>
void MyMaxHeap<T>::pop() {                      // O(log n)
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
    sortedNum ++;
    
}

template <class T>
T MyMaxHeap<T>::popRemove() {                         // O(log n)
    int lastElemIndex = this->validSize;
    // std::cout << "lastElemIndex : " << lastElemIndex;
    int indexNow;
    T temp = data[lastElemIndex];               // 保存最后一个节点
    T returnVal = data[1];                      // 保存要返回的元素  
    data[lastElemIndex] = this->minElem;        // 把最后一个节点抹掉
    validSize --;                               // 此时最后一个节点已经不存在了
    for(indexNow = 1; !isMaxHeap(indexNow, temp);) {
        int maxChildIndex = getMaxChildIndex(indexNow);
        data[indexNow] = data[maxChildIndex];
        indexNow = maxChildIndex;
    }
                                                // 一旦以最后一个元素为根节点的「元子树」满足最大堆，就跳出循环
                                                // 循环结束后，以indexNow为下标，以temp为值的「元子树」满足最大堆
    data[indexNow] = temp;                      // 找到「下沉」操作的目标位置，放入原最后一个节点
    data.resize(data.size() - 2);
    if(validSize == 0) {data[1] = this->minElem;}
    return returnVal;
}


template <class T>
MyMaxHeap<T>::MyMaxHeap(const vector<T>& src, const T& maxElem, const T& minElem) {
    data.resize(2 * src.size() + 2);
    data[0] = maxElem;
    int indexNow = 0;
    for(; indexNow<=src.size(); indexNow++) {
        data[indexNow + 1] = src[indexNow];
    }
    for(; indexNow<data.size(); indexNow++) {
        data[indexNow] = minElem;
    }
    validSize = src.size();
    this->maxElem = maxElem;
    this->minElem = minElem;
}

template <class T>
void MyMaxHeap<T>::buildHeapOptimized(int sortedNum) {    // 从后往前遍历，从上往下走
    // std::cout << getFirstLeafNodeIndex(sortedNum) - 1;
    int beginIndex = getFirstLeafNodeIndex(sortedNum) - 1;   // 从最后一个非叶子节点（从左往右数）开始遍历
    // bool flag = false;                                       // 是否已经存储临时变量
    for(int indexNow = beginIndex; indexNow >= 1; indexNow --) { // 当前下标为indexNow
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


// template <class T>
// void MyMaxHeap<T>::erase(const T& elem) {

// }

template <class T>
int MyMaxHeap<T>::getParentIndex(int nodeIndex) const {// 获取父节点下标
    // if(nodeIndex < 0) {
    //     throw "getParentIndex() : Invalid index";
    // }
    // if(nodeIndex == 0) {
    //     throw "getParentIndex() : No parent : root node";
    // } // impossible within [1:n]
    return nodeIndex / 2;
}

template <class T>
int MyMaxHeap<T>::getChildIndex(int nodeIndex) const {// 获取左子节点下标
    // if(nodeIndex >= getFirstLeafNodeIndex()) {
    //     throw "getChildIndex : Do not have child : leaf node";
    // }
    // if(nodeIndex < 0) {
    //     throw "getChildIndex : Invalid index";
    // } // impossible within [1:n]
    return 2*nodeIndex;    
}

template <class T>
int MyMaxHeap<T>::getFirstLeafNodeIndex() const {// 获取从前往后第一个叶子节点的下标
    int size = validSize;
    return size / 2 + 1;
}

template <class T>
int MyMaxHeap<T>::getFirstLeafNodeIndex(int n) const {// 获取从前往后第一个叶子节点的下标
                                                      // 已经删去最后一个元素
    int size = validSize - n;
    return size / 2 + 1;
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
    // std::cout << "First leaf index : " << getFirstLeafNodeIndex();
    if(beginIndex >= getFirstLeafNodeIndex()) {return true;}
    T maxChild = data.at(getMaxChildIndex(beginIndex));
    if(temp >= maxChild) {return true;}
    return false;
}

template <class T>
int MyMaxHeap<T>::getMaxChildIndex(int parentIndex) const {// 获取beginIndex的最大子节点下标
    int maxIndex = validSize;
    int leftChildIndex = getChildIndex(parentIndex) <= maxIndex ? 
                         getChildIndex(parentIndex) : -1;
    int rightChildIndex = leftChildIndex+1 <= maxIndex ? 
                          leftChildIndex+1 : -1;
    if(leftChildIndex == -1) {
        throw "getMaxChildIndex() : No child : leaf node";
    } // impossible
    if(rightChildIndex == -1) {
        return leftChildIndex;
    } // still impossible
      // possible when pop
    const T& leftChild = data[leftChildIndex];
    const T& rightChild = data[rightChildIndex];
    return leftChild > rightChild ? leftChildIndex : rightChildIndex;
}

#endif
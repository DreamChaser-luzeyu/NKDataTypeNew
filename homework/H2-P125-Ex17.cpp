#include <iostream>
#include <string>
#include "../LinearList/LinerListChainRep.cpp"
using std::cin;
using std::cout;
using std::endl;

template<class T>
class ExtendedChain : public ChainList<T>{
public:
    // 未显式调用父类构造函数，默认调用父类的无参构造函数
    void clear();
    void push_back(const T& theElement);
protected:
    //ChainNode<T>* firstNode;
    //int listSize;
};

template<class T>
void ExtendedChain<T>::push_back(const T& theElement){
    ChainNode<T>* newNode = new ChainNode<T>(theElement, nullptr);
    if(this->firstNode == nullptr){
        this->firstNode = newNode;
    }
    else{
        ChainNode<T>* p = this->firstNode;
        while(p->next != nullptr){
            p = p->next;
        }
        p->next = newNode;
    }
    this->listSize ++;
}

template<class T>
ExtendedChain<T> meld(ExtendedChain<T> a, ExtendedChain<T> b){
    ExtendedChain<T> c;
    int srcIndex = 0;
    int dstIndex = 0;
    while((srcIndex < a.size()) && (srcIndex < b.size())){
        c.insert(dstIndex, a.get(srcIndex));
        dstIndex ++;
        c.insert(dstIndex, b.get(srcIndex));
        dstIndex ++;
        srcIndex ++;
    }
    while(srcIndex < a.size()){
        c.insert(dstIndex, a.get(srcIndex));
        srcIndex ++;
        dstIndex ++;
    }
    while(srcIndex < b.size()){
        c.insert(dstIndex, b.get(srcIndex));
        srcIndex ++;
        dstIndex ++;
    }
    return c;
}


int main(){
    ExtendedChain<std::string> a,b;
    // manually prepare data
    a.insert(0,"a,node0");a.insert(1,"a,node1");a.insert(2,"a,node2");a.insert(3,"a,node3");
    b.insert(0,"b,node0");b.insert(1,"b,node1");b.insert(2,"b,node2");// b.insert(3,"b,node3");
    
    a.output(cout);
    cout << endl;
    b.output(cout);
    cout << endl;
    meld(a, b).output(cout);
    
    cout <<"done";
    system("pause");
    return 0;
}

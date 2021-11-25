#include <iostream>
#include <vector>
#include "../PriorityQueue/HeapArrayRep.h"



using std::cin;
using std::cout;
using std::istream;
using std::ostream;
using std::endl;
using std::vector;

void inputArray(istream& in, vector<int>& arr) { 
    int inputBuffer;
    while(in >> inputBuffer) {
        arr.push_back(inputBuffer);
        if(in.get() == '\n') {break;}
    }
}


int main() {
    vector<int> arr;
    inputArray(cin, arr);
    MyMaxHeap<int> mHeap(arr);
    try{
        mHeap.buildHeap();
    } catch(const char* str) {
        cout << str << endl;
        system("pause");
    }
    mHeap.outputArray(cout);
    int newElem; cin >> newElem;
    try{
        mHeap.insert(newElem);
    } catch(const char* str) {
        cout << str << endl;
        system("pause");
    }
    mHeap.outputArray(cout);
    system("pause");
    return 0;
}


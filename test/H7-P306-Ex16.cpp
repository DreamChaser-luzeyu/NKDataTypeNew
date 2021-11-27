#include <iostream>
#include <vector>
#include <string>
#include <limits.h>
#include "../PriorityQueue/MinHeapArrayRepWithMaxElem.h"

using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::vector;
using std::istream;
using std::ostream;

void inputArray(istream& in, vector<int>& arr) { 
    int inputBuffer;
    while(in >> inputBuffer) {
        arr.push_back(inputBuffer);
        if(in.get() == '\n') {break;}
    }
}

void runCmd(istream& in, ostream& out, MyMinHeap<int>& mHeap) {
    out << "pop\tpush [elem]\tbuild\tpopRemove\toutput\n";
    while(true) {
        string cmd; cin >> cmd;
        if(cmd == "pop") {mHeap.pop();}
        else if(cmd == "popRemove") {out << "Poped elem : " << mHeap.popRemove() << endl;}
        else if(cmd == "push") {int elem; in >> elem; mHeap.push(elem);}
        else if(cmd == "output") {mHeap.outputArray(out); out << endl;}
        else if(cmd == "build") {mHeap.buildHeapOptimized(0);}
        else {out << "Wrong input" << endl;}
    } 
}


int main() {
    vector<int> arr;
    inputArray(cin, arr);
    MyMinHeap<int> mHeap(arr, INT32_MAX, INT32_MIN);
    runCmd(cin, cout, mHeap);
    system("pause");
    return 0;
}
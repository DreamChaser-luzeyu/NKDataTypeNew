#include <iostream>
#include <string>
#include "../LinearList/DoublyLinkedList.cpp"
using std::cin;
using std::cout;
using std::endl;
using std::string;

int main(){
    DoublyChainList<string> aList(0);
    while(true){
        cout << "选择操作：" << endl
             << "1.插入     insert [theIndex] [theElement]" << endl
             << "2.取出     get [theIndex]" << endl
             << "3.查找下标 indexOf [theElement]" << endl
             << "4.删除     erase [theIndex]" << endl
             << "5.插入     insert [theIndex] [theElement]" << endl
             << "6.输出     output / outputRev" << endl
             << "7.插入节点 insertNode [theIndex]" << endl
             << "8.查找下标（循环方式） indexOfC [theElement]" << endl;
        string method; cin >> method;
        if(method == "insert") {
            int theIndex; cin >> theIndex;
            string theElement; cin >> theElement;
            aList.insert(theIndex, theElement);
        } else if (method == "get") {
            int theIndex; cin >> theIndex;
            cout << aList.get(theIndex) << endl;
        } else if (method == "indexOf") {
            string theElement; cin >> theElement;
            cout << "theIndex: " << aList.indexOf(theElement) << endl;
        } else if (method == "erase") {
            int theIndex; cin >> theIndex;
            aList.erase(theIndex);
        } else if (method == "insert") {
            int theIndex; cin >> theIndex;
            string theElement; cin >> theElement;
        } else if (method == "output") {
            aList.output(cout);
        } else if (method == "outputRev") {
            aList.outputRev(cout);
        } else if (method == "insertNode") {
            int theIndex; cin >> theIndex;
            aList.insertNode(theIndex, new DoublyChainNode<string>("newNode"));
        } else if (method == "indexOfC") {
            string theElement; cin >> theElement;
            aList.circulateWithHead();
            cout << "theIndex: " << aList.indexOfCirculatedWithHead(theElement) << endl;
            aList.deCirculateWithHead();
        } else {
            cout << "Wrong input" << endl;
        }

    }


}
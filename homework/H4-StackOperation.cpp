#include <iostream>
#include <fstream>
#include "../StackAndQueue/linkedstack.h"

using std::istream;
using std::cin;
using std::ostream;
using std::cout;
using std::endl;

template <class T>
void delete_all(linkedStack<T>& s, const T& x) {
    linkedStack<T> tmpStack;
    while(!s.empty()) {
        tmpStack.push(s.top());
        s.pop();
    }
    while(!tmpStack.empty()) {
        T top = tmpStack.top();
        if(top != x){
            s.push(tmpStack.top());
        }
        tmpStack.pop();
    }
}

template <class T>
void getDstElem(istream& is, T& dstElem) {
    is >> dstElem;
}

template <class T>
void pushData(istream& is, linkedStack<T>& stack) {
    T inputBuffer;
    while(is >> inputBuffer) {      // 遇到EOF时，operator>>(istream&, T) 自动返回0，跳出循环
        stack.push(inputBuffer);
        if(is.get() == '\n') {break;}
        // if(is.eof()) {break;}    // never reached
    }
}

template <class T>
void outputAndPop(ostream& out, linkedStack<T>& s) {
    out << "[stackTop] ";
    while(!s.empty()) {
        out << s.top() << " ";
        s.pop();
    }
    out << "[stackButtom]" << endl;
}

int main() {
    fstream inputFile;
    inputFile.open("D:/Learning/datatype/input/H4-StackOperation.txt");

    linkedStack<char> s;
    char dstElem;
    getDstElem<char>(inputFile, dstElem);
    pushData<char>(inputFile, s);
    delete_all(s, dstElem);
    outputAndPop(cout, s);

    inputFile.close();

    system("pause");
    return 0;
}
#include <iostream>
#include <fstream>
#include <string>

using std::cin;
using std::cout;
using std::endl;
using std::istream;
using std::ostream;
using std::string;
using std::fstream;

class DoubleEndQueue {
public:
    DoubleEndQueue() {
        data = new int[10];
        size = 10;
    }
    DoubleEndQueue(int size) {
        data = new int[size];
        this->size = size;
    }

    bool isEmpty() const {
        return elemNum == 0;
    }

    bool isFull() const {
        return elemNum == size;
    }

    void addLeft(const int& t) {
        if(isFull()) {throw "Full queue !";}
        int dstIndex = getNextHeadIndex();
        data[dstIndex] = t;
        elemNum ++;
    }

    void addRight(const int& t) {
        if(isFull()) {throw "Full queue !";}
        int dstIndex = getNextTailIndex();
        data[dstIndex] = t;    
        elemNum ++;
    }

    void deleteLeft() {
        if(isEmpty()) {throw "Empty";}
        nextHeadIndex ++;
        if(nextHeadIndex == size) {nextHeadIndex = 0;}
        elemNum --;
    }

    void deleteRight() {
        if(isEmpty()) {throw "Empty";}
        nextTailIndex --;
        if(nextTailIndex < 0) {nextTailIndex = size-1;}
        elemNum --;
    }

    void printList(ostream& out) {
        // if(isEmpty()) {
        //     out << "Empty" << endl;
        //     return;
        // }
        int indexNow = nextHeadIndex + 1;
        for(int i=0; i<elemNum; i++) {
            if(indexNow == size) {indexNow = 0;}
            out << data[indexNow] << " ";
            indexNow ++;
        }
        out << endl;
    }

    int& getLeft() {
        if(isEmpty()) {throw "Empty queue !";}
        int index = nextHeadIndex + 1;
        if(index >= size) {index = 0;}
        return data[index];
    }

    int& getRight() {
        if(isEmpty()) {throw "Empty queue !";}
        int index = nextTailIndex - 1;
        if(index < 0) {index = size-1;}
        return data[index];
    }

    void printS(ostream& out) {
        for(int i=0; i<size; i++) {
            out << data[i] << " ";
        }
        out << endl;
        out << "NextHeadIndex : " << nextHeadIndex << endl;
        out << "NextTailIndex : " << nextTailIndex << endl;
    }

private:
    int getNextTailIndex() {
        int toReturn = nextTailIndex;
        nextTailIndex ++;
        if(nextTailIndex == size) {nextTailIndex = 0;}
        return toReturn;
    }

    int getNextHeadIndex() {
        int toReturn = nextHeadIndex;
        nextHeadIndex --;
        if(nextHeadIndex < 0) {nextHeadIndex = size-1;}
        return toReturn;
    }
    int* data;
    int size;
    int elemNum = 0;
    int nextTailIndex = 1;
    int nextHeadIndex = 0;
};

void inputCmd(istream& in, ostream& out, DoubleEndQueue& mQueue) {
    out << "Usage : " << endl
        << "AddLeft [elem] \t" << "AddRight [elem] \t"
        << "DeleteLeft \t" << "DeleteRight \t"  << endl
        << "IsEmpty \t" << "IsFull \t" 
        << "Left \t" << "Right \t" << endl
        << "End \t" << endl;
    while(true) {
        string cmd; in >> cmd;
        if(cmd == "AddLeft") {
            int t; in >> t;
            mQueue.addLeft(t);
            mQueue.printList(out);
        }
        if(cmd == "AddRight") {
            int t; in >> t;
            try{
                mQueue.addRight(t);
            } catch(const char* str) {
                out << str << endl;
            }
            mQueue.printList(out);
        }
        if(cmd == "DeleteLeft") {
            try{
                mQueue.deleteLeft();
            } catch(const char* str) {
                out << str << endl;
            }
            mQueue.printList(out);
        }
        if(cmd == "DeleteRight") {
            try{
                mQueue.deleteRight();
            } catch(const char* str) {
                out << str << endl;
            }
            mQueue.printList(out);
        }
        if(cmd == "IsEmpty") {
            bool flag = mQueue.isEmpty();
            if(flag) {out << "Is empty" << endl;}
            else {out << "Not empty" << endl;}
        }
        if(cmd == "IsFull") {
            bool flag = mQueue.isFull();
            if(flag) {out << "Is full" << endl;}
            else {out << "Not full" << endl;}
        }
        if(cmd == "Left") {
            try {
                out << mQueue.getLeft() << endl;
            } catch(const char* str) {
                out << str << endl;
            }
        }
        if(cmd == "Right") {
            try {
                out << mQueue.getRight() << endl;
            } catch(const char* str) {
                out << str << endl;
            }
        }
        if(cmd == "Debug") {
            mQueue.printS(out);
        }
        if(cmd == "End") {break;}
    }
}


int main() {
    fstream inputFile;
    inputFile.open("D:/Learning/datatype/input/H6-DoubleEndQueue.txt");
    DoubleEndQueue mQueue(5);
    inputCmd(inputFile, cout, mQueue);
    inputFile.close();
    system("pause");
    return 0;
}
#include <iostream>
#include <string>
#include <fstream>
#include "../LinearList/LinerListChainRep.cpp"

using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::fstream;

using std::istream;
using std::ostream;

class LoopList : public ChainList<int> {
public:
    LoopList(int n) : ChainList<int>(0) {
        for(int i=0; i<n; i++) {
            insert(i,i+1);                  // 插入人，和人的编号
        }
        ChainNode<int>* ptr = firstNode;
        for(int i=0; i<n-1; i++) {
            ptr = ptr->next;    // 找最后一个
        }
        ptr->next = firstNode;              // 成环
        loopNode = ptr;               // 开始时loopNode是尾节点
    }

    void delPerson() {
        if(loopNode == loopNode->next) {
            loopNode->next = nullptr;
            return;
        }
        loopNode->next = loopNode->next->next;
    }

    int& getLoop() {
        return loopNode->next->element;
    }

    void loop() {
        loopNode = loopNode->next;
    }

private:
    ChainNode<int>* loopNode;
};



int indexLoop(int size) {
    static int index;
    index ++;
    if(index == size+1) {index = 1;}
    return index;
}

void method_1(istream& in, ostream& out) {
    int numSay = 0;
    int outNum = 0;                       // 出队的人数
    string str1, str2;
    in >> str2 >> str1;
    int m, n;
    // m:出列的人数
    // n:起始的总人数

    // 异常处理
    try {
        m = stoi(str1);
        n = stoi(str2);
    } catch(std::invalid_argument&) {
        out << "Invalid num input" << endl;
    } 

    int* people = new int[n+1];
    for(int i=1; i<=n; i++) {people[i] = 1;} // 都有人
    while(true) {
        int i = indexLoop(n);               // 自动转圈下标
        if(people[i] == 1) {numSay ++;}     // 有人才报数
        if(numSay == m) {
            people[i] = 0;                  // 出列
            out << i << " ";                // 输出 出队人的编号
            outNum ++;                      // 统计人数+1
            numSay = 0;                     // 重新报数
        }
        if(outNum == n) {                   // 一个人都没有了
            break;
        }
    }
}

void method_2(istream& in, ostream& out) {
    int numSay = 0;
    int outNum = 0;                       // 出队的人数
    // ChainList<int> people(0);
    // people.insert(0, -1); // 头节点
    int m, n;
    // m:出列的序号
    // n:起始的总人数
    // 异常处理
    {
        string str1, str2;
        in >> str2 >> str1;
        // 异常处理
        try {
            m = stoi(str1);
            n = stoi(str2);
        } catch(std::invalid_argument&) {
            out << "Invalid num input" << endl;
        } 
    }
    
    //初始状态满人
    // for(int i=1; i<=n; i++) {people.insert(i, 1);}
    LoopList people(n);
    while(true) {
        numSay ++;                                  // 得到这次报的数

        if(outNum == n) {
            // people.firstNode = nullptr;
            break;
        }                    // 所有人都出去了
        
        if(numSay == m) {
            out << people.getLoop() << " ";         // 输出出局人的编号
            people.delPerson();
            outNum ++;
            numSay = 0;                             // 从头报
            continue;                               // 有人出局后不能执行loop()
                                                    // 若还执行，那loopNode就不指向报数的前一个人了
        }
        people.loop();                              // 人循环
    }
}



int main() {
    fstream inputFile;
    inputFile.open("D:/Learning/datatype/input/H4-Josephus.txt");

    fstream inputFile2;
    inputFile2.open("D:/Learning/datatype/input/H4-Josephus.txt");
    method_2(inputFile, cout);
    cout << endl;
    method_1(inputFile2, cout);
    cout << endl;
    inputFile.close();
    inputFile2.close();
    system("pause");
    return 0;
}
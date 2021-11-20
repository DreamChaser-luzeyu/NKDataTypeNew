#include <iostream>
#include <string>
#include <vector>
#include <stack>
#include <fstream>
#include "../BinTreeAndHeap/BinTree.h"

// using std::cin;
using std::cout;
using std::endl;
using std::istream;
using std::ostream;
using std::string;
using std::vector;
using std::stack;
using std::fstream;



int getPriority(char op) {
    switch (op) {
    case '+':
    case '-':
        return 1;
    case '*':
    case '/':
        return 2;
    case '^':
        return 3;
    default:
        return 0;
    }
}

bool isOperator(char ch) {
    return ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '^'
                     || ch == '(' || ch == ')';
}

bool isValidChar(char ch) {
    return ('0' <= ch && ch <= '9') || ('a' <= ch && ch <= 'z') || ('A' <= ch && ch <= 'Z') || isOperator(ch);
}

string infixToPostfix(string infix) {
    string postfix;
    stack<char> opStack;
    int len = infix.size();
    int flag = 0;                           // 未匹配左括号数量
    for(int i=0; i<len; i++) {
        char ch = infix.at(i);
        if(!isValidChar(ch)) {throw "Invalid character";}
        if(isOperator(ch)) {                // 是运算符
            if(ch == '(') {flag++;}    // 标注有左括号
            if(ch == ')' && flag <= 0) {throw "Invalid expression";}
                                            // 有右括号，没有左括号

            if(ch == ')') {                 // 弹出栈中左括号之上的符号
                while(opStack.top() != '(') {   // 直到遇到左括号
                    postfix.push_back(opStack.top());
                    opStack.pop();
                }
                opStack.pop();              // 弹出左括号
                flag --;                    // 未匹配数目-1
            }
            else if(ch == '(') {opStack.push(ch);}  // 左括号直接入栈 未匹配数目+1(前面)
            else if(opStack.empty() || getPriority(opStack.top()) < getPriority(ch)) {   // 当前优先级高
                opStack.push(ch);
            } else {                        // 栈顶优先级高或等于
                char topOp = opStack.top();
                opStack.pop();
                postfix.push_back(topOp);
                opStack.push(ch);
            }
        } else {
            postfix.push_back(ch);
        }
    }
    while(!opStack.empty()) {
        char ch = opStack.top();
        postfix.push_back(ch);
        opStack.pop();
    }
    if(flag > 0) {throw "Invalid expression";}
    return postfix;
}


int main() {
    fstream cin; cin.open("D:/Learning/datatype/input/H6-BuildAndPrintBinTree.txt");


    string infix = "a+b*(c/d+e)"; cin >> infix;
    cout << endl;
    string postfix;
    try{
        postfix = infixToPostfix(infix);                // 中缀转后缀
    } catch (const char* str) {cout << str;}
    cout << postfix;                                    // 输出后缀
    BinTree<char> tree;
    tree.buildTreeFromPostfix(postfix);          // 通过后缀来建树
    cout << endl << tree.getPostfixExpression(tree.root);   // 遍历方式输出后缀表达式，检验二叉树是否正确
    tree.showTree(tree.root, cout, 0);                  // 右子树->当前节点->左子树顺序遍历二叉树
    cout << endl;

    cin.close();
    system("pause");
    return 0;
}
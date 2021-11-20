#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include "../BinTreeAndHeap/BinTree.h"

using std::cin;
using std::cout;
using std::endl;
using std::fstream;
using std::vector;
using std::string;


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


// generated by copilot
// 能不能实现呢
// prefix to postfix
string prefixToPostfix(string prefix) {
    string postfix;
    stack<char> opStack;
    int len = prefix.size();
    for(int i=0; i<len; i++) {
        char ch = prefix.at(i);
        if(!isValidChar(ch)) {throw "Invalid character";}
        if(isOperator(ch)) {                // 是运算符
            if(ch == '(') {opStack.push(ch);}  // 左括号直接入栈
            else if(ch == ')') {
                while(opStack.top() != '(') {   // 直到遇到左括号
                    postfix.push_back(opStack.top());
                    opStack.pop();
                }
                opStack.pop();              // 弹出左括号
            }
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
    return postfix;
}

// 前缀表达式转中缀表达式
string prefixToInfix(string prefix) {
    int len = prefix.size();
    string infix;
    stack<char> opStack;
    stack<char> numStack;
    for(int i=len-1; i>=0; i--) {
        char ch = prefix.at(i);
        if(!isValidChar(ch)) {throw "Invalid character";}
        if(isOperator(ch)) {
            char num1 = numStack.top();
            numStack.pop();
            char num2 = numStack.top();
            numStack.pop();
            
        }
        else {
            numStack.push(ch);
        }
    
    return "";
}



// nodenum - 1, swapSubTree - 2, traversalByLevel - 3, width - 4
void runCmd(BinTree<char>& tree, istream& in, ostream& out) {
    int cmd;
    while(true) {
        out << "Please input the command number: " << endl;
        out << "1 - 输出二叉树的叶子节点个数" << endl
            << "2 - 输出二叉树的宽度" << endl
            << "3 - 层序遍历二叉树" << endl
            << "4 - 交换二叉树的两个子树" << endl
            << "5 - 打印二叉树" << endl;

        in >> cmd;
        switch (cmd){
            case 1:
                out << tree.getLeafNum() << endl;
                break;
            case 2:
                out << tree.getWidth() << endl;
                break;
            case 3:
                out << tree.getLevelOrderExpression() << endl;
                break;
            case 4:
                tree.swapSubTree(tree.root);
                break;
            case 5:
                tree.showTree(tree.root, out, 0);
                out << endl;
                break;
            default:
                out << "Wrong command!" << endl;
                break;
        }
    }
}

// 1 - build tree from postfix expression
// 2 - build tree from infix expression
// 3 - build tree from prefix expression
// 4 - build tree from array
void buildTree(BinTree<char>& tree, istream& in, ostream& out) {
    while(true) {
        out << "Please input the command number: " << endl;
        out << "1 - build tree from postfix expression" << endl
            << "2 - build tree from infix expression" << endl
            << "3 - build tree from prefix expression" << endl
            << "4 - build tree from array" << endl
            << "5 - continue program" << endl;

        int cmd;
        in >> cmd;
        switch(cmd) {
            case 1:{
                string postfix;
                out << "Please input the postfix expression: " << endl;
                in >> postfix;
                tree.buildTreeFromPostfix(postfix);
                break;}
            case 2:{
                string infix;
                out << "Please input the infix expression: " << endl;
                in >> infix;
                tree.buildTreeFromPostfix(infixToPostfix(infix));
                break;}
            case 3:{
                string prefix;
                out << "Please input the prefix expression: " << endl;
                in >> prefix;
                // out << prefixToPostfix(prefix);
                out << prefixToInfix(prefix);
                system("pause");
                tree.buildTreeFromPostfix(infixToPostfix(prefixToInfix(prefix)));
                break;}
            case 4: {
                vector<char> array;
                out << "Please input the array: " << endl;
                char c;
                while(in >> c) {
                    array.push_back(c);
                    if(in.get() == '\n') {break;}
                }
                tree.buildTreeFromArray(array);
                break;}
            case 5:{
                return;}
            default:{
                out << "Wrong command!" << endl;
                break;}
        }
    }
            
}

int main() {
    BinTree<char> tree;
    buildTree(tree, cin, cout);
    runCmd(tree, cin, cout);
    system("pause");
    return 0;
}
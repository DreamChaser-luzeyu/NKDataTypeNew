#include <iostream>
#include <vector>
#include <string>
#include "../BinTreeAndHeap/BinTree.h"

using std::cin;
using std::cout;
using std::vector;
using std::string;
using std::endl;

int main() {
    BinTree<char> tree;
    tree.root = buildTreeFromPostfix("abcd/e+*+");
    cout << tree.getPostfixExpression(tree.root);
    system("pause");
    return 0;
}
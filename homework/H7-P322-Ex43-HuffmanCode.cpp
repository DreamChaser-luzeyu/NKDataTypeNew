#include <iostream>
#include <vector>
#include <string>
#include <list>
#include <map>
#include "../PriorityQueue/HuffmanTree.h"

using std::istream;
using std::ostream;
using std::endl;
using std::vector;
using std::string;
using std::list;
using std::map;

/*
测试样例
 As we had had a long walk through one of the markets of old Delhi, we stopped at a square to have a rest. After a time, we noticed a snake charmer with two large baskets at the other side of the square, so we went to have a look at him. As soon as he saw us, he picked up a long pipe which was covered with coins and opened one of the baskets. When he began to play a tune, we had our first glimpse of the snake. It rose out of the basket and began to follow the movements of the pipe. We were very much surprised when the snake charmer suddenly began to play jazz and modern pop songs. The snake, however, continued to 'dance' slowly. It obviously could not tell the difference between Indian music and jazz!
*/


template<class T>
void inputNodeArr(istream& in, list<TreeNode<T>* >& arr) {
    while(true) {
        int weight; T val;
        in >> val >> weight;
        TreeNode<T>* ptr = new TreeNode<T>;
        ptr->weight = weight;
        ptr->val = val;
        arr.push_back(ptr);
        if(in.get() == '\n') {break;}
    }
}

void inputText(istream& is, vector<string>& arr) {
    string str;
    while(is >> str) {
        arr.push_back(str);
        if(is.get() == '\n') {break;}
    }
}

void countWeight(const vector<string>& text, list<TreeNode<string>* >& arr) {
    map<string, int> freqMap;
    for(string str : text) {
        freqMap[str] ++;
    }
    for(std::pair<string, int> p : freqMap) {
        TreeNode<string>* node = new TreeNode<string>;
        node->val = p.first;
        node->weight = p.second;
        arr.push_back(node);
        std::cout << "<" << node->val << "," << node->weight << ">" << endl;
    }
}


int main() {
    vector<string> text;
    inputText(std::cin, text);

    list<TreeNode<string>* > arr;           // 统计词频
    countWeight(text, arr);

    // inputNodeArr(std::cin, arr);
    HuffmanTree<string> huffmanTree;
    huffmanTree.buildTree(arr, "null");             // 创建哈夫曼树

    std::cout << "Tree : " << endl;
    huffmanTree.showTree(huffmanTree.root, std::cout, 0);
    huffmanTree.buildDic();

    std::cout << "Dic : " << endl;
    huffmanTree.showDic(std::cout);
    
    std::cout << "BinCode : " << endl;
    string binCode = huffmanTree.encode(text);
    std::cout << endl << binCode << endl;

    std::cout << "Decode result : " << endl;
    vector<string> textDecode;
    huffmanTree.decode(binCode, textDecode);
    for(string str : textDecode) {
        std::cout << str << " ";
    }
    std::cout << endl;

    return 0;
}
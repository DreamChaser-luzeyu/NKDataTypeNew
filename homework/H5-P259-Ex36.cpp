#include <iostream>
#include <string>
#include "../HashList/HashListChained.h"
#include "../HashList/hash.h"

using std::cin;
using std::cout;
using std::endl;
using std::istream;
using std::ostream;
using std::string;

/*
output
发现目前的尾节点value为空

insert 2147483647 233
output
发现所有尾节点value都变成了233
表示尾节点其实都是同一个

hash 666
显示会插入在6号桶上
insert 666 sixsixsix
output

hash 66
显示也会插入在6号桶上，产生了哈希碰撞
insert 66 sixtysix
output

发现按照key的大小顺序存储
erase 66
output
删除头节点也没有问题

erase 2147483647
抛出异常，异常正确处理

insert 666 changedval
output
成功修改已经存在的键值对


*/


template <class V>
void menuLoop(istream& in, ostream& out, HashListChained<V>& aMap) {
    while(true) {
        out  << "选择操作：" << endl
             << "1.插入         insert [key] [val]" << endl
             << "2.查找         find [key]" << endl
             << "3.删除         erase [key]" << endl
             << "4.输出         output" << endl
             << "5.显示哈希     hash [key]" << endl
             << "6.退出         exit" << endl;
        string method; in >> method;
        if(method == "insert") {
            int key; V val;
            in >> key >> val;
            try{
                aMap.insert(new Pair<V>(key, val));
            } catch (char const* str) {
                out << str << endl;
            }
        } else if(method == "find") {
            int key; in >> key;
            Pair<V>* ptr = aMap.find(key);
            if(ptr != nullptr) {
                out << *ptr << endl;
            } else {
                out << "nullptr, not found" << endl;
            }
        } else if(method == "erase") {
            int key; in >> key;
            try{
                aMap.erase(key);
            } catch(char const* str) {
                out << str << endl;
            }
        } else if(method == "output") {
            aMap.output(out);
        } 
        else if(method == "hash") {
            int key; in >> key;
            out << "Hash:" << (unsigned int) hash<int>{}(key) << "\t"
                << "ideal index:" << (unsigned int) hash<int>{}(key) % 10
                << endl;
        } else if(method == "exit") {
            break;
        } else {
            out << "Invalid method." << endl;
        }
    }
}



int main() {
    HashListChained<string> aMap(10, 10);
    menuLoop(cin, cout, aMap);
    system("pause");
    return 0;
}
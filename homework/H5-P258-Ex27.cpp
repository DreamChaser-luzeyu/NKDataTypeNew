#include <iostream>
#include <string>
#include "../HashList/HashList.h"
#include "../HashList/hash.h"

using std::cin;
using std::cout;
using std::endl;
using std::istream;
using std::ostream;
using std::string;

/*

hash 22
hash 77
发现理想情况下，key为22的Pair和key为77的Pair所对应的下标相同
尝试插入这两个Pair:
insert 22 222
insert 77 777
按照线性探查的冲突处理方法，key为77的Pair会位于紧邻22的下一个空位置
output
发现确实如此，77在22下面

把这两个Pair删除
erase 22
erase 77
再重新插入Pair
insert 22 222
output
发现前面两个标注为Used的位置未被使用
因为如果强行使用，会导致key值在表中可能不唯一

可是不使用又导致了空间的浪费
所以在标记为Used的位置占比到达一定程度（60%）时
会调用resetList()函数，来重新生成整个哈希表
这样就会重新利用（相当于回收了）标注为Used的空位置
erase 22 222

继续插入更多数据：
insert 77 777
insert 22 222
(22在77下面，进一步说明22和77对应的Hash值相同)
insert 44 444
insert 33 333
至neverUsed==false的位置超过60%：
（此时已有7个位置标注为Used）

尝试删除
erase 33
自动调用resetList()函数
output
发现原先被标注为Used的空位置已经可用，浪费的空间已经回收
表示整个哈希表已经重新生成

*/

// catch(char const*)

template <class K, class V>
void menuLoop(istream& in, ostream& out, HashList<K, V>& aMap) {
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
            K key; V val;
            in >> key >> val;
            try{
                aMap.insert(new Pair<K, V>(key, val));
            } catch (char const* str) {
                out << str << endl;
            }
        } else if(method == "find") {
            K key; in >> key;
            Pair<K, V>* ptr = aMap.find(key);
            if(ptr != nullptr) {
                out << *ptr << endl;
            } else {
                out << "nullptr, not found" << endl;
            }
        } else if(method == "erase") {
            K key; in >> key;
            try{
                aMap.erase_mark(key);
            } catch(char const* str) {
                out << str << endl;
            }
        } else if(method == "output") {
            aMap.output(out);
        } 
        else if(method == "hash") {
            K key; in >> key;
            out << "Hash:" << (unsigned int) hash<K>{}(key) << "\t"
                << "ideal index:" << (unsigned int) hash<K>{}(key) % 10
                << endl;
        } else if(method == "exit") {
            break;
        } else {
            out << "Invalid method." << endl;
        }
    }
}



int main() {
    HashList<string, string> aMap(10, 10);
    menuLoop(cin, cout, aMap);
    system("pause");
    return 0;
}
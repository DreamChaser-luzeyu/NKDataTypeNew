#include "标头.h"
int main()
{
    int n;
    cin >> n;
    cout << n << endl;
    HashTable<int> table(n);
    table.output();
    int *temp = new int[n];
    for (int i = 0; i < n; i++)
    {
        cin >> temp[i];
        table.insert(temp[i]);
    }
    table.output();
    int t = 0;
    cout << "请输入要删除的数" << endl;
    cin >> t;
    table.erase(t);
    table.output();
    cout << "请输入要添加的数" << endl;
    cin >> t;
    table.insert(t);
    cout << "请输入要添加的数" << endl;
    cin >> t;
    table.insert(t);
    cout << "请输入要添加的数" << endl;
    cin >> t;
    table.insert(t);
    table.output();
    cout << "请输入要删除的数" << endl;
    cin >> t;
    table.erase(t);
    table.output();
    cout << "请输入要删除的数" << endl;
    cin >> t;
    table.erase(t);
    table.output();
    system("pause");
    return 0;
}
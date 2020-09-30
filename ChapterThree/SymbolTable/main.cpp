#include <iostream>
#include <string>

// 不同实现方法的符号表
/**
* SEQ SequentialSearchST
* BIN BinarySerachST
*
*
*/
#define ORDERED
#define BIN

using namespace std;
#ifdef SEQ
    #include "SequentialSearchST.h"
    SequentialSearchST<string, int> st;
#endif // SEQ

#ifdef BIN
    #include "BinarySearchST.h"
    BinarySearchST<string, int> st;
#endif // BIN


void print_details();

string high_frequency = " ";
string::size_type min_len;
int cnt = 0;

int main(int argc, char** args)
{
    // system("chcp 65001");
    min_len = stoi(args[1]);
    string word;
    while (cin >> word) {
        cnt++;
        if ( word.size() < min_len) continue;
        if (!st.contains(word)) st.put(word, 1);
        else st.put(word, *(st.get(word)) + 1);
    }

    // 获取最高频单词
    st.put(high_frequency, 0);
    for (const string &word: st.keys()) {
        if ( *(st.get(word)) > *(st.get(high_frequency)) )
            high_frequency = word;
    }
    st.ddelete(" ");

    print_details();
    cout << "单词数量: " << cnt << "\n";
    cout << "出现频率最多的单词: ";
    cout << high_frequency << " " << *(st.get(high_frequency)) << "\n";
    cout << "总计: " << st.size() << "\n";
    cout << "ST中是否存在 the: " << boolalpha << st.contains("the") << " \n";

    // 测试有序的ST
    #ifdef ORDERED
    cout << "最小的单词: " << st.min() << "\n";
    cout << "排名为的单词: " << st.select(1) << "\n";
    cout << "最大的单词: " << st.max() << "\n";
    #endif // ORDERED

    return 0;
}

void print_details()
{
    cout << "该文本包含的长度大于 " << min_len << " 单词以及对应的数量:\n";
    for (const string &word: st.keys()) {
        cout << word << " " << *(st.get(word)) << "\n";
    }
}


#include <ctime>
#include <iostream>
#include <string>

// 不同实现方法的符号表
/**
* SEQ SequentialSearchST
* BIN BinarySerachST
* TSB BST
* RBT RedBlackBST
* SCH SeparateChainingHash
*/
#define SCH

/**
* WC 测试数据 tale.txt tinyTale.txt leipzig1M.txt
* ORDERED 测试数据 ordered.txt
*/
#define WC // WC  或 ORDERED

/**
* TEST 测试 delete_min, delete_max, rank, ceil, floor
* NOTEST 不进行测试
*/
#define TEST
using namespace std;

#ifdef SEQ
    #include "SequentialSearchST.h"
    SequentialSearchST<string, int> st;
#endif // SEQ

#ifdef BIN
    #include "BinarySearchST.h"
    BinarySearchST<string, int> st;
#endif // BIN

#ifdef TSB
    #include "BST.h"
    BST<string, int> st;
#endif // BST

#ifdef RBT
    #include "RedBlackBST.h"
    RedBlackBST<string, int> st;
#endif // RBT

#ifdef SCH
    #include "SeparateChainingHashST.h"
    SeparateChainingHashST<string, int> st;
#endif // SCH

// 分析 tinyTale.txt tale.txt leipzig1M.txt
void word_count();
void print_details();

string high_frequency = " ";
string::size_type min_len;
int cnt = 0;
clock_t t;

int main(int argc, char** args)
{
    system("chcp 65001");
    min_len = stoi(args[1]);

    t = clock(); //开始计时
    string word;
    while (cin >> word) {
        cnt++;
        if ( word.size() < min_len) continue;
        if (!st.contains(word)) st.put(word, 1);
        else st.put(word, *(st.get(word)) + 1);
    }

    #ifdef WC
    word_count();
    #endif // WC

    // 测试有序的ST
    #ifdef ORDERED
    print_details();
    cout << "单词总数量: " << st.size() << "\n";
    cout << "最小的单词: " << st.min() << "\n";
    cout << "排名为 1 的单词: " << st.select(1) << "\n";
    cout << "排名为 -2 的单词: " << st.select(st.size()-2) << "\n";
    cout << "最大的单词: " << st.max() << "\n";
    cout << "单词 the 的排名: " << st.rank("the") << "\n";

    #ifdef TEST
    cout << "删除最大和最小的单词以及 the \n";
    st.delete_max();
    st.delete_min();
    st.ddelete("the");
    print_details();
    cout << "floor(\"c\"): " << st.floor("c") << "\n";
    cout << "ceil(\"x\"): " << st.ceil("x") << "\n";
    cout << "大于等于c 小于等于x 的单词\n";
    for (string& word: st.keys("c", "x")) cout << word << "\n";
    #endif // TEST

    #endif // ORDERED

    return 0;
}

void print_details()
{
    for (const string &word: st.keys()) {
        cout << word << " " << *(st.get(word)) << "\n";
    }
}

void word_count()
{
    // 获取最高频单词
    st.put(high_frequency, 0);
    for (const string &word: st.keys()) {
        if ( *(st.get(word)) > *(st.get(high_frequency)) )
            high_frequency = word;
    }
    st.ddelete(" ");

    cout << "该文本包含的长度大于 " << min_len << " 单词以及对应的数量:\n";
    //print_details();
    cout << "单词数量: " << cnt << "\n";
    cout << "出现频率最多的单词: ";
    cout << high_frequency << " " << *(st.get(high_frequency)) << "\n";
    cout << "总计: " << st.size() << "\n";
    cout << "ST中是否存在 the: " << boolalpha << st.contains("the") << " \n";
    t = clock() - t;
    cout << "花费时间: " << t << " clicks" << endl;
}


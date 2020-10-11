#include <ctime>
#include <iostream>
#include "TrieST.h"

/**
* WC 测试数据 tale.txt tinyTale.txt leipzig1M.txt
* TEST 测试数据 shells.txt
*/
#define WC

/**
*   TRIE R路单词查找树
*   THREE 3路单词查找树
*/
#define THREE

#ifdef TRIE
    #include "TrieST.h"
    TrieST<int> st;
#endif // TRIE

#ifdef THREE
    #include "TST.h"
    TST<int> st;
#endif // THRE
using namespace std;

void word_count();
void print_detals(const vector<string> &ks);

string::size_type min_len;
int cnt = 0;
string high_frequency = " ";
clock_t t;

int main(int argc, char** args)
{
    system("chcp 65001");
    //min_len = stoi(args[1]);
    t = clock();
    string word;
    while (cin >> word) {
        cnt++;
        if (!st.contains(word)) st.put(word, 1);
        else st.put(word, *(st.get(word)) + 1);
    }

    #ifdef WC
    word_count();
    #endif // WC

    #ifdef TEST
    cout << "所有单词: \n";
    vector<string> keys = st.keys();
    print_detals(keys);

    cout << "匹配 \".\"  的单词: \n";
    keys = st.keys_that_match(".");
    print_detals(keys);

    cout << "匹配 \"s..\"  的单词: \n";
    keys = st.keys_that_match("s..");
    print_detals(keys);

    cout << "匹配 \".he\"  的单词: \n";
    keys = st.keys_that_match(".he");
    print_detals(keys);

    cout << "匹配 \"s.e\"  的单词: \n";
    keys = st.keys_that_match("s.e");
    print_detals(keys);

    cout << "以 \"sh\" 开头的单词: \n";
    keys = st.keys_with_prefix("sh");
    print_detals(keys);

    cout << "\"shellss\" 最长的前缀键为: "  << st.longest_prefix("shellss") << "\n";

    #ifdef TRIE
    cout << "删除以 \"sh\" 开头的所有单词: \n";
    for (auto k: keys) st.ddelete(k);
    keys = st.keys();
    print_detals(keys);

    #endif // TRIE
    #endif // TEST

    return 0;
}

void print_detals(const vector<string> &ks)
{
    cout << "-------------------------------\n";
    cout << "总计: " << ks.size() << "\n";
    for (auto key: ks) {
        cout << key << " " << *(st.get(key)) << "\n";
    }
    cout << "-------------------------------\n\n";
}

void word_count()
{
    //获取最高频单词
    st.put(high_frequency, 0);
    for (const string &word: st.keys()) {
        if ( *(st.get(word)) > *(st.get(high_frequency)) )
            high_frequency = word;
    }
    //st.ddelete(" ");

    cout << "该文本包含的长度大于 " << min_len << " 单词以及对应的数量:\n";
    cout << "单词数量: " << cnt << "\n";
    cout << "出现频率最多的单词: ";
    cout << high_frequency << " " << *(st.get(high_frequency)) << "\n";
    cout << "总计: " << st.size() << "\n";
    cout << "ST中是否存在 the: " << boolalpha << st.contains("the") << " \n";
    t = clock() - t;
    cout << "花费时间: " << t << " clicks" << endl;
}

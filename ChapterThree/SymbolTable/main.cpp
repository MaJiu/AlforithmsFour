#include <iostream>
#include <string>
#include "SequentialSearchST.h"

using namespace std;

int main(int argc, char** args)
{

    string::size_type min_len = stoi(args[1]);
    SequentialSearchST<string, int> st;
    string word;
    while (cin >> word) {
        if ( word.size() < min_len) continue;
        if (!st.contains(word)) st.put(word, 1);
        else st.put(word, *(st.get(word)) + 1);
    }

    string high_frequency = " ";
    st.put(high_frequency, 0);
    for (const string &word: st.keys()) {
        if ( *(st.get(word)) > *(st.get(high_frequency)) )
            high_frequency = word;
    }
    cout << high_frequency << " " << *(st.get(high_frequency)) << endl;
    cout << st.size() << endl;
    return 0;
}

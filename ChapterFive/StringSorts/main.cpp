#include <iostream>
#include <algorithm>
#include <iterator>
#include <vector>
#include <string>

#define MSD

#ifdef LSD
    #include "LSD.h"
    auto string_sort = lsd_sort;
#endif // LSD

#ifdef MSD
    #include "MSD.h"
    auto string_sort = msd_sort;
#endif // MSD

#ifdef QQQ
    #include "Quick3string.h"
    auto string_sort = quick3_sort;
#endif // QQQ

using namespace std;


int main()
{
    vector<string> words;
    istream_iterator<string> ibeg(cin);
    istream_iterator<string> iend;
    copy(ibeg, iend, back_inserter(words));
    string_sort(words);
    ostream_iterator<string> out(cout, "\n");
    copy(words.begin(), words.end(), out);
    return 0;
}

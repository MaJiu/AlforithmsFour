#include <iostream>
#include <string>
#include "KMP.h"

using namespace std;

int main()
{
    string txt, pat;
    cin >> pat >> txt;
    KMP kmp(pat);
    int offset = kmp.search(txt);
    cout << "text:    " << txt << "\n";
    cout << "pattern: ";
    for (int i = 0; i < offset; i++) cout << " ";
    cout << pat << "\n";
    return 0;
}

#include <iostream>
#include <string>

#define BM

#ifdef PMK
    #include "KMP.h"
#endif // PMK

#ifdef RK
    #include "RabinKarp.h"
#endif // RK

#ifdef BM
    #include "BoyerMoore.h"
#endif // BM
using namespace std;

int main()
{

    string txt, pat;
    while (cin >> pat >> txt) {
        #ifdef PMK
        KMP search_algo(pat);
        #endif // PMK

        #ifdef RK
        RabinKarp search_algo(pat);
        #endif // RK

        #ifdef BM
        BoyerMoore search_algo(pat);
        #endif // BM
        int offset = search_algo.search(txt);
        cout << "--------------------------------------\n";
        cout << "text:    " << txt << "\n";
        cout << "pattern: ";
        for (int i = 0; i < offset; i++) cout << " ";
        cout << pat << "\n";
        cout << "--------------------------------------\n\n";
    }

    return 0;
}

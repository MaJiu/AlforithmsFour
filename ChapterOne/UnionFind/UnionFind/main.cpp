#include <iostream>
// #include "uf1.h"
// #include "uf2.h"
// #include "uf3.h"
#include "uf4.h"

using namespace std;

int main()
{
    int N;
    cin >> N;
    UF uf(N);
    int p, q;
    for (int i=0; i<N; i++) {
        cin >> p >> q;
        if (uf.connected(p, q)) continue;
        uf.uunion(p, q);
        cout << p << " " << q << "\n";
    }
    cout << uf.count() << " components" << endl;
    return 0;
}

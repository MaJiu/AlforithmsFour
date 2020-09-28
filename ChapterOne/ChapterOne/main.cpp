#include <iostream>
#include <numeric>
#include <string>
#include "Queue.h"
#include "Stack.h"
#include "ArrayStack.h"
#include "Bag.h"

using namespace std;

void test_stack();
void test_queue();
void test_array_stack();
void test_bag();

int main()
{
//    test_array_stack();
//    test_stack();
//    test_queue();
//    test_bag();
    string word;
    Stack<string> s;
    while (cin >> word) {
        if (word != "-") s.push(word);
        else if (!s.empty()) cout << s.pop() << " ";
    }
    cout << "( " << s.size() << " left on stack)" << endl;
    return 0;
}

void test_stack()
{
    cout << "Stack: " << endl;
    Stack<int> s;
    for (int i=0; i<10; i++) s.push(i);
    for (auto it=s.begin(); it != s.end(); ++it) cout << *it << " ";
    cout << endl;
    Stack<int> s2(s);
    s2.pop();
    for (int i: s) cout << i << " ";
    cout << endl;
    for (int i: s2) cout << i << " ";
    cout << endl;
    s2.pop();
    s = s2;
    for (int i: s) cout << i << " ";
    cout << endl;
}

void test_array_stack()
{
    cout << "ArrayStack: " << endl;
    ArrayStack<int> s;
    for (int i=0; i<10; i++) s.push(i);
    for (int i: s) cout << i << " ";
    cout << endl;
}

void test_queue()
{
    cout << "Queue: " << endl;
    Queue<int> q;
    for (int i=0; i<10; i++) {
        q.enqueue(i);
    }
    Queue<int> q2(q);
    q2.dequeue();
    for (int i: q) cout << i << " ";
    cout << endl;
    for (int i: q2) cout << i << " ";
    cout << endl;
    q = q2;
    for (int i: q) cout << i << " ";
    cout << endl;
}

void test_bag()
{
    cout << "Bag: " << endl;
    Bag<int> bag;
    for (int i=0; i<10; i++) bag.add(i);
    int sum = 0;
    for (int i: bag) sum += i;
    cout << sum << endl;
    cout << boolalpha << (sum == accumulate(bag.begin(), bag.end(), 0)) << endl;
}

/*
 * hello, world
 */

#include <iostream>
#include <thread>

using namespace std;

void hello() {
    cout << "hello, world2" << endl;
}

int main() {
    thread a([] { cout << "hello, world1" << endl; }), b(hello);
    a.join();
    b.join();
    return 0;
}
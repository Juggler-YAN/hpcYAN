/*
 * 带参数的函数（值，指针和引用）
 * 注意：引用是值引用
 */

#include <iostream>
#include <thread>

using namespace std;

template <class T>
void print(int i, T num1, T *num2, T &num3, T &&num4) {
    cout << "thread " << i << ": " << num1 << " " << *num2 << " " << num3 << " "
        << num4 << endl;
}

int main() {
    int num = 100;
    thread th[10];
    for (int i = 0; i < 10; ++i) {
        th[i] = thread(print<int>, i, num, &num, ref(num), 100);
    }
    for (int i = 0; i < 10; ++i) {
        th[i].join();
    }
    return 0;
}
/*
 * this_thread: 线程对自己进行控制
 * gei_id, sleep_duration, yield
 */

#include <atomic>
#include <iostream>
#include <thread>

using namespace std;

atomic_bool ready = 0;

void sleep(uintmax_t ms) { this_thread::sleep_for(chrono::milliseconds(ms)); }

void count() {
    while (!ready) this_thread::yield();
    for (int i = 0; i <= 20'0000'0000; i++)
        ;
    cout << "Thread " << this_thread::get_id() << " finished!" << endl;
    return;
}

int main() {

    thread th[10];
    for (int i = 0; i < 10; i++) {
        th[i] = thread(::count);
    }
    sleep(3000);
    ready = true;
    cout << "Start!" << endl;
    for (int i = 0; i < 10; i++) {
        th[i].join();
    }
    return 0;

}

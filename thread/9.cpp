/*
 * 异步
 * wait_for
 * launch::async异步启动，launch::deferred惰性求值
 */

#include <future>
#include <iostream>

using namespace std;

void count_big_number() {
    for (long long i = 0; i <= 1e10; ++i)
        ;
}

int main() {

    future<void> fut = async(launch::async, count_big_number);
    cout << "Please wait" << flush;
    while (fut.wait_for(chrono::seconds(1)) != future_status::ready) {
        cout << '.' << flush;
    }
    cout << endl << "Finished!" << endl;
    return 0;

}

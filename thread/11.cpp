/*
 * promise
 * future的值不能改变，promise的值可以改变。
 */
#include <future>
#include <iostream>
#include <thread>

using namespace std;

template <class... Args>
decltype(auto) sum(Args &&...args) {
  return (0 + ... + args);
}

template <class... Args>
void sum_thread(promise<long long> &val, Args &&...args) {
  val.set_value(sum(args...));
}

int main() {
  promise<long long> sum_value;
  thread get_sum(sum_thread<int, int, int>, ref(sum_value), 1, 10, 100);
  cout << sum_value.get_future().get() << endl;
  get_sum.join();
  return 0;
}

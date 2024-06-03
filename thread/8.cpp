/*
 * 异步
 * 有返回值
 */

#include <future>
#include <iostream>

using namespace std;

template <class... Args>
decltype(auto) sum(Args&&... args) {
  return (0 + ... + args);
}

int main() {
  future<int> val = async(launch::async, sum<int, int, int>, 1, 10, 100);
  cout << val.get() << endl;
  return 0;
}

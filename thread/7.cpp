/*
 * 异步
 * 无返回值
 */

#include <future>
#include <iostream>

using namespace std;

int main() {
  auto f1 = async(
      launch::async, [](const char *message) { cout << message << flush; },
      "Hello, ");
  cout << "World!" << endl;
  f1.wait();
  return 0;
}

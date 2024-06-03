/*
 * 原子操作
 */

#include <iostream>
#include <mutex>
#include <thread>
#include <atomic>

using namespace std;

atomic<int> n = 0;

void count10000() {
  for (int i = 1; i <= 10000; i++) {
    n++;
  }
}

int main() {
  thread th[100];
  for (thread &x : th) x = thread(count10000);
  for (thread &x : th) x.join();
  cout << n << endl;
  return 0;
}
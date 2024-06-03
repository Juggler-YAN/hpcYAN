/*
 * 锁
 * 多种mutex：互斥/共享、递归、超时
 * 方法：lock, unlock, try_lock
 * 管理mutex：lock_guard、unique_lock、shared_lock、scoped_lock + 锁定策略：defer_lock、try_to_lock、adopt_lock
 * 管理mutex的原理是RAII变成机制
 * 缺点：频繁上锁去锁会导致性能剧烈下降
 */

#include <iostream>
#include <mutex>
#include <thread>

using namespace std;

int n = 0;
mutex mtx;

void count10000() {
  for (int i = 1; i <= 10000; i++) {
    mtx.lock();
    n++;
    mtx.unlock();
  }
}

int main() {
  thread th[100];
  for (thread &x : th) x = thread(count10000);
  for (thread &x : th) x.join();
  cout << n << endl;
  return 0;
}

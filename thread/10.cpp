/*
 * 异步
 * packaged_task
 */

#include <cmath>
#include <future>
#include <iomanip>
#include <iostream>
#include <vector>

#define MAX 1e8

using namespace std;

double concurrent_worker(int min, int max) {
    double sum = 0;
    for (int i = min; i <= max; i++) {
        sum += sqrt(i);
    }
    return sum;
}

double concurrent_task(int min, int max) {
    
    vector<future<double>> results;
    
    unsigned concurrent_count = thread::hardware_concurrency();
    min = 0;
    for (int i = 0; i < concurrent_count; i++) {
        packaged_task<double(int, int)> task(concurrent_worker);
        results.push_back(task.get_future());
        int range = max / concurrent_count * (i + 1);
        thread t(std::move(task), min, range);
        t.detach();
        min = range + 1;
    }
    
    cout << "threads create finish" << endl;
    double sum = 0;
    for (auto& r : results) {
        sum += r.get();
    }
    return sum;

}

int main() {
    
    auto start_time = chrono::steady_clock::now();
    double r = concurrent_task(0, MAX);
    auto end_time = chrono::steady_clock::now();
    auto ms = chrono::duration_cast<chrono::milliseconds>(end_time - start_time)
                .count();
    cout << "Concurrent task finish, " << ms << " ms consumed, Result: " << r
       << endl;
    return 0;

}
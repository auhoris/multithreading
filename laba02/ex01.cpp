#include <cstdlib>
#include <iostream>
#include <mutex>
#include <thread>
using namespace std;

mutex msg;

void summ(int number, int arr[], int idx) {
    std::thread::id id = std::this_thread::get_id();
    msg.lock();
    cout << "Thread with id " << id << " started. "
         << "\n";
    msg.unlock();
    int sum = 0;
    for (int i = 0; i < number; i++) {
        sum += i;
    }
    arr[idx] = sum;
}

int main() {
    const int length = 20;
    thread::id id;
    thread thread_array[length];
    int res_arr[length] = {0};
    for (int i = 0; i < length; i++) {
        thread_array[i] = thread(summ, rand() % 10, res_arr, i);
    }
    for (int i = 0; i < length; i++) {
        if (thread_array[i].joinable()) {
            id = thread_array[i].get_id();
            thread_array[i].join();
            msg.lock();
            cout << "Thread with id " << id << " finished. With result "
                 << res_arr[i] << "\n";
            msg.unlock();
        }
    }
    return 0;
}

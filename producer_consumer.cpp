#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <queue>
#include <chrono>

using namespace std;

const int BUFFER_SIZE = 5;
queue<int> buffer;

mutex mtx;
condition_variable cv_producer, cv_consumer;

void producer() {
    for (int i = 0; i < 10; ++i) {
        unique_lock<mutex> lock(mtx);
        cv_producer.wait(lock, [] { return buffer.size() < BUFFER_SIZE; });

        // Produce item
        int item = i;
        buffer.push(item);
        cout << "Produced item: " << item << endl;

        lock.unlock();
        cv_consumer.notify_one();

        this_thread::sleep_for(chrono::milliseconds(500));
    }
}

void consumer() {
    for (int i = 0; i < 10; ++i) {
        unique_lock<mutex> lock(mtx);
        cv_consumer.wait(lock, [] { return !buffer.empty(); });

        // Consume item
        int item = buffer.front();
        buffer.pop();
        cout << "Consumed item: " << item << endl;

        lock.unlock();
        cv_producer.notify_one();

        this_thread::sleep_for(chrono::milliseconds(1000));
    }
}

int main() {
    thread producer_thread(producer);
    thread consumer_thread(consumer);

    producer_thread.join();
    consumer_thread.join();

    return 0;
}

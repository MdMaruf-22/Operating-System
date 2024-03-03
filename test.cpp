#include <iostream>
#include <stack>

using namespace std;

const int BUFFER_SIZE = 5;
stack<int> buffer;

void produceItem(int item) {
    buffer.push(item);
    cout << "Producer produces item number: " << item << endl;
}

void consumeItem() {
    if (!buffer.empty()) {
        cout << "Consumer consumes item number: " << buffer.top() << ".\n";
        buffer.pop();
    } else {
        cout << "The Buffer is empty! New data cannot be consumed!\n";
    }
}

void producer() {
    static int itemCount = 0;
    if (buffer.size() < BUFFER_SIZE) {
        produceItem(++itemCount);
    } else {
        cout << "The Buffer is full! New data cannot be produced!\n";
    }
}

void consumer() {
    consumeItem();
}

int main() {
    int choice;
    cout << "1. Enter 1 for Producer\n"
         << "2. Enter 2 for Consumer\n"
         << "3. Enter 3 to Exit\n";

    while (true) {
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            producer();
            break;

        case 2:
            consumer();
            break;

        case 3:
            return 0;

        default:
            cout << "Invalid choice. Please enter again.\n";
        }
    }

    return 0;
}

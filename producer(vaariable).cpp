#include <iostream>

using namespace std;

int mymutex = 1;
int myfull = 0;
int myempty = 10, mydata = 0;

void producer() {
    --mymutex;
    ++myfull;
    --myempty;
    mydata++;
    cout << "\nProducer produces item number: " << mydata << endl;
    ++mymutex;
}

void consumer() {
    --mymutex;
    --myfull;
    ++myempty;
    cout << "\nConsumer consumes item number: " << mydata << ".\n";
    mydata--;
    ++mymutex;
}

int main() {
    int n, i;
    cout << "\n1. Enter 1 for Producer"
         << "\n2. Enter 2 for Consumer"
         << "\n3. Enter 3 to Exit";

    for (i = 1; i > 0; i++) {
        cout << "\nEnter your choice: ";
        cin >> n;

        switch (n) {
        case 1:
            if ((mymutex == 1) && (myempty != 0)) {
                producer();
            } else {
                cout << "The Buffer is full. New data cannot be produced!";
            }
            break;

        case 2:
            if ((mymutex == 1) && (myfull != 0)) {
                consumer();
            } else {
                cout << "The Buffer is empty! New data cannot be consumed!";
            }
            break;

        case 3:
            exit(0);
            break;
        }
    }
    return 0;
}
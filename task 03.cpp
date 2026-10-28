
#include <iostream>
using namespace std;

class myCarStack {
private:
    int* arr;
    int capacity;
    int count;

public:
    myCarStack(int size) {
        capacity = size;
        count = 0;
        arr = new int[capacity];
    }

    bool isEmpty() const {
        return count == 0;
    }

    bool isFull() const {
        return count == capacity;
    }

    int size() const {
        return count;
    }

    void push(int car) {
        if (isFull()) {
            cout << "Parking lot is full!\n";
            return;
        }

        arr[count++] = car;
    }

    int pop() {
        if (isEmpty()) {
            cout << "Parking lot is empty!\n";
            return -1;
        }

        return arr[--count];
    }

    int top() const {
        if (isEmpty())
            return -1;

        return arr[count - 1];
    }

    bool contains(int car) const {
        for (int i = 0; i < count; i++) {
            if (arr[i] == car)
                return true;
        }
        return false;
    }

    void display() const {
        if (isEmpty()) {
            cout << "No cars are parked.\n";
            return;
        }

        cout << "Cars (top to bottom):\n";
        for (int i = count - 1; i >= 0; i--) {
            cout << arr[i] << endl;
        }
    }

    ~myCarStack() {
        delete[] arr;
    }
};

int main() {
    const int MAX_CARS = 8;

    myCarStack parking(MAX_CARS);

    int choice, car;
    bool found;

    do {
        cout << "\n===== PARKING LOT MENU =====\n";
        cout << "1. Park a new car\n";
        cout << "2. Remove a car by number\n";
        cout << "3. View parked cars\n";
        cout << "4. Show total cars parked\n";
        cout << "5. Search for a car\n";
        cout << "6. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            if (parking.isFull()) {
                cout << "Parking lot is full. Maximum 8 cars.\n";
                break;
            }

            cout << "Enter car number: ";
            cin >> car;

            if (parking.contains(car)) {
                cout << "This car is already parked.\n";
                break;
            }

            parking.push(car);
            cout << "Car parked successfully.\n";
            break;

        case 2:
            if (parking.isEmpty()) {
                cout << "Parking lot is empty.\n";
                break;
            }

            cout << "Enter car number to remove: ";
            cin >> car;

            if (!parking.contains(car)) {
                cout << "Car not found.\n";
                break;
            }

            {
                myCarStack temp(MAX_CARS);

                // Move blocking cars to temporary stack
                while (parking.top() != car) {
                    temp.push(parking.pop());
                }

                // Remove the requested car
                parking.pop();
                cout << "Car removed successfully.\n";

                // Restore the remaining cars
                while (!temp.isEmpty()) {
                    parking.push(temp.pop());
                }
            }
            break;

        case 3:
            parking.display();
            break;

        case 4:
            cout << "Total cars parked: "
                << parking.size() << "/" << MAX_CARS << endl;
            break;

        case 5:
            cout << "Enter car number to search: ";
            cin >> car;

            found = parking.contains(car);

            if (found)
                cout << "Car is present in the parking lot.\n";
            else
                cout << "Car is not present in the parking lot.\n";
            break;

        case 6:
            cout << "Exiting parking system.\n";
            break;

        default:
            cout << "Invalid choice.\n";
        }

    } while (choice != 6);

    return 0;
}


#include <iostream>
using namespace std;

template <typename T>
class AbstractStack {
public:
    virtual void push(T value) = 0;
    virtual T pop() = 0;
    virtual T top() const = 0;
    virtual bool isEmpty() const = 0;
    virtual bool isFull() const = 0;
    virtual ~AbstractStack() {}
};

template <typename T>
class myStack : public AbstractStack<T> {
private:
    T* arr;
    T* minArr;
    int capacity;
    int count;
    int minCount;

public:
    myStack(int size) {
        capacity = size;
        count = 0;
        minCount = 0;

        arr = new T[capacity];
        minArr = new T[capacity];
    }

    void push(T value) override {
        if (isFull()) {
            cout << "Stack is full!\n";
            return;
        }

        arr[count++] = value;

        if (minCount == 0 || value <= minArr[minCount - 1]) {
            minArr[minCount++] = value;
        }

        cout << "Element pushed successfully.\n";
    }

    T pop() override {
        if (isEmpty()) {
            cout << "Stack is empty!\n";
            return T();
        }

        T value = arr[--count];

        if (value == minArr[minCount - 1]) {
            minCount--;
        }

        return value;
    }

    T top() const override {
        if (isEmpty()) {
            cout << "Stack is empty!\n";
            return T();
        }

        return arr[count - 1];
    }

    T getMin() const {
        if (isEmpty()) {
            cout << "Stack is empty; no minimum exists.\n";
            return T();
        }

        return minArr[minCount - 1];
    }

    bool isEmpty() const override {
        return count == 0;
    }

    bool isFull() const override {
        return count == capacity;
    }

    void display() const {
        if (isEmpty()) {
            cout << "Stack is empty.\n";
            return;
        }

        cout << "Stack from top to bottom:\n";
        for (int i = count - 1; i >= 0; i--) {
            cout << arr[i] << endl;
        }
    }

    ~myStack() override {
        delete[] arr;
        delete[] minArr;
    }
};

int main() {
    int size, choice, value;

    cout << "Enter stack capacity: ";
    cin >> size;

    if (!cin || size <= 0) {
        cout << "Invalid capacity.\n";
        return 0;
    }

    myStack<int> s(size);

    do {
        cout << "\n===== MINIMUM STACK MENU =====\n";
        cout << "1. Push element\n";
        cout << "2. Pop element\n";
        cout << "3. Show top element\n";
        cout << "4. Check if stack is empty\n";
        cout << "5. Check if stack is full\n";
        cout << "6. Display stack\n";
        cout << "7. Show minimum element\n";
        cout << "8. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            cout << "Enter value: ";
            cin >> value;
            if (cin)
                s.push(value);
            else {
                cout << "Invalid input.\n";
                return 0;
            }
            break;

        case 2:
            if (!s.isEmpty())
                cout << "Popped: " << s.pop() << endl;
            else
                cout << "Stack is empty!\n";
            break;

        case 3:
            if (!s.isEmpty())
                cout << "Top: " << s.top() << endl;
            else
                cout << "Stack is empty!\n";
            break;

        case 4:
            cout << (s.isEmpty() ? "Stack is empty.\n"
                : "Stack is not empty.\n");
            break;

        case 5:
            cout << (s.isFull() ? "Stack is full.\n"
                : "Stack is not full.\n");
            break;

        case 6:
            s.display();
            break;

        case 7:
            if (!s.isEmpty())
                cout << "Minimum element: " << s.getMin() << endl;
            else
                cout << "Stack is empty!\n";
            break;

        case 8:
            cout << "Program ended.\n";
            break;

        default:
            cout << "Invalid choice.\n";
        }

    } while (choice != 8);

    return 0;
}

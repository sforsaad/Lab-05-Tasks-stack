
#include <iostream>
using namespace std;

template <typename T>
class myStack {
private:
    T* arr;
    int capacity;
    int count;

public:
    myStack(int size) {
        capacity = size;
        count = 0;
        arr = new T[capacity];
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

    bool push(T value) {
        if (isFull())
            return false;

        arr[count++] = value;
        return true;
    }

    T pop() {
        if (isEmpty())
            return T();

        return arr[--count];
    }

    T top() const {
        if (isEmpty())
            return T();

        return arr[count - 1];
    }

    void clear() {
        count = 0;
    }

    ~myStack() {
        delete[] arr;
    }
};

int main() {
    const int MAX_TEXT = 1000;
    const int MAX_HISTORY = 1000;

    char text[MAX_TEXT];
    int length = 0;
    text[0] = '\0';

   
    myStack<char> undoType(MAX_HISTORY);
    myStack<char> undoValue(MAX_HISTORY);

    myStack<char> redoType(MAX_HISTORY);
    myStack<char> redoValue(MAX_HISTORY);

    int choice;
    char ch, type, value;

    do {
        cout << "\n===== TEXT EDITOR MENU =====\n";

        cout << "Current text: ";
        for (int i = 0; i < length; i++)
            cout << text[i];

        cout << "\n\n";
        cout << "1. Type a character\n";
        cout << "2. Delete last character\n";
        cout << "3. Undo\n";
        cout << "4. Redo\n";
        cout << "5. Display current text\n";
        cout << "6. Show history status\n";
        cout << "7. Exit\n";
        cout << "Enter choice: ";

        if (!(cin >> choice)) {
            cout << "Invalid input.\n";
            return 0;
        }

        switch (choice) {

        case 1:
            if (length >= MAX_TEXT - 1) {
                cout << "Text is full.\n";
                break;
            }

            if (undoType.isFull()) {
                cout << "Undo history is full.\n";
                break;
            }

            cout << "Enter character to type: ";
            cin >> ch;

            if (!cin) {
                cout << "Invalid character input.\n";
                return 0;
            }

            undoType.push('T');
            undoValue.push(ch);

       
            redoType.clear();
            redoValue.clear();

            text[length++] = ch;
            text[length] = '\0';

            cout << "Character typed successfully.\n";
            break;

        case 2:
            if (length == 0) {
                cout << "Text is empty. Nothing to delete.\n";
                break;
            }

            if (undoType.isFull()) {
                cout << "Undo history is full.\n";
                break;
            }

      
            ch = text[length - 1];

            undoType.push('D');
            undoValue.push(ch);

          
            redoType.clear();
            redoValue.clear();

            length--;
            text[length] = '\0';

            cout << "Last character deleted.\n";
            break;

        case 3:
            if (undoType.isEmpty()) {
                cout << "Nothing to undo.\n";
                break;
            }

            if (redoType.isFull()) {
                cout << "Redo history is full.\n";
                break;
            }

        
            type = undoType.pop();
            value = undoValue.pop();

            if (type == 'T') {
                
                if (length > 0) {
                    length--;
                    text[length] = '\0';
                }
            }
            else if (type == 'D') {
              
                if (length < MAX_TEXT - 1) {
                    text[length++] = value;
                    text[length] = '\0';
                }
            }

    
            redoType.push(type);
            redoValue.push(value);

            cout << "Undo completed.\n";
            break;

        case 4:
            if (redoType.isEmpty()) {
                cout << "Nothing to redo.\n";
                break;
            }

            if (undoType.isFull()) {
                cout << "Undo history is full.\n";
                break;
            }

        
            type = redoType.pop();
            value = redoValue.pop();

            if (type == 'T') {
             
                if (length < MAX_TEXT - 1) {
                    text[length++] = value;
                    text[length] = '\0';
                }
            }
            else if (type == 'D') {
                
                if (length > 0) {
                    length--;
                    text[length] = '\0';
                }
            }


            undoType.push(type);
            undoValue.push(value);

            cout << "Redo completed.\n";
            break;

        case 5:
            cout << "Current text: ";
            for (int i = 0; i < length; i++)
                cout << text[i];

            cout << endl;
            break;

        case 6:
            cout << "Undo actions available: "
                << undoType.size() << endl;

            cout << "Redo actions available: "
                << redoType.size() << endl;
            break;

        case 7:
            cout << "Exiting text editor.\n";
            break;

        default:
            cout << "Invalid choice. Try again.\n";
        }

    } while (choice != 7);

    return 0;
}



#include <iostream>
using namespace std;

const int MAX_SIZE = 100;

// Display all array elements
void displayArray(int arr[], int size) {
    if (size == 0) {
        cout << "Array is empty.\n";
        return;
    }

    cout << "Array elements: ";

    for (int i = 0; i < size; i++) {
        cout << arr[i] << " ";
    }

    cout << endl;
}

// Insert an element at a given position (1-based)
void insertElement(int arr[], int &size, int element, int position) {
    if (size >= MAX_SIZE) {
        cout << "Error: Array is full.\n";
        return;
    }

    if (position < 1 || position > size + 1) {
        cout << "Error: Invalid position.\n";
        return;
    }

    for (int i = size; i >= position; i--) {
        arr[i] = arr[i - 1];
    }

    arr[position - 1] = element;
    size++;

    cout << "Element inserted successfully.\n";
}

// Delete an element from a given position (1-based)
void deleteElement(int arr[], int &size, int position) {
    if (size == 0) {
        cout << "Error: Array is empty.\n";
        return;
    }

    if (position < 1 || position > size) {
        cout << "Error: Invalid position.\n";
        return;
    }

    for (int i = position - 1; i < size - 1; i++) {
        arr[i] = arr[i + 1];
    }

    size--;

    cout << "Element deleted successfully.\n";
}

// Search for an element using linear search
void searchElement(int arr[], int size, int target) {
    for (int i = 0; i < size; i++) {
        if (arr[i] == target) {
            cout << "Element found at position " << i + 1 << ".\n";
            return;
        }
    }

    cout << "Element not found.\n";
}

int main() {
    int arr[MAX_SIZE];
    int size, choice, element, position;

    cout << "===== BASIC ARRAY OPERATIONS =====\n";

    cout << "Enter initial array size (0-" << MAX_SIZE << "): ";
    cin >> size;

    if (cin.fail() || size < 0 || size > MAX_SIZE) {
        cout << "Invalid array size.\n";
        return 1;
    }

    cout << "Enter " << size << " elements:\n";

    for (int i = 0; i < size; i++) {
        cin >> arr[i];

        if (cin.fail()) {
            cout << "Invalid input.\n";
            return 1;
        }
    }

    do {
        cout << "\n========== MENU ==========\n";
        cout << "1. Insert Element\n";
        cout << "2. Delete Element\n";
        cout << "3. Search Element\n";
        cout << "4. Display Array\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";

        cin >> choice;

        if (cin.fail()) {
            cout << "Invalid input. Exiting program.\n";
            return 1;
        }

        switch (choice) {
            case 1:
                cout << "Enter element to insert: ";
                cin >> element;

                cout << "Enter position (1-" << size + 1 << "): ";
                cin >> position;

                if (cin.fail()) {
                    cout << "Invalid input.\n";
                    return 1;
                }

                insertElement(arr, size, element, position);
                break;

            case 2:
                cout << "Enter position to delete (1-" << size << "): ";
                cin >> position;

                if (cin.fail()) {
                    cout << "Invalid input.\n";
                    return 1;
                }

                deleteElement(arr, size, position);
                break;

            case 3:
                cout << "Enter element to search: ";
                cin >> element;

                if (cin.fail()) {
                    cout << "Invalid input.\n";
                    return 1;
                }

                searchElement(arr, size, element);
                break;

            case 4:
                displayArray(arr, size);
                break;

            case 5:
                cout << "Exiting program. Thank you!\n";
                break;

            default:
                cout << "Invalid choice. Please try again.\n";
        }

    } while (choice != 5);

    return 0;
}

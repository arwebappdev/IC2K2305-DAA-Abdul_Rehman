
#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>
using namespace std;

struct Item {
    int id;
    double value;
    double weight;
    double ratio;
};

// Compare items according to value-to-weight ratio
bool compare(Item a, Item b) {
    return a.ratio > b.ratio;
}

double fractionalKnapsack(vector<Item>& items, double capacity) {
    // Sort items by decreasing value-to-weight ratio
    sort(items.begin(), items.end(), compare);

    double totalValue = 0.0;

    cout << "\nSelected Items:\n";

    for (const Item& item : items) {
        if (capacity <= 0) {
            break;
        }

        if (item.weight <= capacity) {
            // Take the complete item
            capacity -= item.weight;
            totalValue += item.value;

            cout << "Item " << item.id
                 << ": Full item selected"
                 << " | Value = " << item.value
                 << " | Weight = " << item.weight << endl;
        } else {
            // Take only the fraction that fits
            double fraction = capacity / item.weight;
            double selectedValue = item.value * fraction;

            totalValue += selectedValue;

            cout << "Item " << item.id
                 << ": " << fixed << setprecision(2)
                 << fraction * 100 << "% selected"
                 << " | Value = " << selectedValue
                 << " | Weight = " << capacity << endl;

            capacity = 0;
        }
    }

    return totalValue;
}

int main() {
    int n;
    double capacity;

    cout << "Enter number of items: ";
    cin >> n;

    if (n <= 0 || n > 100) {
        cout << "Please enter a number of items between 1 and 100."
             << endl;
        return 0;
    }

    vector<Item> items(n);

    cout << "Enter weight and value of each item:\n";

    for (int i = 0; i < n; i++) {
        cout << "Item " << i + 1 << " (weight value): ";
        cin >> items[i].weight >> items[i].value;

        if (items[i].weight <= 0 || items[i].value < 0) {
            cout << "Weight must be positive and value cannot be negative."
                 << endl;
            return 0;
        }

        items[i].id = i + 1;
        items[i].ratio = items[i].value / items[i].weight;
    }

    cout << "\nEnter knapsack capacity: ";
    cin >> capacity;

    if (capacity < 0) {
        cout << "Capacity cannot be negative." << endl;
        return 0;
    }

    double maximumValue = fractionalKnapsack(items, capacity);

    cout << "\nMaximum value in knapsack: "
         << fixed << setprecision(2) << maximumValue << endl;

    return 0;
}

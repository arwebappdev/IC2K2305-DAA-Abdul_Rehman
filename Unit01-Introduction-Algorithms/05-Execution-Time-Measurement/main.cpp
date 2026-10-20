
#include <iostream>
#include <vector>
#include <chrono>
#include <fstream>
using namespace std;
using namespace chrono;

// Prevent the compiler from discarding search results.
volatile int resultSink = -1;

// Linear Search
int linearSearch(const vector<int>& arr, int target) {
    for (int i = 0; i < static_cast<int>(arr.size()); i++) {
        if (arr[i] == target) {
            return i;
        }
    }

    return -1;
}

int main() {
    // Different input sizes
    vector<int> inputSizes = {
        100, 1000, 10000, 100000, 1000000
    };

    // Repetitions for each input size
    vector<int> repetitions = {
        10000, 5000, 1000, 100, 10
    };

    ofstream outputFile("results.csv");

    if (!outputFile.is_open()) {
        cout << "Error: Unable to create results.csv\n";
        return 1;
    }

    outputFile << "Input Size,Repetitions,Average Time (ns)\n";

    cout << "===== EXECUTION TIME ANALYSIS =====\n\n";

    cout << "Input Size\tRepetitions\tAverage Time (ns)\n";
    cout << "------------------------------------------------\n";

    for (size_t i = 0; i < inputSizes.size(); i++) {

        int size = inputSizes[i];
        int repeat = repetitions[i];

        // Generate array outside the timed section
        vector<int> arr(size);

        for (int j = 0; j < size; j++) {
            arr[j] = j + 1;
        }

        // Search for the last element (worst case)
        int target = size;

        long long checksum = 0;

        auto start = high_resolution_clock::now();

        for (int j = 0; j < repeat; j++) {
            checksum += linearSearch(arr, target);
        }

        auto stop = high_resolution_clock::now();

        // Store result outside the timed section
        resultSink = static_cast<int>(checksum);

        // Calculate total execution time
        auto duration =
            duration_cast<nanoseconds>(stop - start);

        double averageTime =
            static_cast<double>(duration.count()) / repeat;

        cout << size << "\t\t"
             << repeat << "\t\t"
             << averageTime << " ns\n";

        // Save experimental results
        outputFile << size << ","
                   << repeat << ","
                   << averageTime << "\n";
    }

    outputFile.close();

    cout << "\nExperimental results saved to results.csv\n";

    return 0;
}

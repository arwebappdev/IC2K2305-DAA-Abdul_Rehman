
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct Job {
    int id;
    int deadline;
    int profit;
};

// Sort jobs in descending order of profit
bool compare(Job a, Job b) {
    return a.profit > b.profit;
}

void jobSequencing(vector<Job>& jobs, int n) {
    // Sort jobs according to profit
    sort(jobs.begin(), jobs.end(), compare);

    // Find the maximum deadline
    int maxDeadline = 0;

    for (const Job& job : jobs) {
        maxDeadline = max(maxDeadline, job.deadline);
    }

    // Each position represents a time slot
    // -1 means the slot is empty
    vector<int> slots(maxDeadline + 1, -1);

    int totalProfit = 0;
    int jobCount = 0;

    // Schedule each job in the latest available slot
    for (const Job& job : jobs) {
        for (int j = job.deadline; j >= 1; j--) {
            if (slots[j] == -1) {
                slots[j] = job.id;
                totalProfit += job.profit;
                jobCount++;
                break;
            }
        }
    }

    cout << "\nScheduled Jobs:\n";

    for (int i = 1; i <= maxDeadline; i++) {
        if (slots[i] != -1) {
            cout << "Time Slot " << i
                 << ": Job J" << slots[i] << endl;
        } else {
            cout << "Time Slot " << i << ": Empty" << endl;
        }
    }

    cout << "\nTotal Jobs Scheduled: " << jobCount << endl;
    cout << "Maximum Profit: " << totalProfit << endl;
}

int main() {
    int n;

    cout << "Enter number of jobs: ";
    cin >> n;

    if (n <= 0 || n > 100) {
        cout << "Please enter between 1 and 100 jobs." << endl;
        return 0;
    }

    vector<Job> jobs(n);

    cout << "\nEnter deadline and profit for each job:\n";

    for (int i = 0; i < n; i++) {
        jobs[i].id = i + 1;

        cout << "Job J" << i + 1 << " (deadline profit): ";
        cin >> jobs[i].deadline >> jobs[i].profit;

        if (jobs[i].deadline <= 0 || jobs[i].deadline > 1000 ||
            jobs[i].profit < 0) {
            cout << "Invalid deadline or profit." << endl;
            return 0;
        }
    }

    jobSequencing(jobs, n);

    return 0;
}

#include <iostream>
#include <fstream>
#include <vector>
#include <chrono> // Added for time measurement
using namespace std;
using namespace std::chrono;

int max_value = 0;
vector<int> best_solution;

void backtrack(vector<int>& values, vector<int>& weights, vector<int>& solution, int capacity, int current_value, int current_weight, int index) {
    if (index == values.size()) {
        if (current_value > max_value) {
            max_value = current_value;
            best_solution = solution;
        }
        return;
    }

    if (current_weight + weights[index] <= capacity) {
        solution[index] = 1;
        backtrack(values, weights, solution, capacity, current_value + values[index], current_weight + weights[index], index + 1);
    }

    solution[index] = 0;
    backtrack(values, weights, solution, capacity, current_value, current_weight, index + 1);
}

int main() {
    string filepath = "low-dimensional\\f2_l-d_kp_20_878";
    ifstream file(filepath);

    if (!file.is_open()) {
        cout << "Failed to open file." << endl;
        return 0;
    }

    // Read the size and capacity
    int n, c;
    if (!(file >> n >> c))
    {
        cerr << "Failed to read the size and capacity from the file." << endl;
        return 1;
    }

    // Read the values and weights
    vector<int> values(n);
    vector<int> weights(n);
    for (int i = 0; i < n; i++)
    {
        if (!(file >> values[i] >> weights[i]))
        {
            cerr << "Failed to read the values and weights from the file." << endl;
            return 1;
        }
    }

    file.close();

    vector<int> solution(n, 0);

    auto start = high_resolution_clock::now();

    backtrack(values, weights, solution, c, 0, 0, 0);

    auto end = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(end - start);

    /*cout << "0/1 Sequence: [" << endl;
    for (int i = 0; i < n; i++) {
        cout << best_solution[i] << ",";
    }
    cout << "]" << endl;
    */

    cout << "Maximum Value: " << max_value << endl;

    // Print the execution time
    cout << "Execution Time: " << duration.count() << " microseconds" << endl;

    return 0;
}

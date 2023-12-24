#include <iostream>
#include <fstream>
#include <vector>
#include <chrono> // Added for time measurement
using namespace std;
using namespace std::chrono; // Added for time measurement

// Function to solve the 0/1 Knapsack problem using dynamic programming
void knapsack(vector<vector<int>> &dp,int n, int c, vector<int> &values, vector<int> &weights)
{
    // Fill the table in a bottom-up manner
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= c; j++)
        {
            if (weights[i - 1] <= j)
            {
                dp[i][j] = max(values[i - 1] + dp[i - 1][j - weights[i - 1]], dp[i - 1][j]);
            }
            else
            {
                dp[i][j] = dp[i - 1][j];
            }
        }
    }

    // Print the 0/1 sequence
    /*vector<int> selectedItems(n, 0);
    int i = n, j = c;
    while (i > 0 && j > 0)
    {
        if (dp[i][j] != dp[i - 1][j])
        {
            selectedItems[i - 1] = 1;
            j -= weights[i - 1];
        }
        i--;
    }
    cout << "0/1 Sequence: [";
    for (int k = 0; k < selectedItems.size(); k++)
    {
        cout << selectedItems[k];
        if (k != selectedItems.size() - 1)
        {
            cout << ",";
        }
    }
    cout << "]" << endl;
    */

}


int main()
{
    // Read the input file
    string filepath = "large_scale\\knapPI_3_200_1000_1";
    ifstream file(filepath);
    if (!file.is_open())
    {
        cerr << "Failed to open the file." << endl;
        return 1;
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

    // Close the file
    file.close();

    // Create a 2D table to store the maximum values for each subproblem
    vector<vector<int>> dp(n + 1, vector<int>(c + 1, 0));

    // Measure the execution time
    auto start = high_resolution_clock::now();

    // Solve the 0/1 Knapsack problem using dynamic programming
    knapsack(dp,n, c, values, weights);

    auto end = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(end - start);

    // Print the maximum value
    cout << "Maximum Value: " << dp[n][c] << endl;

    // Print the execution time
    cout << "Execution Time: " << duration.count() << " microseconds" << endl;

    return 0;
}
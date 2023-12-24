#include <iostream>
#include <algorithm> // Added for sorting
#include <fstream>
#include <vector>
#include <queue>
#include <chrono> // Added for time measurement
using namespace std;
using namespace std::chrono;

struct Item
{
    int value;
    int weight;
    double density; // value per weight
};

struct Node
{
    int level;
    int value;
    int weight;
    vector<int> solution;
};

bool operator<(const Node &a, const Node &b)
{
    return a.value < b.value;
}

bool compare(Item a, Item b)
{
    return a.density > b.density;
}

int max_value = 0;
vector<int> best_solution;

void branchAndBound(int n,vector<Item>& items, int capacity)
{
    priority_queue<Node> pq;
    sort(items.begin(), items.end(), compare);

    Node root;
    root.level = -1;
    root.value = 0;
    root.weight = 0;
    root.solution = vector<int>(n, 0);
    pq.push(root);

    while (!pq.empty())
    {
        Node current = pq.top();
        pq.pop();

        int level = current.level + 1;
        int value = current.value;
        int weight = current.weight;
        vector<int> solution = current.solution;

        // get a new solution
        if (level == n)
        {
            if (value > max_value)
            {
                max_value = value;
                best_solution = solution;
            }
            continue;
        }

        // Include the item at the current level
        if (weight + items[level].weight <= capacity)
        {
            solution[level] = 1;
            pq.push({level, value + items[level].value, weight + items[level].weight, solution});
        }

        // Exclude the item at the current level, and calculate the remaining maximum value, if it is greater than the current maximum value, then push it to the priority queue
        solution[level] = 0;
        int remaining_capacity = capacity - weight;
        int remaining_max_value = 0;
        for(int i = level+1; i < n; i++)
            if(remaining_capacity >= items[i].weight)
            {
                remaining_capacity -= items[i].weight;
                remaining_max_value += items[i].value;
            }
            else
            {
                remaining_max_value += items[i].density * remaining_capacity;
                break;
            }
        if (value + remaining_max_value > max_value)
            pq.push({level, value, weight, solution});
    }
}

int main()
{
    string filepath = "large_scale\\knapPI_3_200_1000_1";
    ifstream file(filepath);

    if (!file.is_open())
    {
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
    vector<Item> items(n);
    for (int i = 0; i < n; i++)
    {
        if (!(file >> items[i].value >> items[i].weight))
        {
            cerr << "Failed to read the values and weights from the file." << endl;
            return 1;
        }
        items[i].density = (double)items[i].value / items[i].weight;
    }

    file.close();

    auto start = high_resolution_clock::now();

    branchAndBound(n,items, c);

    auto end = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(end - start);

    /*cout << "0/1 Sequence: [";
    for (int i = 0; i < n; i++)
    {
        cout << best_solution[i] << ",";
    }
    cout << "]" << endl;*/

    cout << "Maximum Value: " << max_value << endl;

    // Print the execution time
    cout << "Execution Time: " << duration.count() << " microseconds" << endl;

    return 0;
}

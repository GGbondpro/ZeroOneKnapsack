#include <iostream>
#include <algorithm>
#include <fstream>
#include <vector>
#include <queue>
#include <chrono>
using namespace std;
using namespace std::chrono;

// 物品结构体
struct Item
{
    int value;
    int weight;
    double density;
};
 
// 节点结构体
struct Node
{
    int level;
    int value;
    int weight;
    vector<int> solution;
};

// 答案结构体
struct answer
{
    int solvingtime;
    int maxvalue;
};

// 比较函数，对物品按照单位重量价值从大到小排序
bool compare(Item a, Item b)
{
    return a.density > b.density;
}

// 比较函数，用于节点优先队列的比较
bool operator<(const Node &a, const Node &b)
{
    return a.value < b.value;
}

int max_value;
vector<int> best_solution;

//  best-first search,only left branch limit
void branchAndBound_1(int n, vector<Item> &items, int capacity)
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

        // Include the item at the current level,left branch limit
        if (weight + items[level].weight <= capacity)
        {
            solution[level] = 1;
            pq.push({level, value + items[level].value, weight + items[level].weight, solution});
        }

        // Exclude the item at the current level,no right branch limit
        solution[level] = 0;
        pq.push({level, value, weight, solution});
    }
}


// best-first search, only right branch limit
void branchAndBound_2(int n, vector<Item> &items, int capacity)
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
            if ((value > max_value)&&(weight<= capacity))
            {
                max_value = value;
                best_solution = solution;
            }
            continue;
        }

        // Include the item at the current level,no left branch limit
        solution[level] = 1;
        pq.push({level, value + items[level].value, weight + items[level].weight, solution});

        // Exclude the item at the current level,right branch limit
        // calculate the remaining maximum value, if it is greater than the current maximum value, then push it to the priority queue
        int remaining_capacity = capacity - weight;
        int remaining_max_value = 0;
        for (int i = level + 1; i < n; i++)
            if (remaining_capacity >= items[i].weight)
            {
                remaining_capacity -= items[i].weight;
                remaining_max_value += items[i].value;
            }
            else
            {
                remaining_max_value += items[i].density * remaining_capacity;
                break;
            }
        if (value + remaining_max_value >= max_value)
        {
            solution[level] = 0;
            pq.push({level, value, weight, solution});
        }
    }
}


// best-first search,left and right branch limit
void branchAndBound_3(int n, vector<Item> &items, int capacity)
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

        // Include the item at the current level,left branch limit
        if (weight + items[level].weight <= capacity)
        {
            solution[level] = 1;
            pq.push({level, value + items[level].value, weight + items[level].weight, solution});
        }

        // Exclude the item at the current level,right branch limit
        // calculate the remaining maximum value, if it is greater than the current maximum value, then push it to the priority queue
        int remaining_capacity = capacity - weight;
        int remaining_max_value = 0;
        for (int i = level + 1; i < n; i++)
            if (remaining_capacity >= items[i].weight)
            {
                remaining_capacity -= items[i].weight;
                remaining_max_value += items[i].value;
            }
            else
            {
                remaining_max_value += items[i].density * remaining_capacity;
                break;
            }
        if (value + remaining_max_value >= max_value)
        {
            solution[level] = 0;
            pq.push({level, value, weight, solution});
        }
    }
}

// 给定背包容量c，物品数量n，数据路径filepath，重复求解次数freq，返回解决问题的平均时间、最大价值
answer solveproblem_1(int n, int c, string filepath, int freq = 10)
{
    answer ans;
    // Read the input file
    ifstream file(filepath);
    if (!file.is_open())
    {
        cerr << "Failed to open the file." << endl;
        return ans;
    }

    // Read the size and capacity
    int num, cap;
    if (!(file >> num >> cap))
    {
        cerr << "Failed to read the size and capacity from the file." << endl;
        return ans;
    }

    // Read the values and weights
    vector<Item> items(n);
    for (int i = 0; i < n; i++)
    {
        if (!(file >> items[i].value >> items[i].weight))
        {
            cerr << "Failed to read the values and weights from the file." << endl;
            return ans;
        }
        items[i].density = (double)items[i].value / items[i].weight;
    }
    file.close();

    max_value = 0;

    // Measure the execution time
    int sum = 0;
    for (int i = 0; i < freq; i++)
    {
        auto start = high_resolution_clock::now();
        branchAndBound_1(n, items, c);
        auto end = high_resolution_clock::now();
        auto duration = duration_cast<microseconds>(end - start);
        sum += duration.count();
    }
    int average_duration = sum / freq;

    ans.solvingtime = average_duration;
    ans.maxvalue = max_value;
    return ans;
}

// 给定背包容量c，物品数量n，数据路径filepath，重复求解次数freq，返回解决问题的平均时间、最大价值
answer solveproblem_2(int n, int c, string filepath, int freq = 10)
{
    answer ans;
    // Read the input file
    ifstream file(filepath);
    if (!file.is_open())
    {
        cerr << "Failed to open the file." << endl;
        return ans;
    }

    // Read the size and capacity
    int num, cap;
    if (!(file >> num >> cap))
    {
        cerr << "Failed to read the size and capacity from the file." << endl;
        return ans;
    }

    // Read the values and weights
    vector<Item> items(n);
    for (int i = 0; i < n; i++)
    {
        if (!(file >> items[i].value >> items[i].weight))
        {
            cerr << "Failed to read the values and weights from the file." << endl;
            return ans;
        }
        items[i].density = (double)items[i].value / items[i].weight;
    }
    file.close();

    max_value = 0;

    // Measure the execution time
    int sum = 0;
    for (int i = 0; i < freq; i++)
    {
        auto start = high_resolution_clock::now();
        branchAndBound_2(n, items, c);
        auto end = high_resolution_clock::now();
        auto duration = duration_cast<microseconds>(end - start);
        sum += duration.count();
    }
    int average_duration = sum / freq;

    ans.solvingtime = average_duration;
    ans.maxvalue = max_value;
    return ans;
}

// 给定背包容量c，物品数量n，数据路径filepath，重复求解次数freq，返回解决问题的平均时间、最大价值
answer solveproblem_3(int n, int c, string filepath, int freq = 10)
{
    answer ans;
    // Read the input file
    ifstream file(filepath);
    if (!file.is_open())
    {
        cerr << "Failed to open the file." << endl;
        return ans;
    }

    // Read the size and capacity
    int num, cap;
    if (!(file >> num >> cap))
    {
        cerr << "Failed to read the size and capacity from the file." << endl;
        return ans;
    }

    // Read the values and weights
    vector<Item> items(n);
    for (int i = 0; i < n; i++)
    {
        if (!(file >> items[i].value >> items[i].weight))
        {
            cerr << "Failed to read the values and weights from the file." << endl;
            return ans;
        }
        items[i].density = (double)items[i].value / items[i].weight;
    }
    file.close();

    max_value = 0;

    // Measure the execution time
    int sum = 0;
    for (int i = 0; i < freq; i++)
    {
        auto start = high_resolution_clock::now();
        branchAndBound_3(n, items, c);
        auto end = high_resolution_clock::now();
        auto duration = duration_cast<microseconds>(end - start);
        sum += duration.count();
    }
    int average_duration = sum / freq;

    ans.solvingtime = average_duration;
    ans.maxvalue = max_value;
    return ans;
}



int main()
{

    string infilepath = "large_scale\\knapPI_1_200_1000_1";
    
    // only left branch limit
    string outfilepath_1 = "test_result\\boundary_1.txt";
    std::ofstream outfile1(outfilepath_1);
    outfile1.close();
    outfile1.open(outfilepath_1, std::ios::app);
    for(int i=1;i<=25;i++){
        answer ans = solveproblem_1(i,5002,infilepath,3);
        outfile1 << i <<" "<<5002<<" "<<ans.maxvalue <<" "<<ans.solvingtime<<endl;
    }
    outfile1.close();
    
    // only right branch limit 
    string outfilepath_2 = "test_result\\boundary_2.txt";
    std::ofstream outfile2(outfilepath_2);
    outfile2.close();
    outfile2.open(outfilepath_2, std::ios::app);
    for(int i=1;i<=25;i++){
        answer ans = solveproblem_2(i,5002,infilepath,3);
        outfile2 << i <<" "<<5002<<" "<<ans.maxvalue <<" "<<ans.solvingtime<<endl;
    }
    outfile2.close();

    // left and right limit
    string outfilepath_3 = "test_result\\boundary_3.txt";
    std::ofstream outfile3(outfilepath_3);
    outfile3.close();
    outfile3.open(outfilepath_3, std::ios::app);
    for(int i=1;i<=25;i++){
        answer ans = solveproblem_3(i,5002,infilepath,3);
        outfile3 << i <<" "<<5002<<" "<<ans.maxvalue <<" "<<ans.solvingtime<<endl;
    }
    outfile3.close();


   /*
    answer ans = solveproblem_1(100, 995, infilepath, 1);
    cout << ans.maxvalue << " " << ans.solvingtime << endl;
    */

    return 0;
}

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
            if ((value > max_value) && (weight <= capacity))
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

// test function
// validate t-n
void test_1()
{
    string infilepath = "large_scale\\knapPI_1_200_1000_1";

    // only left branch limit
    string outfilepath_1 = "test_result\\boundary_1_1.txt";
    std::ofstream outfile1(outfilepath_1);
    outfile1.close();
    outfile1.open(outfilepath_1, std::ios::app);
    for (int i = 1; i <= 30; i++)
    {
        answer ans = solveproblem_1(i, 1008 , infilepath, 5);
        outfile1 << i << " " << 1008 << " " << ans.maxvalue << " " << ans.solvingtime << endl;
    }
    outfile1.close();

    // only right branch limit
    string outfilepath_2 = "test_result\\boundary_1_2.txt";
    std::ofstream outfile2(outfilepath_2);
    outfile2.close();
    outfile2.open(outfilepath_2, std::ios::app);
    for (int i = 1; i <= 30; i++)
    {
        answer ans = solveproblem_2(i, 1008 , infilepath, 5);
        outfile2 << i << " " << 1008 << " " << ans.maxvalue << " " << ans.solvingtime << endl;
    }
    outfile2.close();

    // left and right limit
    string outfilepath_3 = "test_result\\boundary_1_3.txt";
    std::ofstream outfile3(outfilepath_3);
    outfile3.close();
    outfile3.open(outfilepath_3, std::ios::app);
    for (int i = 1; i <= 30; i++)
    {
        answer ans = solveproblem_3(i, 1008, infilepath, 5);
        outfile3 << i << " " << 1008 << " " << ans.maxvalue << " " << ans.solvingtime << endl;
    }
    outfile3.close();
}


//三种数据集的对比
void test_2(){
    string infilepath_2 = "large_scale\\knapPI_1_200_1000_1";
    string outfilepath_4 = "test_result\\boundary_2_1.txt";
    std::ofstream outfile4(outfilepath_4);
    outfile4.close();
    outfile4.open(outfilepath_4, std::ios::app);
    for (int i = 1; i <= 200; i++)
    {
        answer ans = solveproblem_3( i, 1008, infilepath_2, 5);
        outfile4 <<  i << " " << 1008 << " " << ans.maxvalue << " " << ans.solvingtime << endl;
    }
    outfile4.close();


    string infilepath_3 = "large_scale\\knapPI_2_200_1000_1";
    string outfilepath_5 = "test_result\\boundary_2_2.txt";
    std::ofstream outfile5(outfilepath_5);
    outfile5.close();
    outfile5.open(outfilepath_5, std::ios::app);
    for (int i = 1; i <= 200; i++)
    {
        answer ans = solveproblem_3( i, 1008, infilepath_3, 5);
        outfile5 <<  i << " " << 1008 << " " << ans.maxvalue << " " << ans.solvingtime << endl;
    }
    outfile5.close();


    string infilepath_4 = "large_scale\\knapPI_3_200_1000_1";
    string outfilepath_6 = "test_result\\boundary_2_3.txt";
    std::ofstream outfile6(outfilepath_6);
    outfile6.close();
    outfile6.open(outfilepath_6, std::ios::app);
    for (int i = 1; i <= 200; i++)
    {
        answer ans = solveproblem_3( i, 1008, infilepath_4, 5);
        outfile6 <<  i << " " << 1008 << " " << ans.maxvalue << " " << ans.solvingtime << endl;
    }
    outfile6.close();
}

void test_contrast(){

    string infilepath_1 = "large_scale\\knapPI_1_200_1000_1";
    string outfilepath_1 = "test_result\\contrast_1_boundary.txt";
    std::ofstream outfile_1(outfilepath_1);  
    outfile_1.close();
    outfile_1.open(outfilepath_1, std::ios::app);
    for (int i = 1; i <= 130; i++)
    {
        answer ans = solveproblem_3( i, 1008, infilepath_1, 1);
        outfile_1 <<  i << " " << 1008 << " " << ans.maxvalue << " " << ans.solvingtime << endl;
    }
    outfile_1.close();


    string infilepath_2 = "large_scale\\knapPI_2_200_1000_1";
    string outfilepath_2 = "test_result\\contrast_2_boundary.txt";
    std::ofstream outfile_2(outfilepath_2);
    outfile_2.close();
    outfile_2.open(outfilepath_2, std::ios::app);
    for (int i = 1; i <= 130; i++)
    {
        answer ans = solveproblem_3( i, 1008, infilepath_2, 1);
        outfile_2 <<  i << " " << 1008 << " " << ans.maxvalue << " " << ans.solvingtime << endl;
    }
    outfile_2.close();


    string infilepath_3 = "large_scale\\knapPI_3_200_1000_1";
    string outfilepath_3 = "test_result\\contrast_3_boundary.txt";
    std::ofstream outfile_3(outfilepath_3);
    outfile_3.close();
    outfile_3.open(outfilepath_3, std::ios::app);
    for (int i = 1; i <= 130; i++)
    {
        answer ans = solveproblem_3( i, 1008, infilepath_3, 1);
        outfile_3 <<  i << " " << 1008 << " " << ans.maxvalue << " " << ans.solvingtime << endl;
    }
    outfile_3.close();

    string infilepath_4 = "large_scale\\knapPI_1_10000_1000_1";
    string outfilepath_4 = "test_result\\contrast_dynamic_boundary_2.txt";
    std::ofstream outfile_4(outfilepath_4);  
    outfile_4.close();
    outfile_4.open(outfilepath_4, std::ios::app);
    for (int i = 1; i <= 1000; i++)
    {
        answer ans = solveproblem_3( i*10, 49877, infilepath_4, 1);
        outfile_4 <<  i*10 << " " << 49877 << " " << ans.maxvalue << " " << ans.solvingtime << endl;
    }
    outfile_4.close();



}

int main()
{
    test_1();   // validate t-n
    //test_2();   // 三种数据集的对比
    //test_contrast();    // 三种算法比较：分支限界

    return 0;
}

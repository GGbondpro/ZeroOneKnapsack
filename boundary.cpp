#include <iostream>
#include <algorithm> 
#include <fstream>
#include <vector>
#include <queue>
#include <chrono> 
using namespace std;
using namespace std::chrono;

struct Item
{
    int value;
    int weight;
    double density; 
};

struct Node
{
    int level;
    int value;
    int weight;
    vector<int> solution;
};

struct answer{
    int solvingtime;
    int maxvalue;
};

int max_value ;
vector<int> best_solution;

bool operator<(const Node &a, const Node &b)
{
    return a.value < b.value;
}

bool compare(Item a, Item b)
{
    return a.density > b.density;
}

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
        if (value + remaining_max_value >= max_value)
            solution[level] = 0;
            pq.push({level, value, weight, solution});
    }
}

//给定背包容量c，物品数量n，数据路径filepath，重复求解次数freq，返回解决问题的平均时间、最大价值
answer solveproblem(int n,int c,string filepath,int freq=10){
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
    for (int i =0;i<freq;i++){
        auto start = high_resolution_clock::now();
        branchAndBound(n,items, c);
        auto end = high_resolution_clock::now();
        auto duration = duration_cast<microseconds>(end - start);
        sum += duration.count();
    }
    int average_duration = sum/freq;

    ans.solvingtime = average_duration;
    ans.maxvalue = max_value;
    return ans;
}



int main()
{
    
    string infilepath = "large_scale\\knapPI_1_100_1000_1";

    /*
    string outfilepath = "test_result\\boundary_1.txt";
    std::ofstream outfile(outfilepath);
    outfile.close();
    outfile.open(outfilepath, std::ios::app);
    for(int i=1;i<=500;i++){
        answer ans = solveproblem(i,5002,infilepath,10);
        outfile << i*2 <<" "<<5002<<" "<<ans.maxvalue <<" "<<ans.solvingtime<<endl;
    }
    outfile.close();
    */

    answer ans = solveproblem(100,995,infilepath,1);
    cout <<ans.maxvalue <<" "<<ans.solvingtime<<endl;
    return 0;
}

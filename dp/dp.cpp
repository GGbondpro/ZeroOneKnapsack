#include <iostream>
#include <fstream>
#include <vector>
#include <chrono> 
using namespace std;
using namespace std::chrono; 

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
}

struct answer{
    int solvingtime;
    int maxvalue;
};
//给定背包容量c，物品数量n，数据路径，返回解决问题的平均时间
answer solveproblem(int n,int c,string filepath){
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
    vector<int> values(n);
    vector<int> weights(n);
    for (int i = 0; i < n; i++)
    {
        if (!(file >> values[i] >> weights[i]))
        {
            cerr << "Failed to read the values and weights from the file." << endl;
            return ans;
        }
    }

    file.close();


    vector<vector<int>> dp(n + 1, vector<int>(c + 1, 0));

    // Measure the execution time
    int sum = 0;
    for (int i =0;i<10;i++){
        auto start = high_resolution_clock::now();
        knapsack(dp,n, c, values, weights);
        auto end = high_resolution_clock::now();
        auto duration = duration_cast<microseconds>(end - start);
        sum += duration.count();
    }
    int average_duration = sum/10;

    ans.solvingtime = average_duration;
    ans.maxvalue = dp[n][c];
    return ans;
}

int main()
{
    string filepath = "input_1000_5000";
    
    //清空
    std::ofstream outfile("output_time_n.txt");
    outfile.close();

    //测试不同的n
    outfile.open("output_time_n.txt", std::ios::app);
    for(int i=1;i<=500;i++){
        answer ans = solveproblem(i*2,5002,filepath);
        outfile << 2*i <<" "<<5002<<" "<<ans.maxvalue <<" "<<ans.solvingtime<<endl;
    }
    outfile.close();


    //清空
    std::ofstream open("output_time_c.txt");
    outfile.close();

    //测试不同的c
    outfile.open("output_time_c.txt", std::ios::app);
    for(int i=1;i<=500;i++){
        answer ans = solveproblem(500,10*i,filepath);
        outfile << 500 <<" "<<10*i<<" "<<ans.maxvalue <<" "<<ans.solvingtime<<endl;
    }
    outfile.close();

    return 0;
}
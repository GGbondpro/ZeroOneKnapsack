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
    for (int i =0;i<freq;i++){
        auto start = high_resolution_clock::now();
        knapsack(dp,n, c, values, weights);
        auto end = high_resolution_clock::now();
        auto duration = duration_cast<microseconds>(end - start);
        sum += duration.count();
    }
    int average_duration = sum/freq;

    ans.solvingtime = average_duration;
    ans.maxvalue = dp[n][c];
    return ans;
}

int main()
{
    string infilepath = "large_scale\\knapPI_1_100_1000_1";
    
    /*
    // t-n
    string outfilepath_1 = "test_result\\dynamic_1.txt";
    std::ofstream outfile(outfilepath_1);
    outfile.close();

    outfile.open(outfilepath_1, std::ios::app);
    for(int i=1;i<=500;i++){
        answer ans = solveproblem(i*2,5002,filepath,10);
        outfile << 2*i <<" "<<5002<<" "<<ans.maxvalue <<" "<<ans.solvingtime<<endl;
    }
    outfile.close();


    // t-c
    sting outfilepath_2 = "test_result\\dynamic_2.txt";
    std::ofstream open(outfilepath_2);
    outfile.close();

    outfile.open(outfilepath_2, std::ios::app);
    for(int i=1;i<=500;i++){
        answer ans = solveproblem(500,10*i,filepath,10);
        outfile << 500 <<" "<<10*i<<" "<<ans.maxvalue <<" "<<ans.solvingtime<<endl;
    }
    outfile.close();
    */

    answer ans = solveproblem(100,995,infilepath,1);
    cout <<ans.maxvalue <<" "<<ans.solvingtime<<endl;
    return 0;
}
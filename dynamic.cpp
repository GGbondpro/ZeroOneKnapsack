#include <iostream>
#include <fstream>
#include <vector>
#include <chrono> 
using namespace std;
using namespace std::chrono; 

// Function to solve the 0/1 Knapsack problem using dynamic programming
void dynamic(vector<vector<int>> &dp,int n, int c, vector<int> &values, vector<int> &weights)
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

// Given the knapsack capacity c, the number of items n, the data file path filepath, and the number of repetitions freq, return the average solving time and the maximum value of the solution
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
        dynamic(dp,n, c, values, weights);
        auto end = high_resolution_clock::now();
        auto duration = duration_cast<microseconds>(end - start);
        sum += duration.count();
    }
    int average_duration = sum/freq;

    ans.solvingtime = average_duration;
    ans.maxvalue = dp[n][c];
    return ans;
}

// test function
// validate t-n
void test_1(){

    string infilepath_1 = "large_scale\\knapPI_1_1000_1000_1";
    string outfilepath_1 = "test_result\\dynamic_1.txt";
    std::ofstream outfile1(outfilepath_1);
    outfile1.close();
    outfile1.open(outfilepath_1, std::ios::app);
    for(int i=1;i<=500;i++){
        answer ans = solveproblem(i*2,5002,infilepath_1,10);
        outfile1 << 2*i <<" "<<5002<<" "<<ans.maxvalue <<" "<<ans.solvingtime<<endl;
    }
    outfile1.close();
}

// validate t-c
void test_2(){
    string infilepath_1 = "large_scale\\knapPI_1_1000_1000_1";
    string outfilepath_2 = "test_result\\dynamic_2.txt";
    std::ofstream outfile2(outfilepath_2);
    outfile2.close();
    outfile2.open(outfilepath_2, std::ios::app);
    for(int i=1;i<=500;i++){
        answer ans = solveproblem(500,10*i,infilepath_1,10);
        outfile2 << 500 <<" "<<10*i<<" "<<ans.maxvalue <<" "<<ans.solvingtime<<endl;
    }
    outfile2.close();
}


// validate t-n, the impact of three types of correlation data on the algorithm
void test_3(){
    string infilepath_2 = "large_scale\\knapPI_1_1000_1000_1";
    string outfilepath_3_1 = "test_result\\dynamic_3_1.txt";
    std::ofstream outfile3(outfilepath_3_1);
    outfile3.close();
    outfile3.open(outfilepath_3_1, std::ios::app);
    for(int i=1;i<=500;i++){
        answer ans = solveproblem(i*2,5002,infilepath_2,10);
        outfile3 << 2*i <<" "<<5002<<" "<<ans.maxvalue <<" "<<ans.solvingtime<<endl;
    }
    outfile3.close();
    
    string infilepath_3 = "large_scale\\knapPI_2_1000_1000_1";
    string outfilepath_3_2 = "test_result\\dynamic_3_2.txt";
    std::ofstream outfile4(outfilepath_3_2);
    outfile4.close();
    outfile4.open(outfilepath_3_2, std::ios::app);
    for(int i=1;i<=500;i++){
        answer ans = solveproblem(i*2,5002,infilepath_3,10);
        outfile4 << 2*i <<" "<<5002<<" "<<ans.maxvalue <<" "<<ans.solvingtime<<endl;
    }
    outfile4.close();

    string infilepath_4 = "large_scale\\knapPI_3_1000_1000_1";
    string outfilepath_3_3 = "test_result\\dynamic_3_3.txt";
    std::ofstream outfile5(outfilepath_3_3);
    outfile5.close();
    outfile5.open(outfilepath_3_3, std::ios::app);
    for(int i=1;i<=500;i++){
        answer ans = solveproblem(2*i,5002,infilepath_4,10);
        outfile5 << 2*i <<" "<<5002<<" "<<ans.maxvalue <<" "<<ans.solvingtime<<endl;
    }
    outfile5.close();
}

// Comparison of three algorithms: dynamic programming
void test_contrast(){
    string infilepath_5 = "large_scale\\knapPI_1_200_1000_1";
    string outfilepath_5 = "test_result\\contrast_1_dynamic.txt";
    std::ofstream outfile6(outfilepath_5);
    outfile6.close();
    outfile6.open(outfilepath_5, std::ios::app);
    for(int i=1;i<=130;i++){
        answer ans = solveproblem(i,1008,infilepath_5,1);
        outfile6 << i <<" "<<1008<<" "<<ans.maxvalue <<" "<<ans.solvingtime<<endl;
    }
    outfile6.close();

    string infilepath_6 = "large_scale\\knapPI_2_200_1000_1";
    string outfilepath_6 = "test_result\\contrast_2_dynamic.txt";
    std::ofstream outfile7(outfilepath_6);
    outfile7.close();
    outfile7.open(outfilepath_6, std::ios::app);
    for(int i=1;i<=130;i++){
        answer ans = solveproblem(i,1008,infilepath_6,1);
        outfile7 << i <<" "<<1008<<" "<<ans.maxvalue <<" "<<ans.solvingtime<<endl;
    }
    outfile7.close();
    

    string infilepath_7 = "large_scale\\knapPI_3_200_1000_1";
    string outfilepath_7 = "test_result\\contrast_3_dynamic.txt";
    std::ofstream outfile8(outfilepath_7);
    outfile8.close();
    outfile8.open(outfilepath_7, std::ios::app);
    for(int i=1;i<=130;i++){
        answer ans = solveproblem(i,1008,infilepath_7,1);
        outfile8 << i <<" "<<1008<<" "<<ans.maxvalue <<" "<<ans.solvingtime<<endl;
    }
    outfile8.close();
    

    string infilepath_8 = "large_scale\\knapPI_1_10000_1000_1";
    string outfilepath_8 = "test_result\\contrast_dynamic_boundary_1.txt";
    std::ofstream outfile9(outfilepath_8);
    outfile9.close();
    outfile9.open(outfilepath_8, std::ios::app);
    for(int i=1;i<=1000;i++){
        answer ans = solveproblem(i*10,49877,infilepath_8,1);
        outfile9 << i*10 <<" "<<49877<<" "<<ans.maxvalue <<" "<<ans.solvingtime<<endl;
    }
    outfile9.close();

}


int main()
{

    //test_1();    //t-n
    //test_2();    //t-c
    //test_3();    //t-n, the impact of three types of correlation data on the algorithm
    test_contrast();    // Comparison of three algorithms: dynamic programming

   return 0;

}
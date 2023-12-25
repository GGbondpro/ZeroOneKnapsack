#include <iostream>
#include <fstream>
#include <vector>
#include <chrono> 
using namespace std;
using namespace std::chrono;

int max_value ;
vector<int> best_solution;

// 对解空间的回溯完全搜索
void backtrack_1(vector<int>& values, vector<int>& weights, vector<int>& solution, int capacity, int current_value, int current_weight, int index) {
    if (index == values.size()) {
        if ((current_value > max_value)&&(current_weight<=capacity)) {
            max_value = current_value;
            best_solution = solution;
        }
        return;
    }

    solution[index] = 1;
    backtrack_1(values, weights, solution, capacity, current_value + values[index], current_weight + weights[index], index + 1);

    solution[index] = 0;
    backtrack_1(values, weights, solution, capacity, current_value, current_weight, index + 1);
}

// 对解空间的回溯剪枝搜索
void backtrack_2(vector<int>& values, vector<int>& weights, vector<int>& solution, int capacity, int current_value, int current_weight, int index) {
    if (index == values.size()) {
        if (current_value > max_value) {
            max_value = current_value;
            best_solution = solution;
        }
        return;
    }

    if (current_weight + weights[index] <= capacity) {
        solution[index] = 1;
        backtrack_2(values, weights, solution, capacity, current_value + values[index], current_weight + weights[index], index + 1);
    }

    solution[index] = 0;
    backtrack_2(values, weights, solution, capacity, current_value, current_weight, index + 1);
}

struct answer{
    int solvingtime;
    int maxvalue;
};

//给定背包容量c，物品数量n，数据路径，返回解决问题的平均时间
answer solveproblem_1(int n,int c,string filepath){
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

    max_value = 0;
    vector<int> solution(n, 0);

    // Measure the execution time
    int sum = 0;
    for (int i =0;i<10;i++){
        auto start = high_resolution_clock::now();
        backtrack_1(values, weights, solution, c, 0, 0, 0);
        auto end = high_resolution_clock::now();
        auto duration = duration_cast<microseconds>(end - start);
        sum += duration.count();
    }
    int average_duration = sum/10;

    ans.solvingtime = average_duration;
    ans.maxvalue = max_value;
    return ans;
}

//给定背包容量c，物品数量n，数据路径，返回解决问题的平均时间
answer solveproblem_2(int n,int c,string filepath){
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

    max_value = 0;
    vector<int> solution(n, 0);

    // Measure the execution time
    int sum = 0;
    for (int i =0;i<10;i++){
        auto start = high_resolution_clock::now();
        backtrack_2(values, weights, solution, c, 0, 0, 0);
        auto end = high_resolution_clock::now();
        auto duration = duration_cast<microseconds>(end - start);
        sum += duration.count();
    }
    int average_duration = sum/10;

    ans.solvingtime = average_duration;
    ans.maxvalue = max_value;
    return ans;
}


int main() {
    string filepath = "large_scale\\knapPI_1_1000_1000_1";
    
    //对解空间的回溯完全搜索
    std::ofstream outfile("test_result\\backtrace_1.txt");
    outfile.close();

    outfile.open("test_result\\backtrace_1.txt", std::ios::app);
    for(int i=7;i<=31;i++){
        answer ans = solveproblem_1(i,5002,filepath);
        outfile << i <<" "<<5002<<" "<<ans.maxvalue <<" "<<ans.solvingtime<<endl;
    }
    outfile.close();



    // 对解空间的回溯剪枝搜索
    std::ofstream open("test_result\\backtrace_2.txt");
    outfile.close();

    outfile.open("test_result\\backtrace_2.txt", std::ios::app);
    for(int i=7;i<=31;i++){
        answer ans = solveproblem_2(i,5002,filepath);
        outfile << i <<" "<<5002<<" "<<ans.maxvalue <<" "<<ans.solvingtime<<endl;
    }
    outfile.close();

    return 0;
}

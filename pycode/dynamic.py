import time
def knapsack(n, c, values, weights):
    dp = [[0] * (c + 1) for _ in range(n + 1)]
    for i in range(1, n + 1):
        for j in range(1, c + 1):
            if weights[i - 1] <= j:
                dp[i][j] = max(values[i - 1] + dp[i - 1][j - weights[i - 1]], dp[i - 1][j])
            else:
                dp[i][j] = dp[i - 1][j]
    return dp[n][c]

# Read the input file
filepath = "large_scale\\knapPI_3_200_1000_1"
with open(filepath, 'r') as file:
    # Read the size and capacity
    n, c = map(int, file.readline().split())

    # Read the values and weights
    values = []
    weights = []
    for _ in range(n):
        value, weight = map(int, file.readline().split())
        values.append(value)
        weights.append(weight)

# Solve the 0/1 Knapsack problem using dynamic programming
start = time.time()
max_value = knapsack(n, c, values, weights)
end = time.time()
execution_time = (end - start) * 1000000

# Print the maximum value
print("Maximum Value:", max_value)

# Print the execution time
print("Execution Time:", execution_time, "microseconds")

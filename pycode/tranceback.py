import time

max_value = 0
best_solution = []

def backtrack(values, weights, solution, capacity, current_value, current_weight, index):
    global max_value, best_solution
    
    if index == len(values):
        if current_value > max_value:
            max_value = current_value
            best_solution = solution.copy()
        return
    
    if current_weight + weights[index] <= capacity:
        solution[index] = 1
        backtrack(values, weights, solution, capacity, current_value + values[index], current_weight + weights[index], index + 1)
    
    solution[index] = 0
    backtrack(values, weights, solution, capacity, current_value, current_weight, index + 1)

def main():
    filepath = "low-dimensional\\f2_l-d_kp_20_878"
    
    try:
        with open(filepath, 'r') as file:
            # Read the size and capacity
            n, c = map(int, file.readline().split())
            
            # Read the values and weights
            values = []
            weights = []
            for _ in range(n):
                v, w = map(int, file.readline().split())
                values.append(v)
                weights.append(w)
            
            solution = [0] * n
            
            start = time.time()
            
            backtrack(values, weights, solution, c, 0, 0, 0)
            
            end = time.time()
            duration = (end - start) * 1000000
            
            print("Maximum Value:", max_value)
            print("Execution Time:", duration, "microseconds")
    
    except FileNotFoundError:
        print("Failed to open file.")

if __name__ == "__main__":
    main()

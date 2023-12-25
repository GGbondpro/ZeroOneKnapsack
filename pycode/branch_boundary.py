## 这个代码山存在问题，需要修改
import heapq
from typing import List

class Item:
    def __init__(self, value: int, weight: int, density: float):
        self.value = value
        self.weight = weight
        self.density = density

class Node:
    def __init__(self, level: int, value: int, weight: int, solution: List[int]):
        self.level = level
        self.value = value
        self.weight = weight
        self.solution = solution

    def __lt__(self, other):
        return self.value < other.value

def compare(a: Item, b: Item) -> bool:
    return a.density > b.density

max_value = 0
def branchAndBound(n: int, items: List[Item], capacity: int):
    max_value = 0
    best_solution = []

    pq = []
    heapq.heapify(pq)

    items.sort(key=compare)

    root = Node(-1, 0, 0, [0] * n)
    heapq.heappush(pq, root)

    while pq:
        current = heapq.heappop(pq)

        level = current.level + 1
        value = current.value
        weight = current.weight
        solution = current.solution.copy()

        if level == n:
            if value > max_value:
                max_value = value
                best_solution = solution
            continue

        if weight + items[level].weight <= capacity:
            solution[level] = 1
            heapq.heappush(pq, Node(level, value + items[level].value, weight + items[level].weight, solution))

        solution[level] = 0
        remaining_capacity = capacity - weight
        remaining_max_value = 0
        for i in range(level + 1, n):
            if remaining_capacity >= items[i].weight:
                remaining_capacity -= items[i].weight
                remaining_max_value += items[i].value
            else:
                remaining_max_value += items[i].density * remaining_capacity
                break

        if value + remaining_max_value > max_value:
            heapq.heappush(pq, Node(level, value, weight, solution))

filepath = "low-dimensional\\f1_l-d_kp_10_269"
with open(filepath, "r") as file:
    lines = file.readlines()

n, c = map(int, lines[2].split())
items = []
for line in lines[4:4+n]:
    value, weight = map(int, line.split())
    density = value / weight
    items.append(Item(value, weight, density))

branchAndBound(n, items, c)

print("Maximum Value:", max_value)

import os
import matplotlib.pyplot as plt
data = []
with open('output.txt', 'r') as file:
    for line in file:
        values = line.split()
        x = int(values[0])
        y = int(values[3])
        data.append((x, y))

x = [d[0] for d in data]
y = [d[1] for d in data]
y = [i / 1000 for i in y]

plt.scatter(x, y, s=1)  
plt.xlabel('n')
plt.ylabel('time / nanosecond')
plt.title('Solving time with number of items')
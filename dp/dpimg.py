# the capacity of the backpack is 5002
import os
import matplotlib.pyplot as plt
data = []
with open('output_time_n.txt', 'r') as file:
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

# Save the plot in the current directory
plt.savefig(os.path.join(os.getcwd(), 'dp_time-n.png'))

plt.show()

# the number of items is 500
data = []
with open('output_time_c.txt', 'r') as file:
    for line in file:
        values = line.split()
        x = int(values[1])
        y = int(values[3])
        data.append((x, y))

x = [d[0] for d in data]
y = [d[1] for d in data]
y = [i / 1000 for i in y]

plt.scatter(x, y, s=1)  
plt.xlabel('c')
plt.ylabel('time / nanosecond')
plt.title('Solving time with backpack capacity')

# Save the plot in the current directory
plt.savefig(os.path.join(os.getcwd(), 'dp_time-c.png'))

plt.show()

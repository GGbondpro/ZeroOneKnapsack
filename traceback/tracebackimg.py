import os
import matplotlib.pyplot as plt
import math
data = []
with open('output_time_n_3.txt', 'r') as file:
    for line in file:
        values = line.split()
        n = int(values[0])
        t = int(values[3])
        data.append((n, t))

n = [d[0] for d in data]
t = [d[1] for d in data]
z = [math.log2(i) if i > 0 else 0 for i in t]  # 计算以2为底的对数


plt.scatter(n, t, s=1)  
plt.xlabel('n')
plt.ylabel('t / nanosecond')
plt.title('Solving time with number of items')
plt.savefig(os.path.join(os.getcwd(), 'backtrace_t-n.png'))
plt.show()


# 绘制z的散点图
plt.scatter(n, z, s=1)  
plt.xlabel('n')
plt.ylabel('z=log2(t)')
plt.title('Log2 of solving time with number of items')
plt.savefig(os.path.join(os.getcwd(), 'backtrace1_log2(t)-n.png'))
plt.show()
import os
import matplotlib.pyplot as plt
import math

# 绘制动态规划算法的时间图表t-n
def plot_dynamic_1():
    # the capacity of the backpack is 5002
    data = []
    with open('test_result\dynamic_1.txt', 'r') as file:
        for line in file:
            values = line.split()
            n = int(values[0])
            t = int(values[3])
            data.append((n, t))

    n = [d[0] for d in data]
    t = [d[1] for d in data]
    t = [i / 1000 for i in t]

    plt.scatter(n, t, s=1)  
    plt.xlabel('n')
    plt.ylabel('t / nanosecond')
    plt.title('Solving time with number of items')

    plt.savefig(os.path.join(os.getcwd(), 'image\\dynamic_1.png'))
    plt.show()


# 绘制动态规划算法的时间图表t-c
def plot_dynamic_2():
    # the number of items is 500
    data = []
    with open('test_result\dynamic_2.txt', 'r') as file:
        for line in file:
            values = line.split()
            c = int(values[1])
            t = int(values[3])
            data.append((c, t))

    c = [d[0] for d in data]
    t = [d[1] for d in data]
    t = [i / 1000 for i in t]

    plt.scatter(c, t, s=1)  
    plt.xlabel('c')
    plt.ylabel('t / nanosecond')
    plt.title('Solving time with backpack capacity')

    plt.savefig(os.path.join(os.getcwd(), 'image\\dynamic_2.png'))

    plt.show()


# 绘制回溯完全搜索算法的时间图表
def plot_backtrack_1():
    data = []
    with open('test_result\\backtrace_1.txt', 'r') as file:
        for line in file:
            values = line.split()
            n = int(values[0])
            t = int(values[3])
            data.append((n, t))

    n = [d[0] for d in data]
    t = [d[1] for d in data]
    z = [math.log2(i) if i > 0 else 0 for i in t]  # 计算以2为底的对数
    t = [i / 1000 for i in t]

    fig, axs = plt.subplots(1, 2, figsize=(10, 5))
    # 绘制t-n的散点图
    axs[0].scatter(n, t, s=1)
    axs[0].set_xlabel('n')
    axs[0].set_ylabel('t / nanosecond')
    axs[0].set_title('backtrack_1:Solving time with number of items')

    # 绘制z-n的散点图
    axs[1].scatter(n, z, s=1)
    axs[1].set_xlabel('n')
    axs[1].set_ylabel('z=log2(t)')
    axs[1].set_title('backtrack_1:Log2 of solving time with number of items')

    plt.tight_layout()  
    plt.savefig(os.path.join(os.getcwd(), 'image\\backtrack_1.png'))
    plt.show()

# 绘制回溯剪枝搜索算法的时间图表
def plot_backtrack_2():
    data = []
    with open('test_result\\backtrace_2.txt', 'r') as file:
        for line in file:
            values = line.split()
            n = int(values[0])
            t = int(values[3])
            data.append((n, t))

    n = [d[0] for d in data]
    t = [d[1] for d in data]
    z = [math.log2(i) if i > 0 else 0 for i in t]  # 计算以2为底的对数
    t = [i / 1000 for i in t]

    fig, axs = plt.subplots(1, 2, figsize=(10, 5))
    # 绘制t-n的散点图
    axs[0].scatter(n, t, s=1)
    axs[0].set_xlabel('n')
    axs[0].set_ylabel('t / nanosecond')
    axs[0].set_title('backtrack_2:Solving time with number of items')

    # 绘制z-n的散点图
    axs[1].scatter(n, z, s=1)
    axs[1].set_xlabel('n')
    axs[1].set_ylabel('z=log2(t)')
    axs[1].set_title('backtrack_2:Log2 of solving time with number of items')

    plt.tight_layout()  
    plt.savefig(os.path.join(os.getcwd(), 'image\\backtrack_2.png'))
    plt.show()

# 绘制两种回溯算法的对比时间图表
def plot_backtrack_3():
    data1 = []
    with open('test_result\\backtrace_1.txt', 'r') as file:
        for line in file:
            values = line.split()
            n = int(values[0])
            t = int(values[3])
            data1.append((n, t))

    n1 = [d[0] for d in data1]
    t1 = [d[1] for d in data1]
    z1 = [math.log2(i) if i > 0 else 0 for i in t1]  # 计算以2为底的对数

    data2 = []
    with open('test_result\\backtrace_2.txt', 'r') as file:
        for line in file:
            values = line.split()
            n = int(values[0])
            t = int(values[3])
            data2.append((n, t))
    
    n2 = [d[0] for d in data2]
    t2 = [d[1] for d in data2]
    z2 = [math.log2(i) if i > 0 else 0 for i in t2]  # 计算以2为底的对数

    plt.scatter(n1, z1, s=1,label='backtrack_1')
    plt.scatter(n2, z2, s=1,label='backtrack_2') 
    plt.xlabel('n')
    plt.ylabel('z=log2(t)')
    plt.title('Log2 of solving time with number of items')
    plt.legend()

    plt.tight_layout()  
    plt.savefig(os.path.join(os.getcwd(), 'image\\backtrack_3.png'))
    plt.show()






#plot_dynamic_1()
#plot_dynamic_2()
#plot_backtrack_1()
#plot_backtrack_2()
#plot_backtrack_3()
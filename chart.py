import os
import matplotlib.pyplot as plt
import math

# 绘制动态规划算法的时间图表t-n，时间单位为纳秒
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
    plt.title('Dynamic:Solving time with number of items')

    plt.savefig(os.path.join(os.getcwd(), 'image\\dynamic_1.png'))
    plt.show()


# 绘制动态规划算法的时间图表t-c，时间单位为纳秒
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
    plt.title('Dynamic:Solving time with backpack capacity')

    plt.savefig(os.path.join(os.getcwd(), 'image\\dynamic_2.png'))

    plt.show()

# 绘制动态规划算法的时间图表t-n，三种不同数据相关性的曲线对比，时间单位为纳秒
def plot_dynamic_3():
    # no correlation
    data1 = []
    with open('test_result\\dynamic_3_1.txt', 'r') as file:
        for line in file:
            values = line.split()
            n = int(values[0])
            t = int(values[3])
            data1.append((n, t))

    n1 = [d[0] for d in data1]
    t1 = [d[1] for d in data1]
    t1 = [i/1000 for i in t1]

    # weak correlation
    data2 = []
    with open('test_result\\dynamic_3_2.txt', 'r') as file:
        for line in file:
            values = line.split()
            n = int(values[0])
            t = int(values[3])
            data2.append((n, t))
    
    n2 = [d[0] for d in data2]
    t2 = [d[1] for d in data2]
    t2 = [i/1000 for i in t2]

    # strong correlation
    data3 = []
    with open('test_result\\dynamic_3_3.txt', 'r') as file: 
        for line in file:
            values = line.split()
            n = int(values[0])
            t = int(values[3])
            data3.append((n, t))
    
    n3 = [d[0] for d in data3]
    t3 = [d[1] for d in data3]
    t3 = [i/1000 for i in t3]

    plt.scatter(n1, t1, s=1,label='no correlation')
    plt.scatter(n2, t2, s=1,label='weak correlation') 
    plt.scatter(n3, t3, s=1,label='strong correlation') 
    plt.xlabel('n')
    plt.ylabel('t / nanosecond')
    plt.title('Dynamic:Log2 of solving time with number of items')
    plt.legend()

    plt.tight_layout()  
    plt.savefig(os.path.join(os.getcwd(), 'image\\dynamic_3.png'))
    plt.show()

# 绘制回溯算法的时间图表，时间单位为纳秒
def plot_backtrack_1():
    data = []
    with open('test_result\\backtrack_1.txt', 'r') as file:
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
    axs[0].set_title('Backtrack:Solving time with number of items')

    # 绘制z-n的散点图
    axs[1].scatter(n, z, s=1)
    axs[1].set_xlabel('n')
    axs[1].set_ylabel('z=log2(t)')
    axs[1].set_title('Backtrack:Log2 of solving time with number of items')

    plt.tight_layout()  
    plt.savefig(os.path.join(os.getcwd(), 'image\\backtrack_1.png'))
    plt.show()

# 绘制最坏情况、回溯法的对比时间图表,这个时间单位为微秒
def plot_backtrack_2():
    # the worst case
    data1 = []
    for n in range(1, 65):
        data1.append((2*n, 2*n))
    n1 = [d[0] for d in data1]
    z1 = [d[1] for d in data1]

    # the actually backtrack
    data2 = []
    with open('test_result\\backtrack_1.txt', 'r') as file:
        for line in file:
            values = line.split()
            n = int(values[0])
            t = int(values[3])
            data2.append((n, t))
    
    n2 = [d[0] for d in data2]
    t2 = [d[1] for d in data2]
    z2 = [math.log2(i) if i > 0 else 0 for i in t2]  # 计算以2为底的对数

    plt.scatter(n1, z1, s=1,label='the worst case')
    plt.scatter(n2, z2, s=1,label='the actually backtrack') 
    plt.xlabel('n')
    plt.ylabel('z=log2(t)')
    plt.title('Log2 of solving time with number of items')
    plt.legend()

    plt.tight_layout()  
    plt.savefig(os.path.join(os.getcwd(), 'image\\backtrack_2.png'))
    plt.show()


# 绘制回溯法，不同数据相关性的曲线
def plot_backtrack_3():
    # no correlation
    data1 = []
    with open('test_result\\backtrack_3_1.txt', 'r') as file:
        for line in file:
            values = line.split()
            n = int(values[0])
            t = int(values[3])
            data1.append((n, t))

    n1 = [d[0] for d in data1]
    t1 = [d[1] for d in data1]
    z1 = [math.log2(i) if i > 0 else 0 for i in t1]  # 计算以2为底的对数

    # weak correlation
    data2 = []
    with open('test_result\\backtrack_3_2.txt', 'r') as file:
        for line in file:
            values = line.split()
            n = int(values[0])
            t = int(values[3])
            data2.append((n, t))
    
    n2 = [d[0] for d in data2]
    t2 = [d[1] for d in data2]
    z2 = [math.log2(i) if i > 0 else 0 for i in t2]  # 计算以2为底的对数

    # strong correlation
    data3 = []
    with open('test_result\\backtrack_3_3.txt', 'r') as file: 
        for line in file:
            values = line.split()
            n = int(values[0])
            t = int(values[3])
            data3.append((n, t))
    
    n3 = [d[0] for d in data3]
    t3 = [d[1] for d in data3]
    z3 = [math.log2(i) if i > 0 else 0 for i in t3]  # 计算以2为底的对数

    plt.scatter(n1, z1, s=1,label='no correlation')
    plt.scatter(n2, z2, s=1,label='weak correlation') 
    plt.scatter(n3, z3, s=1,label='strong correlation') 
    plt.xlabel('n')
    plt.ylabel('z=log2(t)')
    plt.title('Backtrack:Log2 of solving time with number of items')
    plt.legend()

    plt.tight_layout()  
    plt.savefig(os.path.join(os.getcwd(), 'image\\backtrack_3.png'))
    plt.show()

# 绘制分支限界法不同限界条件的时间曲线
def plot_boundary_1():

    # the worst case
    data0 = []
    for n in range(1, 25):
        data0.append((n, n*math.log2(n)))
    n0 = [d[0] for d in data0]
    z0 = [d[1] for d in data0]

    # left limit
    data1 = []
    with open('test_result\\boundary_1_1.txt', 'r') as file:
        for line in file:
            values = line.split()
            n = int(values[0])
            t = int(values[3])
            data1.append((n, t))

    n1 = [d[0] for d in data1]
    t1 = [d[1] for d in data1]
    z1 = [math.log2(i) if i > 0 else 0 for i in t1]  # 计算以2为底的对数

    # right limit
    data2 = []
    with open('test_result\\boundary_1_2.txt', 'r') as file:
        for line in file:
            values = line.split()
            n = int(values[0])
            t = int(values[3])
            data2.append((n, t))
    
    n2 = [d[0] for d in data2]
    t2 = [d[1] for d in data2]
    z2 = [math.log2(i) if i > 0 else 0 for i in t2]  # 计算以2为底的对数

    # left and right limit
    data3 = []
    with open('test_result\\boundary_1_3.txt', 'r') as file: 
        for line in file:
            values = line.split()
            n = int(values[0])
            t = int(values[3])
            data3.append((n, t))
    
    n3 = [d[0] for d in data3]
    t3 = [d[1] for d in data3]
    z3 = [math.log2(i) if i > 0 else 0 for i in t3]  # 计算以2为底的对数

    plt.scatter(n0, z0, s=1,label='the worst case')
    plt.scatter(n1, z1, s=1,label='left limit')
    plt.scatter(n2, z2, s=1,label='right limit') 
    plt.scatter(n3, z3, s=1,label='left and right limit') 
    plt.xlabel('n')
    plt.ylabel('z=log2(t)')
    plt.title('Boundary:Log2 of solving time with number of items')
    plt.legend()

    plt.tight_layout()  
    plt.savefig(os.path.join(os.getcwd(), 'image\\boundary_1.png'))
    plt.show()

# 绘制分支限界算法的在不同数据相关性下的时间曲线
def plot_boundary_2():
    # no correlation
    data1 = []
    with open('test_result\\boundary_2_1.txt', 'r') as file:
        for line in file:
            values = line.split()
            n = int(values[0])
            t = int(values[3])
            data1.append((n, t))

    n1 = [d[0] for d in data1]
    t1 = [d[1] for d in data1]
    z1 = [math.log2(i) if i > 0 else 0 for i in t1]  # 计算以2为底的对数

    # weak correlation
    data2 = []
    with open('test_result\\boundary_2_2.txt', 'r') as file:
        for line in file:
            values = line.split()
            n = int(values[0])
            t = int(values[3])
            data2.append((n, t))
    
    n2 = [d[0] for d in data2]
    t2 = [d[1] for d in data2]
    z2 = [math.log2(i) if i > 0 else 0 for i in t2]  # 计算以2为底的对数

    # strong correlation
    data3 = []
    with open('test_result\\boundary_2_3.txt', 'r') as file: 
        for line in file:
            values = line.split()
            n = int(values[0])
            t = int(values[3])
            data3.append((n, t))
    
    n3 = [d[0] for d in data3]
    t3 = [d[1] for d in data3]
    z3 = [math.log2(i) if i > 0 else 0 for i in t3]  # 计算以2为底的对数

    plt.scatter(n1, z1, s=1,label='no correlation')
    plt.scatter(n2, z2, s=1,label='weak correlation') 
    plt.scatter(n3, z3, s=1,label='strong correlation') 
    plt.xlabel('n')
    plt.ylabel('z=log2(t)')
    plt.title('Boundary:Log2 of solving time with number of items')
    plt.legend()

    plt.tight_layout()  
    plt.savefig(os.path.join(os.getcwd(), 'image\\boundary_2.png'))
    plt.show()




# 绘制三种算法在无相关性数据的表现
def plot_contrast_1():
    # dynamic
    data1 = []
    with open('test_result\\contrast_1_dynamic.txt', 'r') as file:
        for line in file:
            values = line.split()
            n = int(values[0])
            t = int(values[3])
            data1.append((n, t))

    n1 = [d[0] for d in data1]
    t1 = [d[1] for d in data1]
    z1 = [math.log2(i) if i > 0 else 0 for i in t1]  # 计算以2为底的对数

    # backtrack
    data2 = []
    with open('test_result\\contrast_1_backtrack.txt', 'r') as file:
        for line in file:
            values = line.split()
            n = int(values[0])
            t = int(values[3])
            data2.append((n, t))
    
    n2 = [d[0] for d in data2]
    t2 = [d[1] for d in data2]
    z2 = [math.log2(i) if i > 0 else 0 for i in t2]  # 计算以2为底的对数

    # boundary
    data3 = []
    with open('test_result\\contrast_1_boundary.txt', 'r') as file: 
        for line in file:
            values = line.split()
            n = int(values[0])
            t = int(values[3])
            data3.append((n, t))
    
    n3 = [d[0] for d in data3]
    t3 = [d[1] for d in data3]
    z3 = [math.log2(i) if i > 0 else 0 for i in t3]  # 计算以2为底的对数

    plt.scatter(n1, z1, s=1,label='dynamic')
    plt.scatter(n2, z2, s=1,label='backtrack') 
    plt.scatter(n3, z3, s=1,label='boundary') 
    plt.xlabel('n')
    plt.ylabel('z=log2(t)')
    plt.title('Contrast_1:Log2 of solving time with number of items')
    plt.legend()

    plt.tight_layout()  
    plt.savefig(os.path.join(os.getcwd(), 'image\\contrast_1.png'))
    plt.show()

def plot_contrast_2():
    # dynamic
    data1 = []
    with open('test_result\\contrast_2_dynamic.txt', 'r') as file:
        for line in file:
            values = line.split()
            n = int(values[0])
            t = int(values[3])
            data1.append((n, t))

    n1 = [d[0] for d in data1]
    t1 = [d[1] for d in data1]
    z1 = [math.log2(i) if i > 0 else 0 for i in t1]  # 计算以2为底的对数

    # backtrack
    data2 = []
    with open('test_result\\contrast_2_backtrack.txt', 'r') as file:
        for line in file:
            values = line.split()
            n = int(values[0])
            t = int(values[3])
            data2.append((n, t))
    
    n2 = [d[0] for d in data2]
    t2 = [d[1] for d in data2]
    z2 = [math.log2(i) if i > 0 else 0 for i in t2]  # 计算以2为底的对数

    # boundary
    data3 = []
    with open('test_result\\contrast_2_boundary.txt', 'r') as file: 
        for line in file:
            values = line.split()
            n = int(values[0])
            t = int(values[3])
            data3.append((n, t))
    
    n3 = [d[0] for d in data3]
    t3 = [d[1] for d in data3]
    z3 = [math.log2(i) if i > 0 else 0 for i in t3]  # 计算以2为底的对数

    plt.scatter(n1, z1, s=1,label='dynamic')
    plt.scatter(n2, z2, s=1,label='backtrack') 
    plt.scatter(n3, z3, s=1,label='boundary') 
    plt.xlabel('n')
    plt.ylabel('z=log2(t)')
    plt.title('Contrast_2:Log2 of solving time with number of items')
    plt.legend()

    plt.tight_layout()  
    plt.savefig(os.path.join(os.getcwd(), 'image\\contrast_2.png'))
    plt.show()

def plot_contrast_3():
    # dynamic
    data1 = []
    with open('test_result\\contrast_3_dynamic.txt', 'r') as file:
        for line in file:
            values = line.split()
            n = int(values[0])
            t = int(values[3])
            data1.append((n, t))

    n1 = [d[0] for d in data1]
    t1 = [d[1] for d in data1]
    z1 = [math.log2(i) if i > 0 else 0 for i in t1]  # 计算以2为底的对数

    # backtrack
    data2 = []
    with open('test_result\\contrast_3_backtrack.txt', 'r') as file:
        for line in file:
            values = line.split()
            n = int(values[0])
            t = int(values[3])
            data2.append((n, t))
    
    n2 = [d[0] for d in data2]
    t2 = [d[1] for d in data2]
    z2 = [math.log2(i) if i > 0 else 0 for i in t2]  # 计算以2为底的对数

    # boundary
    data3 = []
    with open('test_result\\contrast_3_boundary.txt', 'r') as file: 
        for line in file:
            values = line.split()
            n = int(values[0])
            t = int(values[3])
            data3.append((n, t))
    
    n3 = [d[0] for d in data3]
    t3 = [d[1] for d in data3]
    z3 = [math.log2(i) if i > 0 else 0 for i in t3]  # 计算以2为底的对数

    plt.scatter(n1, z1, s=1,label='dynamic')
    plt.scatter(n2, z2, s=1,label='backtrack') 
    plt.scatter(n3, z3, s=1,label='boundary') 
    plt.xlabel('n')
    plt.ylabel('z=log2(t)')
    plt.title('Contrast_3:Log2 of solving time with number of items')
    plt.legend()

    plt.tight_layout()  
    plt.savefig(os.path.join(os.getcwd(), 'image\\contrast_3.png'))
    plt.show()


def plot_contrast_dynamic_boundary():
    # dynamic
    data1 = []
    with open('test_result\contrast_dynamic_boundary_1.txt', 'r') as file:
        for line in file:
            values = line.split()
            n = int(values[0])
            t = int(values[3])
            data1.append((n, t))

    n1 = [d[0] for d in data1]
    t1 = [d[1] for d in data1]
    z1 = [i/1000 if i > 0 else 0 for i in t1]  

    # boundary
    data2 = []
    with open('test_result\contrast_dynamic_boundary_2.txt', 'r') as file:
        for line in file:
            values = line.split()
            n = int(values[0])
            t = int(values[3])
            data2.append((n, t))
    
    n2 = [d[0] for d in data2]
    t2 = [d[1] for d in data2]
    z2 = [i/1000 if i > 0 else 0 for i in t2]  


    plt.scatter(n1, z1, s=1,label='dynamic')
    plt.scatter(n2, z2, s=1,label='boundary') 
    plt.xlabel('n')
    plt.ylabel('t/nanosecond')
    plt.title('Contrast:Log2 of solving time with number of items')
    plt.legend()

    plt.tight_layout()  
    plt.savefig(os.path.join(os.getcwd(), 'image\\contrast_dynamic_boundary.png'))
    plt.show()






#plot_dynamic_1()
#plot_dynamic_2()
#plot_dynamic_3()
    

#plot_backtrack_1()
#plot_backtrack_2()
#plot_backtrack_3()


#plot_boundary_1()
#plot_boundary_2()

#plot_contrast_1()
#plot_contrast_2()
#plot_contrast_3()
    
plot_contrast_dynamic_boundary()
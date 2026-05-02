import numpy as np
import matplotlib.pyplot as plt
import scipy as sc

def graph_labels(x, y):
    for x, y in zip(x, y):
        if y != 0:
            plt.text(x, y, f"{y:.2f}", ha='center', va='bottom')

# threads = [1, 2, 4, 8, 16]
# mem_per_core = ["64MB", "128MB", "512MB", "1GB", "1.5GB", "2GB"]
# lines_read = [1000, 10000, 100000, 1000000]
# node_num = [1, 2, 4, 8]
cpus_per_task = [1, 2, 4, 8, 16]

# threads_test1 = [np.nan, 22.758, 22.496, 56.55, np.nan]
# threads_test2 = [246.92, 124.364, 130.602, 236.36, np.nan]
# mem_per_core_test1 = [np.nan, np.nan, 4.342, 4.326, 4.288, 4.068]
# mem_per_core_test2 = [np.nan, np.nan, 0.492, 0.49, 0.488, 0.49]
# num_lines_test1 = [0.03, 0.062, 0.482, np.nan]
# num_lines_test2 = [0.034, 0.09, 0.614, np.nan]
# node_num_test1 = [2.908, np.nan, np.nan, np.nan]
# node_num_test2 = [1.89, 3.852, 4.642, np.nan]
cpus_per_task_test1 = [97.168, 2.542, 2.366, 2.044, 2.072]
cpus_per_task_test2 = [8.074, 6.164, 4.246, np.nan, np.nan]

# graph_labels(threads, threads_test1)
# plt.plot(threads, threads_test1, marker='o')
# plt.xlabel('Number of Threads')
# plt.ylabel('Time (seconds)')
# plt.title('Thread scaling (4GB memory, 500000 Lines read, 2 nodes)')
# plt.grid(True)
# plt.savefig("Threads_test1.png")
# plt.show()

# graph_labels(threads, threads_test2)
# plt.plot(threads, threads_test2, marker='o')
# plt.xlabel('Number of Threads')
# plt.ylabel('Time (seconds)')
# plt.title('Thread scaling (3G memory, 1000000 Lines read, 1 node)')
# plt.grid(True)
# plt.savefig("Threads_test2.png")
# plt.show()

# graph_labels(mem_per_core, mem_per_core_test1)
# plt.plot(mem_per_core, mem_per_core_test1, marker='o')
# plt.xlabel('Memory Per Core')
# plt.ylabel('Time (seconds)')
# plt.title('Memory scaling (8 CPUs, 1000000 Lines)')
# plt.grid(True)
# plt.savefig("Mem_test1.png")
# plt.show()

# graph_labels(mem_per_core, mem_per_core_test2)
# plt.plot(mem_per_core, mem_per_core_test2, marker='o')
# plt.xlabel('Memory Per Core')
# plt.ylabel('Time (seconds)')
# plt.title('Memory scaling (2 CPUs, 100000 Lines)')
# plt.grid(True)
# plt.savefig("Mem_test2.png")
# plt.show()

# plt.figure()
# plt.plot(lines_read, num_lines_test1, marker='o')
# graph_labels(lines_read, num_lines_test1)
# plt.xlabel('Number of lines read')
# plt.ylabel('Time (seconds)')
# plt.title('Number of lines read scaling (4 CPUs, 512MB)')
# plt.grid(True)
# plt.xscale('log')
# plt.savefig("Lines_read_test1.png")
# plt.show()

# plt.figure()
# plt.plot(lines_read, num_lines_test2, marker='o')
# graph_labels(lines_read, num_lines_test2)
# plt.xlabel('Number of lines read')
# plt.ylabel('Time (seconds)')
# plt.title('Number of lines read scaling (1 CPUs, 2GB)')
# plt.grid(True)
# plt.xscale('log')
# plt.savefig("Lines_read_test2.png")
# plt.show()

# plt.figure()
# plt.plot(node_num, node_num_test1, marker='o')
# graph_labels(node_num, node_num_test1)
# plt.xlabel('Number of nodes')
# plt.ylabel('Time (seconds)')
# plt.title('Performance of different numbers of nodes (1 thread, 1GB, 100000 lines)')
# plt.grid(True)
# plt.xticks(node_num)
# plt.savefig("Num_nodes_1.png")
# plt.show()

# plt.figure()
# plt.plot(node_num, node_num_test2, marker='o')
# graph_labels(node_num, node_num_test2)
# plt.xlabel('Number of nodes')
# plt.ylabel('Time (seconds)')
# plt.title('Performance of different numbers of nodes (4 thread, 512MB, 10000 lines)')
# plt.grid(True)
# plt.xticks(node_num)
# plt.savefig("Num_nodes_2.png")
# plt.show()

plt.figure()
plt.plot(cpus_per_task, cpus_per_task_test1, marker='o')
graph_labels(cpus_per_task, cpus_per_task_test1)
plt.xlabel('CPUs per task')
plt.ylabel('Time (seconds)')
plt.title('Scaling for the number of CPUs (1.5G, 500000 Lines)')
plt.grid(True)
plt.xticks(cpus_per_task)
plt.savefig("CPUs_per_task_test1.png")
plt.show()

plt.figure()
plt.plot(cpus_per_task, cpus_per_task_test2, marker='o')
graph_labels(cpus_per_task, cpus_per_task_test2)
plt.xlabel('CPUs per task')
plt.ylabel('Time (seconds)')
plt.title('Scaling for the number of CPUs (4G, 1000000 Lines)')
plt.grid(True)
plt.xticks(cpus_per_task)
plt.savefig("CPUs_per_task_test2.png")
plt.show()
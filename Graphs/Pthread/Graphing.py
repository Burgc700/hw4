import numpy as np
import matplotlib.pyplot as plt
import scipy as sc

def graph_labels(x, y):
    for x, y in zip(x, y):
        if y != 0:
            plt.text(x, y, f"{y:.2f}", ha='center', va='bottom')

threads = [1, 2, 4, 8, 16]
mem_per_core = ["64MB", "128MB", "512MB", "1GB", "1.5GB", "2GB"]
lines_read = [1000, 10000, 100000, 1000000]

threads_test1 = [np.nan, 2.596, 2.496, 2.4944, 2.3994]
threads_test2 = [282.6546, 5.4648, 5.1264, 4.6812, np.nan]
mem_per_core_test1 = [np.nan, 0.4938, 0.4948, 0.4938, 0.49, 0.493]
mem_per_core_test2 = [0.494, 0.4806, 0.483, 0.485, 0.4876, np.nan]
num_lines_test1 = [0.0082, 0.0546, 0.4886, 4.8914]
num_lines_test2 = [0.0278, 0.0552, 0.4908, 4.7352]

# graph_labels(threads, threads_test1)
# plt.plot(threads, threads_test1, marker='o')
# plt.xlabel('Number of Threads')
# plt.ylabel('Time (seconds)')
# plt.title('Thread scaling (1G memory, 500000 Lines read)')
# plt.grid(True)
# plt.savefig("Threads_test1.png")
# plt.show()

# graph_labels(threads, threads_test2)
# plt.plot(threads, threads_test2, marker='o')
# plt.xlabel('Number of Threads')
# plt.ylabel('Time (seconds)')
# plt.title('Thread scaling (3G memory, 1000000 Lines read)')
# plt.grid(True)
# plt.savefig("Threads_test2.png")
# plt.show()

# graph_labels(mem_per_core, mem_per_core_test1)
# plt.plot(mem_per_core, mem_per_core_test1, marker='o')
# plt.xlabel('Memory Per Core')
# plt.ylabel('Time (seconds)')
# plt.title('Memory scaling (4 threads, 100000 Lines read)')
# plt.grid(True)
# plt.savefig("Mem_test1.png")
# plt.show()

# graph_labels(mem_per_core, mem_per_core_test2)
# plt.plot(mem_per_core, mem_per_core_test2, marker='o')
# plt.xlabel('Memory Per Core')
# plt.ylabel('Time (seconds)')
# plt.title('Memory scaling (16 threads, 100000 Lines read)')
# plt.grid(True)
# plt.savefig("Mem_test2.png")
# plt.show()

plt.figure()
plt.plot(lines_read, num_lines_test1, marker='o')
graph_labels(lines_read, num_lines_test1)
plt.xlabel('Number of lines read')
plt.ylabel('Time (seconds)')
plt.title('Number of lines read scaling (4 threads, 1G)')
plt.grid(True)
plt.xscale('log')
plt.savefig("Lines_read_test1.png")
plt.show()

plt.figure()
plt.plot(lines_read, num_lines_test2, marker='o')
graph_labels(lines_read, num_lines_test2)
plt.xlabel('Number of lines read')
plt.ylabel('Time (seconds)')
plt.title('Number of lines read scaling (16 threads, 512MG)')
plt.grid(True)
plt.xscale('log')
plt.savefig("Lines_read_test2.png")
plt.show()


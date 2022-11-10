import matplotlib.pyplot as plt
import numpy as np
import copy
import matplotlib


file1 = open('cpuMonitor.txt', 'r')
Lines = file1.readlines()


y = []
x= []
counter = 0
for line in Lines:
    print(line)# 40 coores
    y.append(float(line.split("\n")[0])* 40 / 100)
    x.append(counter)
    counter = counter + 1

for i in range(0, len(x)):
    x[i] = i / len(x) * 100 



y2 = [0.2, 0.3, 0.4, 0.3, 0.2, 0.2, 0.4, 0.3, 0.2, 0.3, 0.2, 0.3, 0.3, 0.2, 0.3, 0.2, 0.3, 0.4, 0.4, 0.3, 0.3, 0.3, 0.5, 0.4, 0.4, 0.3, 0.4, 0.4, 0.4, 0.2, 0.3, 0.4, 0.3, 0.2, 0.3, 0.3, 0.3, 0.3, 0.3, 0.3, 0.3, 0.3, 0.2, 0.3, 0.2, 0.2, 0.3, 0.3, 0.3, 0.3, 0.2, 0.1, 0.1, 0.1, 0.1, 0.1, 0.2, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.2, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.2, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1]

for i in range(0, len(y2)):
    y2[i] = y2[i] * 40 / 100# 40 coores
x2 = []
for i in range(0, len(y2)):
    x2.append(i / len(y2) * 100)
print(y)




font = {'family' : 'normal',
        'size'   :22}

matplotlib.rc('font', **font)

plt.figure("CPU Usage")
#plt.title("CPU  vs. Time")
ax = plt.gca()
#sets the ratio to 5
ax.set_aspect(5)
plt.xlabel('Time (% of Execution)', fontsize=22) 
plt.ylabel('CPU Usage (# of CPU Cores)', fontsize=22) 
plt.plot(x,y, "-",label = "Baseline CPU Usage", linewidth=2)
plt.plot(x2,y2, "-",label = "SLAM-Share CPU Usage", linewidth=2)

#plt.plot(x, ".--",label = "time (s)")
plt.legend()
plt.show()
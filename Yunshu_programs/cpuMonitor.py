import matplotlib.pyplot as plt 
from matplotlib.animation import FuncAnimation
from psutil import cpu_percent
import psutil
cpu_percent()


#print("psutil.cpu_percent(interval=2) = %s" % (psutil.cpu_percent(interval=2),))

#print("psutil.cpu_percent(interval=2) = %s" % (psutil.cpu_percent(interval=2),))

# print("The number of CPUs is : %s" % (psutil.cpu_count(), ))
# print("The CPU utilization of all the CPUs is: %s" % (psutil.cpu_percent(interval=2, percpu=True), ))
resultSava_file = open("cpuMonitor.txt", "w")


print("cpu_percent(): ", cpu_percent())


frame_len = 200
fig = plt.figure(figsize = (8,3))
y = []
def animate(i):
	cpu = cpu_percent()
	y.append(cpu)
	print(cpu)
	resultSava_file.write(str(cpu) + "\n")

	if len(y) <= frame_len:
		plt.cla()
		plt.plot(y, 'r', label = 'Real-Time CPU Usage')
	else:
		plt.cla()
		plt.plot(y[-frame_len:], 'r', label = "Real-Time CPU Usage")

	plt.ylim(0,100)
	plt.xlabel('Time(s)')
	plt.ylabel('CPU Usage (%)')
	plt.legend(loc = 'upper right')
	plt.tight_layout()

ani = FuncAnimation(plt.gcf(), animate, interval = 1000)
plt.show()
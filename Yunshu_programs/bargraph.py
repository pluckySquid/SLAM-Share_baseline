# Import Library


import matplotlib.pyplot as plt
import numpy as np
from matplotlib.pyplot import figure

# Define Data
plt.rcParams.update({'font.size': 12})


Class = ["Baseline", "SLAM-Share"]
#Boys = [15, 20, 16, 18, 25]
#Girls = [10, 12, 5, 9, 15]
Gap = np.array([5000,0])
serialization = np.array([78,0])
transmit = np.array([66,0])
Deserialization = np.array([391,0])
merge = np.array([2339,0])
transmitII = np.array([6.4,0])
BuildSmallMap = np.array([110,0])
serialization2 = np.array([23, 0])
LoadSmallMap = np.array([19.8,0])


encoding = np.array([0, 3])
#1.1M/sec is for 30 FPS, so for each frame, the size is 1.1/30 = 0.0367M, transmition time = 0.0367M/1G = 0
tranmit_Share = np.array([0, 0])
merge_Share = np.array([0, 190])
sendPose = np.array([0, 0.05])
#rtt min/avg/max/mdev = 0.064/0.107/0.178/0.023 ms



w = 0.6




plt.bar(Class, Gap, color='cyan', label='hold-down Time')
plt.bar(Class, serialization, bottom=Gap, color = 'purple', label='serialization')
plt.bar(Class, transmit, bottom=Gap + serialization,color='green', label='transmit')
plt.bar(Class, Deserialization, bottom=Gap + serialization + transmit, label='deserialization')
plt.bar(Class, merge, bottom=Gap + serialization + transmit + Deserialization, color='yellow', label='map merging')
plt.bar(Class, BuildSmallMap, bottom=Gap + serialization + transmit + Deserialization + merge, color = 'pink', label='data processing')
plt.bar(Class, transmitII, bottom=Gap + serialization + transmit + Deserialization + merge + BuildSmallMap, color='green')
plt.bar(Class, serialization2, bottom=Gap + serialization + transmit + Deserialization + merge + BuildSmallMap + transmitII, color='purple')
plt.bar(Class, LoadSmallMap, bottom=Gap + serialization + transmit + Deserialization + merge +BuildSmallMap + transmitII + serialization2, color='red' )


plt.bar(Class, encoding, bottom=Gap + serialization + transmit + Deserialization + merge + transmitII + BuildSmallMap+ serialization2 + LoadSmallMap, label='encoding')
plt.bar(Class, tranmit_Share, bottom=Gap + serialization + transmit + Deserialization + merge + transmitII + BuildSmallMap+ serialization2 + LoadSmallMap + encoding, color='green')
plt.bar(Class, merge_Share, bottom=Gap + serialization + transmit + Deserialization + merge + transmitII + BuildSmallMap + serialization2+ LoadSmallMap + encoding + tranmit_Share,color='yellow')
plt.bar(Class, sendPose, bottom=Gap + serialization + transmit + Deserialization + merge + transmitII + BuildSmallMap + serialization2+ LoadSmallMap + encoding + tranmit_Share + merge_Share, color='red', label='send device pose')


plt.xlabel("Method")
plt.ylabel("Time (ms)")
     
# Add legend
     
plt.legend(loc=1)
# Display

plt.show()

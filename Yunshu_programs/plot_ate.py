import os
import matplotlib.pyplot as plt
import numpy as np
import math
import sys


#y = [0.138499, 0.212135, 0.076227, 0.247870, 0.305510, 0.335415, 0.254689, 0.142917]
#red = [30, 33, 28, 37, 38, 37, 40, 37]
##blue = [26, 37, 36, 38, 43, 42, 47, 45]
#sum_list = [a + b for a, b in zip(red, blue)]
#Overlaps
y = [0.087, 0.104, 0.0918, 0.0895, 0, 0.09651, 0.1203, 0.089534]
x = [1,2,3,4,5,6,7,8]

#Intersection
y1 = [0.255634, 0.310586, 0.186039, 0.3538, 0.120688,0,0,0]
x1 = [1,2,3,4,5]


y2 = [0.177232, 0.177232, 0.144054, 0.3538, 0.120688,0,0,0]
x2 = [1,2,3,4,5]
plt.title("Ate vs. Overlaps" )
plt.title("keyframes from map A vs time" )

#figure1 = plt.plot(x, y, ".")
#figure1 = plt.plot(sum_list, y, ".")
#plt.xlabel("images that are deleted")

x = [0,1,2,3,4,5.19,    5.2,6.2, 7.2, 8.2, 9.2,  10.29, 10.3,      11.3, 12.3, 13.3, 14.3,  15.49, 15.5,   16.5 ,17.5, 18.5,19.49, 20.49, 20.5,  21, 22.5, 23.5, 24.5]
y = [0,0,0,0,0,0,    15,15,15,15,15,15,    25,25,25,25,25,25, 40,40,40,40,40,40, 66,66,66,66,66]

x = [1.05, 1.08, 0.78, 2.23, 3.25, 2.55, 4.46, 4.55, 3.76, 5.82, 2.51, 3.95, 2.64]
y = 
plt.xlabel("time")
plt.ylabel("keyframes")
plt.plot(x, y)
plt.show()

X_axis = np.arange(len(x))
plt.xlabel("Overlaps Number")

plt.xlabel("Intersection/Overlap Number")
plt.ylabel("Ate")
plt.bar(X_axis - 0.2, y, 0.4, label = "Overlap")
plt.bar(X_axis +0.2, y1, 0.4, label = "Intersection")

plt.xticks(X_axis, x)
plt.legend()
plt.show()
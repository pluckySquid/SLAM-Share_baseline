import matplotlib.pyplot as plt
import numpy as np
import copy
import csv
import matplotlib



y_half_bandwidth = [0, 0.031263, 0.010462, 0.009079, 0.022687, 0.022687, 0.039291, 0.039701, 0.039982, 0.069601, 0.07173, 0.07964, 0.07815, 0.073716, 0.073385]
x= [0, 5, 10, 15, 20, 25, 30, 35, 40, 45, 50, 55, 60, 65, 70]
y_Delay = [ 0, 0.010828, 0.030917, 0.021942, 0.017166, 0.030599, 0.033593, 0.045212, 0.045212, 0.063112, 0.067473, 0.069337, 0.07079, 0.068478, 0.067049]
#y_Delay = [0, 0.031263, 0.010462, 0.009079, 0.022687, 0.022687, 0.039291, 0.039291, 0.039982, 0.069601, 0.07173, 0.07964, 0.07815, 0.073716, 0.073385]
y_Delay_LastFiveSec = [0, 0.010828, 0.031664, 0.026006, 0.01739, 0.046868, 0.074274, 0.101627, 0.101627, 0.127976, 0.10501, 0.099184, 0.053236, 0.034903, 0.053458]

y_half_bandwidth_lastFiveSec = [0, 0.031263, 0.006822, 0.006193, 0.029598, 0.029598, 0.093866, 0.093866, 0.068971, 0.114411, 0.070194, 0.061788, 0.069199, 0.069002, 0.071196]



y_baseline = [0, 0.010447, 0.030979, 0.029643, 0.038493, 0.051556, 0.050518, 0.049993, 0.05199, 0.082864, 0.091969, 0.090232, 0.085332, 0.083015, 0.079978]
y_baseline_lastFiveSec = [0,  0.010447, 0.036656, 0.009366, 0.04209, 0.013574, 0.049209, 0.063197, 0.063852, 0.175159, 0.078534, 0.060727, 0.064102, 0.062013, 0.050921]



y_noTC = [0, 0.027108, 0.032307, 0.025914, 0.025239, 0.026697, 0.027984, 0.034999, 0.054371, 0.052951, 0.052051, 0.04616, 0.050578, 0.048797, 0.046036]
y_noTC_lastFiveSec = [0, 0.027108, 0.010252, 0.007838, 0.007746, 0.039628, 0.033055, 0.07386, 0.049485, 0.045278, 0.037176, 0.085088, 0.025195, 0.042178, 0.038468]




y2 = [0.2, 0.3, 0.4, 0.3, 0.2, 0.2, 0.4, 0.3, 0.2, 0.3, 0.2, 0.3, 0.3, 0.2, 0.3, 0.2, 0.3, 0.4, 0.4, 0.3, 0.3, 0.3, 0.5, 0.4, 0.4, 0.3, 0.4, 0.4, 0.4, 0.2, 0.3, 0.4, 0.3, 0.2, 0.3, 0.3, 0.3, 0.3, 0.3, 0.3, 0.3, 0.3, 0.2, 0.3, 0.2, 0.2, 0.3, 0.3, 0.3, 0.3, 0.2, 0.1, 0.1, 0.1, 0.1, 0.1, 0.2, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.2, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.2, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1]

for i in range(0, len(y2)):
    y2[i] = y2[i] * 40 / 100# 40 coores
x2 = []
for i in range(0, len(y2)):
    x2.append(i / len(y2) * 100)







# plt.figure("Baesline Bandwidth")
# #plt.title("CPU  vs. Time")
# plt.xlabel('Time (s)') 
# plt.ylabel('ATE (m)') 
# plt.plot(x,y_baseline, "x-",label = "MH05 Baseline Bandwidth")
# plt.plot(x,y_baseline_lastFiveSec, "x-",label = "MH05 Baseline Bandwidth Last Five Second")
# plt.legend()
# #plt.show()







# plt.figure("Baesline no TC")
# plt.xlabel('Time (s)') 
# plt.ylabel('ATE (m)') 
# plt.plot(x,y_noTC, "x-",label = "MH05 Baseline no TC")
# plt.plot(x,y_noTC_lastFiveSec, "x-",label = "MH05 Baseline no TC Last Five Second")
# plt.legend()
# #plt.show()


# plt.figure("ATE")
# #plt.title("CPU  vs. Time")
# plt.xlabel('Time (s)') 
# plt.ylabel('ATE (m)') 
# plt.plot(x,y_Delay, ".-",label = "delay")
# plt.plot(x,y_Delay_LastFiveSec, "--",label = "last five second of delay")
# plt.legend()
# #plt.show()



























font = {'family' : 'normal',
        'size'   :15}

matplotlib.rc('font', **font)





time = []
value = []
file_data = open('ORB-SLAM.csv')
l=[]
for row in file_data:
	if len(row) == 2:
		continue
	print(len(row))
	r = list(np.fromstring(row, sep=","))
	print(r)
	time.append(r[0])
	value.append(float(r[1]) * 100) 
	    
time_Share = []
value_Share = []
file_data = open('slam-share.csv')
l=[]
for row in file_data:
	if len(row) <= 2:
		continue
	print(len(row))
	r = list(np.fromstring(row, sep=","))
	print(r)
	time_Share.append(r[0])
	value_Share.append(float(r[1]) * 100) 
	    






for i in range(0, len(y_noTC_lastFiveSec)):
	y_noTC_lastFiveSec[i] = y_noTC_lastFiveSec[i] * 100
for i in range(0, len(y_half_bandwidth_lastFiveSec)):
	y_half_bandwidth_lastFiveSec[i] = y_half_bandwidth_lastFiveSec[i] * 100
for i in range(0, len(y_Delay_LastFiveSec)):
	y_Delay_LastFiveSec[i] = y_Delay_LastFiveSec[i] * 100


Shortterm_noTC_Share = [0, 0.020591, 0.02788, 0.015471, 0.017875, 0.019986, 0.023663, 0.017325, 0.024623, 0.022641, 0.010951, 0.008992, 0.017036, 0.018556, 0.003669]

for i in range(0, len(Shortterm_noTC_Share)):
	Shortterm_noTC_Share[i] = Shortterm_noTC_Share[i] * 100
Shortterm_delay_Share = [0, 0.030385
, 0.035221
, 0.015297
, 0.018228
, 0.02701
, 0.02384
, 0.019418
, 0.028454
, 0.027324
, 0.026505
, 0.013312
, 0.017972
, 0.02148
, 0.006913]
for i in range(0, len(Shortterm_delay_Share)):
	Shortterm_delay_Share[i] = Shortterm_delay_Share[i] * 100
plt.figure("Short Term Delay Effect")
#plt.title("CPU  vs. Time")
plt.xlabel('Time (s)', fontsize=18) 
plt.ylabel('Short-term ATE (cm)', fontsize=18 )
plt.ylim([0, 13])

plt.plot(x,y_noTC_lastFiveSec, "x--",label = "Baseline \n(no delay)", linewidth=2.5)
plt.plot(x,y_Delay_LastFiveSec, ".--",label = "Baseline \n(300 ms \ndelay)", linewidth=2.5)


plt.plot(x,Shortterm_noTC_Share, "x-",label = "SLAM-Share \n(no delay)", linewidth=3)
plt.plot(x,Shortterm_delay_Share, ".-",label = "SLAM-Share \n(300 ms \ndelay)", linewidth=3)
leg = plt.legend()
for text in leg.get_texts():
    text.set_fontsize(50)
plt.setp(leg.get_texts(), fontsize='x-large')

plt.xticks(size = 15)
plt.yticks(size = 15)
plt.legend()
plt.show()



#plot3
#Slam-Share short-term with half-bandwidth
# font = {'family' : 'normal',
#         'size'   :13.5}

matplotlib.rc('font', **font)
Shortterm_Half_Share = [0 , 0.007155
, 0.032882
, 0.019889
, 0.01809
, 0.017138
, 0.019563
, 0.017291
, 0.016245
, 0.013051
, 0.011866
, 0.017552
, 0.019955
, 0.012307
, 0.002894]
for i in range(0, len(Shortterm_Half_Share)):
	Shortterm_Half_Share[i] = Shortterm_Half_Share[i] * 100
plt.figure("Short Term half-bandwidth")
#plt.title("CPU  vs. Time")
plt.xlabel('Time (s)', fontsize=18) 
plt.ylabel('Short-term ATE (cm)', fontsize=18) 
plt.ylim([0, 13])


plt.plot(x,y_noTC_lastFiveSec, "x--",label = "Baseline \n(18.7 Mbit/s)", linewidth=2.5)
plt.plot(x,y_half_bandwidth_lastFiveSec, ".--",label = "Baseline \n(9.4 Mbit/s)", linewidth=2.5)

plt.plot(x,Shortterm_noTC_Share, "x-",label = "SLAM-Share \n(18.7 Mbit/s)", linewidth=3)
plt.plot(x,Shortterm_Half_Share, ".-", color = 'y', label = "SLAM-Share \n(9.4 Mbit/s)", linewidth=3)
plt.xticks(size = 15)
plt.yticks(size = 15)
plt.legend()
plt.show()




IMU_Delay_Share = [0.001586, 0.030302, 0.057152, 0.065210, 0.067756, 0.066483, 0.060422, 0.057238, 0.058364,0.064466,0.064267,0.065261,0.066920,0.066781,0.066039,]
for i in range(0, len(IMU_Delay_Share)):
	IMU_Delay_Share[i] = IMU_Delay_Share[i] * 100

time_Share_half_bandwidth = []
value_Share_half_bandwidth = []
file_data = open('half_bandwidth.csv')
l=[]
for row in file_data:
	if len(row) <= 2:
		continue
	print(len(row))
	r = list(np.fromstring(row, sep=","))
	print(r)
	time_Share_half_bandwidth.append(r[0])
	value_Share_half_bandwidth.append(float(r[1]) * 100)




Cumulative_time_Share_Delay = []
Cumulative_value_Share_Delay = []
file_data = open('300ms_delay_cumulative.csv')
l=[]
for row in file_data:
	if len(row) <= 2:
		continue
	print(len(row))
	r = list(np.fromstring(row, sep=","))
	print(r)
	Cumulative_time_Share_Delay.append(r[0])
	Cumulative_value_Share_Delay.append(float(r[1]) * 100)
	if(r[0] > 70):
		break
#plot3
#Slam-Share short-term with half-bandwidth
font = {'family' : 'normal',
        'size'   :24}
matplotlib.rc('font', **font)
plt.figure("SLAM-Share_Networking")
#plt.title("CPU  vs. Time")
plt.xlabel('Time (s)', fontsize=24 ) 
plt.ylabel('Cumulative ATE (cm)', fontsize=24) 
plt.plot(time,value, "--",label = "ORBSLAM3", linewidth=2.5)
plt.plot(time_Share,value_Share, "-",label = "SLAM-Share", linewidth=3)
plt.plot(time_Share_half_bandwidth,value_Share_half_bandwidth, "-", color = 'y', label = "SLAM-Share \n(9.4 Mbit/s)", linewidth=3)
plt.plot(Cumulative_time_Share_Delay,Cumulative_value_Share_Delay, "-",color = 'firebrick', label = "SLAM-Share \n(300 ms delay)", linewidth=3)

plt.legend()
plt.show()
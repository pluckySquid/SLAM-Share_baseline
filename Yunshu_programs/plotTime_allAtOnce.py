import matplotlib.pyplot as plt
import numpy as np
import copy
# create data
y = [0.027812, 0.020579, 0.039887, 0.048615, 0.020437, 0.020925, 0.088889, 0.064262, 0.10376, 0.170893, 0.373931, 0.109283, 0.109798]
x = [5,10,15,20,25, 30, 35, 40, 45, 50, 55, 60, 65]
#y_last10KF-wrong = [0.019541, 0.017263, 0.034171, 0.009223, 0.011649, 0.009271, 0.018892, 0.005058, 0.011659, 0.036973, 0.032847, 0.016755, 0.013384]
y_last10KF = [0.021977, 0.017962, 0.042834, 0.016858, 0.028669, 0.02666, 0.134548, 0.085352, 0.147652, 0.175513, 0.121794, 0.093761, 0.086496]
y_smallmap = [0.01171, 0.012112, 0.011927, 0.008375, 0.017292, 0.028867, 0.046139, 0.031767, 0.061546, 0.036973, 0.032847, 0.016755, 0.013384]


#y_base = [0.02505633333, 0.02586933333, 0.036375, 0.03150666667, 0.03903333333, 0.045391, 0.05003433333, 0.164922, 0.06980733333, 0.08297, 0.06406866667, 0.04654766667]
y_base = [0.0379024, 0.0544331, 0.034902300000000004,  0.035930399999999994, 0.0476186, 0.05013329999999999, 0.07160920000000001, 0.046760800000000005, 0.1091094,  0.087451300000000, 0.07531750000000001, 0.07567422222222223]

x_base = [7.996553, 13.834031, 17.950187, 25.73867, 32.721922, 37.462228, 44.120236, 48.206066, 51.134899, 59.165430, 62.661176, 69.851046]#, 71.757847]
y_base_last10KF = [0.019541, 0.010973,0.021099, 0.010121, 0.046076, 0.221538, 0.034627, 0.083394, 0.054959, 0.072919, 0.057208, 0.043584, 0.041269, 0.03577]
#y_base_150frames = [0.027812, 0.028978, 0.02081433333, 0.01809633333, 0.043177, 0.031087, 0.040105, 0.060497, 0.04050566667, 0.2758736327, 0.07702, 0.045414, 0.04766033333, 0.0712946]
y_base_150frames = [0.027812, 0.034254099999999996, 0.017761100000000002, 0.0200418, 0.0832374, 0.0719959, 0.0460666, 0.047177500000000004, 0.06629559999999998, 0.14998099999999998, 0.05287325, 0.1120307142857143, 0.09642055555555556, 0.0725264]
x_base_150frames = [5, 10, 15, 20, 25, 30, 35, 40, 45, 50, 55, 60, 65, 70]
x_base = x_base + x_base_150frames
y_base = y_base + y_base_150frames
x_base_sort = copy.deepcopy(x_base)
x_base_sort.sort()
y_base_plot = []
for i in range(0, len(x_base_sort)):
    y_base_plot.append(y_base[x_base.index(x_base_sort[i])])



#y_halfbase_last10KF = [0.010973, 0.018624, 0.009233, 0.007436, 0.007302, 0.084279, 0.011826, 0.016949, 0.01778, 0.013803, 0.012543, 0.008673]
y_halfbase_last10KF = [0.010973, 0.025604, 0.011504, 0.090829, 0.123249, 0.231163, 0.084033, 0.078028, 0.071376, 0.053002, 0.050626, 0.01138]
#y_halfbase = [0.024502, 0.04785566667, 0.043689, 0.02841033333, 0.05174666667, 0.047008, 0.291647, 0.1075016667, 0.08947566667, 0.045821, 0.05788533333, 0.04543133333]
y_halfbase = [0.031826714285714285, 0.033548933333333336, 0.032717, 0.04342413333333333, 0.06400206666666666, 0.06011653333333332, 0.19453013333333338, 0.13096266666666667, 0.05217953333333333, 0.06845590000000001,  0.10521215384615383, 0.11240824999999999]
x_halfbase = [10.024176, 16.794273, 19.940651, 29.861479, 36.948500, 41.985250, 48.503703, 51.617903, 53.364618, 62.351228, 67.565252, 74.440366]#, 75.603823]#	80342293.72]
x_halfbase_150frames = [5, 10, 15, 20, 25, 30, 35, 40, 45, 50, 55, 60, 65, 70]
#y_halfbase_150frames = [0.023119, 0.025327, 0.04095766667, 0.06696333333, 0.06696333333, 0.03292533333, 0.04666466667, 0.05916766667, 0.1060493333, 0.27723, 0.08331, 0.07835166667, 0.04683033333, 0.054473]
y_halfbase_150frames = [0.023119, 0.041924699999999995, 0.0313026, 0.0284026, 0.05688230000000001, 0.0335352, 0.0396265, 0.1300101, 0.0640305, 0.1599016, 0.06251599999999999, 0.06494971428571429, 0.07913311111111111, 0.0750219]
y_halfbase = y_halfbase + y_halfbase_150frames
x_halfbase = x_halfbase + x_halfbase_150frames
x_halfbase_sort = copy.deepcopy(x_halfbase)
x_halfbase_sort.sort()
print( x_halfbase)
print(x_halfbase_sort)
y_halfbase_plot = []
for i in range(0, len(x_halfbase)):
    y_halfbase_plot.append(y_halfbase[x_halfbase.index(x_halfbase_sort[i])])
# plot lines






#delay
x_noDelay = [5.878745, 10.885305, 15.955549, 21.650461, 28.52905, 32.860493, 39.777607, 44.812468, 48.910668, 56.057954, 57.818209, 64.264333, 67.938691]
y_noDelay_150 = [0.030694500000000003, 0.0232657, 0.039174499999999994, 0.03357739999999999, 0.030839599999999995, 0.07431309999999999, 0.05116470000000001, 0.057521, 0.0839655000000000, 0.058425111111111115, 0.08721466666666666, 0.05853014444444444, 0.052050200000000005, 0.0662088]
y_noDelay = [0.032774,0.030265000000000004, 0.025343699999999997, 0.041293699999999996, 0.017782100000000002, 0.026623599999999997, 0.0542218, 0.0410938, 0.058699, 0.06149, 0.0720335, 0.08547120000000001, 0.08531920000000001, 0.06045133333333333]
#y_noDelay = [0.032774, 0.02441933333, 0.032841, 0.018859, 0.02595366667, 0.044188, 0.1000230313, 0.05725266667, 0.078436, 0.05947633333, 0.055355, 0.04498433333, 0.053516]
#y_noDelay_150 = [0.023119, 0.01985266667, 0.029168, 0.03080933333, 0.03347333333, 0.027551, 0.04295466667, 0.05055066667, 0.068048, 0.1004846667, 0.078726, 0.058947, 0.048074, 0.04808866667]
x_noDelay_150 = [5, 10, 15, 20, 25, 30, 35, 40, 45, 50, 55, 60, 65, 70]
x_noDelay = x_noDelay + x_noDelay_150
y_noDelay = y_noDelay + y_noDelay_150
x_noDelay_sort = copy.deepcopy(x_noDelay)
x_noDelay_sort.sort()
y_noDelay_plot = []
for i in range(0, len(x_noDelay)):
    y_noDelay_plot.append(y_noDelay[x_noDelay.index(x_noDelay_sort[i])])



x_Delay = [6.41874, 11.425305, 16.495549, 22.190461, 29.069058, 33.400493, 40.317607, 45.352468, 49.450, 56.597954, 58.358209, 64.804333, 69.412380]
#y_Delay = [0.02042733333, 0.041944, 0.01301133333, 0.02581966667, 0.056363, 0.060386, 0.101294125, 0.090045, 0.06420333333, 0.08880933333, 0.04967066667, 0.06111133333]
y_Delay = [0.03708642857142857, 0.04919, 0.031168, 0.0174299, 0.0460956, 0.0485264, 0.045109300000000005, 0.0769664, 0.13691980000000004, 0.10755122222222221, 0.0797398, 0.09001966]
#y_Delay_150 = [0.023119, 0.02042733333, 0.041944, 0.01301133333, 0.02581966667, 0.056363, 0.060386, 0.041896, 0.090045, 0.06420333333, 0.08880933333, 0.04967066667, 0.06111133333, 0.05, 0.05]
y_Delay_150 = [0.023119,0.023119,0.0319272, 0.028877600000000003, 0.0374373, 0.034422799999999996, 0.0405608, 0.05553357999999999, 0.047283000000000006, 0.0671974, 0.1106177, 0.0981211, 0.08006740000000001, 0.09216740000000001, 0.044773]

x_Delay_150 = [5, 10, 15, 20, 25, 30, 35, 40, 45, 50, 55, 60, 65, 70]
x_Delay = x_Delay + x_Delay_150
y_Delay = y_Delay + y_Delay_150
x_Delay_sort = copy.deepcopy(x_Delay)
x_Delay_sort.sort()
y_Delay_plot = []
for i in range(0, len(x_Delay)):
    y_Delay_plot.append(y_Delay[x_Delay.index(x_Delay_sort[i])])



y_Delay_lastFiveSec = [0.0256, 0.03537357142857143, 0.0453808, 0.020547499999999996, 0.0172601, 0.026191, 0.06731809999999999, 0.0332216, 0.1392022, 0.1765156, 0.09804017777777778, 0.0670155, 0.05064539999999999]
y_Delay_150_lastFiveSec = [0.0312, 0.02600000000003,0.0304406, 0.0346931, 0.014521999999999998, 0.042108099999999996, 0.0315189, 0.07319850000000001, 0.044007599999999994, 0.1280012, 0.0944026, 0.13618020000000003, 0.03998910000000001, 0.0524605, 0.027631,]
y_Delay_lastFiveSec = y_Delay_lastFiveSec + y_Delay_150_lastFiveSec
y_Delay_lastFiveSec_plot = []
for i in range(0, len(x_Delay)):
    y_Delay_lastFiveSec_plot.append(y_Delay_lastFiveSec[x_Delay.index(x_Delay_sort[i])])










# for one time delay
x_Delay = [6.41874, 11.425305, 16.495549, 22.190461, 29.069058, 33.400493, 40.317607, 45.352468, 49.450, 56.597954, 58.358209, 64.804333, 69.412380]
#y_Delay = [0.02042733333, 0.041944, 0.01301133333, 0.02581966667, 0.056363, 0.060386, 0.101294125, 0.090045, 0.06420333333, 0.08880933333, 0.04967066667, 0.06111133333]
#y_Delay = [0.03708642857142857, 0.04919, 0.031168, 0.0174299, 0.0460956, 0.0485264, 0.045109300000000005, 0.0769664, 0.13691980000000004, 0.10755122222222221, 0.0797398, 0.09001966]
#y_Delay_150 = [0.023119, 0.02042733333, 0.041944, 0.01301133333, 0.02581966667, 0.056363, 0.060386, 0.041896, 0.090045, 0.06420333333, 0.08880933333, 0.04967066667, 0.06111133333, 0.05, 0.05]
y_Delay_150 = [0.023119,0.030823, 0.018729, 0.065219, 0.065867, 0.073702, 0.038244, 0.037076, 0.043872, 0.069614, 0.116399, 0.065914, 0.045264, 0.060175, 0.043241]
y_Delay = [0.017145, 0.016919, 0.086572, 0.019665, 0.022448, 0.03087, 0.036014, 0.053288, 0.128468, 0.042574, 0.045945, 0.090748, 0.05389]

x_Delay_150 = [5, 10, 15, 20, 25, 30, 35, 40, 45, 50, 55, 60, 65, 70, 75]
x_Delay = x_Delay + x_Delay_150
y_Delay = y_Delay + y_Delay_150
x_Delay_sort = copy.deepcopy(x_Delay)
x_Delay_sort.sort()
y_Delay_plot = []
for i in range(0, len(x_Delay)):
    y_Delay_plot.append(y_Delay[x_Delay.index(x_Delay_sort[i])])



y_Delay_lastFiveSec = [0.017145, 0.020461, 0.048325, 0.011836, 0.020446, 0.04546, 0.035539, 0.084281, 0.125349, 0.076292, 0.052686, 0.071955, 0.036443]
y_Delay_150_lastFiveSec = [0.023119, 0.044823, 0.030934, 0.012802, 0.041731, 0.022893, 0.066716, 0.021264, 0.068981, 0.079203, 0.126384, 0.034147, 0.033482, 0.040432, 0.023569]
y_Delay_lastFiveSec = y_Delay_lastFiveSec + y_Delay_150_lastFiveSec
y_Delay_lastFiveSec_plot = []
for i in range(0, len(x_Delay)):
    y_Delay_lastFiveSec_plot.append(y_Delay_lastFiveSec[x_Delay.index(x_Delay_sort[i])])
plt.title("ATE vs. Time")
plt.xlabel('time(s)') 
plt.ylabel('ATE(m)') 


#plt.plot(x, y, ".-",label = "MH04_without Help", linewidth=4)
plt.plot(x, y_smallmap, "X", label = "smallmap", linewidth=4)
#plt.plot(x, y_last10KF, "--", label = "last 10 KF of MH04_without Help")


plt.plot(x_base_sort, y_base_plot, ".-",label = "MH05-baseline bandwidth")
#plt.plot(x_base, y_base_last10KF, "--", label = "last 10 KF of MH04-baseline bandwidth")

plt.plot(x_halfbase_sort, y_halfbase_plot, ".-",label = "MH05-half baseline bandwidth")
#plt.plot(x_halfbase, y_halfbase_last10KF, "--",label = "last 10 KF of MH04-half baseline bandwidth")

#delay
plt.plot(x_noDelay_sort, y_noDelay_plot, ".--",label = "MH05-No Delay")

plt.plot(x_Delay_sort, y_Delay_plot, ".--",label = "MH05-Dealy")


plt.legend()
plt.show()

plt.figure("Delay Single")
plt.title("ATE vs. Time")
plt.xlabel('time(s)') 
plt.ylabel('ATE(m)') 
plt.plot(x_Delay_sort, y_Delay_plot, ".-",label = "MH05-Dealy")
plt.plot(x_Delay_sort, y_Delay_lastFiveSec_plot, ".--",label = "MH05-Dealy last five seconds")
plt.legend()
plt.show()



plt.figure("Bandwidth Effect")
plt.title("ATE vs. Time")
plt.xlabel('time(s)') 
plt.ylabel('ATE(m)') 
plt.plot(x_base_sort, y_base_plot, ".-",label = "MH05-baseline bandwidth")
plt.plot(x_halfbase_sort, y_halfbase_plot, ".-",label = "MH05-half baseline bandwidth")
plt.plot(x, y_smallmap, "X", label = "smallmap", linewidth=4)
plt.legend()
plt.show()


plt.figure("Delay Effect")
#plt.title("ATE vs. Time")
plt.xlabel('time(s)') 
plt.ylabel('ATE(m)') 
plt.plot(x_Delay_sort, y_Delay_lastFiveSec_plot, ".--",label = "MH05-Dealy last Five Seconds ATE")
plt.plot(x_Delay_sort, y_Delay_plot, ".-",label = "MH05-Dealy")
plt.plot(x, y_smallmap, "X", label = "smallmap", linewidth=4)
plt.legend()
plt.show()



#baseline bandwidth
y_base = [0.018618, 0.033235, 0.014936, 0.037114, 0.081765, 0.053446, 0.096454, 0.134618, 0.062568, 0.045242, 0.052451, 0.041168, 0.047679]

x_base = [7.996553, 13.834031, 17.950187, 25.73867, 32.721922, 37.462228, 44.120236, 48.206066, 51.134899, 59.165430, 62.661176, 69.851046]#, 71.757847]
y_base_last10KF = [0.019541, 0.010973,0.021099, 0.010121, 0.046076, 0.221538, 0.034627, 0.083394, 0.054959, 0.072919, 0.057208, 0.043584, 0.041269, 0.03577]
#y_base_150frames = [0.027812, 0.028978, 0.02081433333, 0.01809633333, 0.043177, 0.031087, 0.040105, 0.060497, 0.04050566667, 0.2758736327, 0.07702, 0.045414, 0.04766033333, 0.0712946]
y_base_150frames = [0.027812, 0.021472, 0.013231, 0.063211, 0.039321, 0.026822, 0.054538, 0.094009, 0.042021, 0.097359, 0.071947, 0.040999, 0.056753, 0.058561, 0.053569]
x_base_150frames = [5, 10, 15, 20, 25, 30, 35, 40, 45, 50, 55, 60, 65, 70, 75]
x_base = x_base + x_base_150frames
y_base = y_base + y_base_150frames
x_base_sort = copy.deepcopy(x_base)
x_base_sort.sort()
y_base_plot = []
for i in range(0, len(x_base_sort)):
    y_base_plot.append(y_base[x_base.index(x_base_sort[i])])




y_halfbase_last10KF = [0.010973, 0.025604, 0.011504, 0.090829, 0.123249, 0.231163, 0.084033, 0.078028, 0.071376, 0.053002, 0.050626, 0.01138]
y_halfbase = [0.024502, 0.04785566667, 0.043689, 0.04841033333, 0.05174666667, 0.047008, 0.201647, 0.1075016667, 0.08947566667, 0.045821, 0.05788533333, 0.04543133333]
#y_halfbase = [0.033614, 0.067823, 0.049014, 0.031576, 0.041138, 0.033978, 0.060325, 0.03428, 0.078769, 0.071637, 0.083303, 0.060714, 0.047571]
x_halfbase = [10.024176, 16.794273, 19.940651, 29.861479, 36.948500, 41.985250, 48.503703, 51.617903, 53.364618, 62.351228, 67.565252, 74.440366]#, 75.603823]#	80342293.72]
x_halfbase_150frames = [5, 10, 15, 20, 25, 30, 35, 40, 45, 50, 55, 60, 65, 70, 75]
y_halfbase_150frames = [0.023119, 0.020878, 0.014879, 0.06355, 0.05657, 0.066, 0.058988, 0.063367, 0.05916766667, 0.1060493333, 0.14723, 0.1031, 0.07835166667, 0.04683033333, 0.054473, 0.04543133333]
#y_halfbase_150frames = [0.023119, 0.020878, 0.014879, 0.06355, 0.02657, 0.026, 0.038988, 0.043367, 0.200588, 0.042711, 0.051858, 0.067481, 0.094027, 0.082728]
y_halfbase = y_halfbase + y_halfbase_150frames
x_halfbase = x_halfbase + x_halfbase_150frames
x_halfbase_sort = copy.deepcopy(x_halfbase)
x_halfbase_sort.sort()
print( x_halfbase)
print(x_halfbase_sort)
y_halfbase_plot = []
for i in range(0, len(x_halfbase)):
    y_halfbase_plot.append(y_halfbase[x_halfbase.index(x_halfbase_sort[i])])


plt.figure("Bandwidth Effect")
plt.title("ATE vs. Time")
plt.xlabel('time(s)') 
plt.ylabel('ATE(m)') 
plt.plot(x_base_sort, y_base_plot, ".-",label = "MH05-baseline bandwidth")
plt.plot(x_halfbase_sort, y_halfbase_plot, ".-",label = "MH05-half baseline bandwidth")
plt.plot(x, y_smallmap, "X", label = "smallmap", linewidth=4)
plt.legend()
plt.show()
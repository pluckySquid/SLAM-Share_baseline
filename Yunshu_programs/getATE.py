import os
import sys
import subprocess
#os.chdir("/home/ucrnet/Desktop/workspace/ORBSLAM3/results/smallmap/auto/10 times/full bandwidth/")
#os.chdir("/home/ucrnet/Desktop/workspace/ORBSLAM3/results/smallmap/auto/10 times/half bandwidth - ")
os.chdir("/home/ucrnet/Desktop/workspace/ORBSLAM3/results/smallmap/auto/one time run/half baseline bandwidth 150")
#os.chdir("/home/ucrnet/Desktop/workspace/ORBSLAM3/results/smallmap/auto/10 times/300 delay/")
#os.chdir("/home/ucrnet/Desktop/workspace/ORBSLAM3")
os.chdir("/home/ucrnet/Desktop/workspace/ORBSLAM3/results/onetime/MH05Alone (copy)")

f = open("ATEResult.txt", "r")
Lines = f.readlines()


fileNames = dict({"Map100":[0.37,10]})



#ATEs = []


for iline in range(0, len(Lines)):
    print(Lines[iline])
    if "kf_" in Lines[iline]:
        documentName = Lines[iline]
        key = documentName.rsplit("_", 1)[0]
        print(key)
        value = Lines[iline + 1].split("error.rmse ")[1].split(" m")[0]
        print(value)
        if key in fileNames :
            fileNames[key].append(float(value))
            
        else:
            fileNames[key] = []
            fileNames[key].append(float(value))

        iline = iline + 1

print(fileNames)   
ave = dict()
for i in fileNames:
    print(i)
    ave[int(i.split("Map")[1])] = sum(fileNames[i])/len(fileNames[i])
print(ave)  

sorted_ave = dict(sorted(ave.items()))
for i in sorted_ave:
    print(str(ave[i]) + ", ", end = '')




# for last five sec
fileNames2 = dict({"Map100":[0.37,10]})
for iline in range(0, len(Lines)):
    print(Lines[iline])
    if "kf_" in Lines[iline]:
        documentName = Lines[iline]
        key = documentName.rsplit("_", 1)[0]
        print(key)
        value = Lines[iline + 1].split("error.rmse ")[2].split(" m")[0]
        print(value)
        if key in fileNames2 :
            fileNames2[key].append(float(value))
            
        else:
            fileNames2[key] = []
            fileNames2[key].append(float(value))

        iline = iline + 1

print(fileNames2)   
ave2 = dict()
for i in fileNames2:
    print(i)
    ave2[int(i.split("Map")[1])] = sum(fileNames2[i])/len(fileNames2[i])
print(ave2)  


print("sorted_ave2")
sorted_ave2 = dict(sorted(ave2.items()))

for i in sorted_ave:
    print(str(ave[i]) + ", ", end = '')
print("sorted_ave2")
for i in sorted_ave2:
    print(str(ave2[i]) + ", ", end = '')





# resultSava_file = open("saveATE.txt", "w")
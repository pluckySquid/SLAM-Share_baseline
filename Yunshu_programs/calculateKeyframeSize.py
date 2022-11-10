import os
import matplotlib.pyplot as plt
import numpy as np
import math
import sys


if __name__=="__main__":
    #path = '/home/ucrnet/Desktop/workspace/ORBSLAM3/Yunshu_Results/intervals/Logs/'
    #path = '/home/ucrnet/Desktop/workspace/ORBSLAM3/Yunshu_Results/onlineResults/1kMH04+1kMH05/'
    #path = '/home/ucrnet/Desktop/workspace/ORBSLAM3/Yunshu_Results/1024_MH04_0-1000_MH05_0-1000/result/'
    #path = '/home/ucrnet/Desktop/workspace/ORBSLAM3/Yunshu_Results/1030_MH04_0-2000/result/'
    path = '/home/ucrnet/Desktop/workspace/ORBSLAM3/Yunshu_programs/Shellscommends/'

    os.chdir(path)
    #fileWrite = open(path+"totalResults.txt", "w+")
    if len(sys.argv) < 2:
        fileRead = "KFsize_withKFDB.txt"
    else:
        fileRead = str(sys.argv[1])

    fileWrite = open(path+fileRead +"Result.txt", "w+")

    files = sorted(os.listdir(path))

    #initiate an array of [20][4]

    KFnum = []
    size = []
    y = []
    x = []
    y_average = []
    for i in range(0,100):
        #for j in range(0,4):
            y.append([])
            y_average.append([])
    #y = np.empty([20, 1])
    #print y

    

    file = open(path+fileRead, "r")
    lines = file.read()
    results = lines.split("\n")
    results = filter(None, results)
    count = 0
    sumtemp = 0
    sumsize = 0

    
    
    for result in results:
        #print(result)
        if "keyframe number:" in result:
            KFnum.append(float(result.split("keyframe number: ")[1]))
            
            temp = float(result.split("keyframe number: ")[1])

            sumtemp = sumtemp + temp
            x.append(count)
            
           

            count = count + 1
        elif ".osa size is: " in result:
            #print("here")
            size.append(int(result.split(".osa size is: ")[1]))
            sumsize += int(result.split(".osa size is: ")[1])

    #print(len(x), len(KFnum), len(size))

    for i in range(0, len(x)):
        y[i] = size[i]/KFnum[i]

    fileWrite.write(str(file) + ":\n\t" + str(sumsize/sumtemp))
    print("keyframe size is: ", str(sumsize/sumtemp))
    #fileWrite.write(str(sumtemp/len(results)) + "\n\n")

    file.close()

#                plt.title("absolute_translational_error vs. deleted: " + str(interval) +" images")
    #print(y)
    



    plt.title("keyframes size of each iteration." )
    figure1 = plt.plot(x, y)
    #plt.xlabel("images that are deleted")
    plt.xlabel("Iteration")
    plt.ylabel("Keyframe size")
    plt.show()

    for i in range(0,100):
        y_average[i].append(sum(y[i])/len(y[i]))
    print(y_average)
    figure2 =plt.plot(x,y_average)
    plt.title("average akey frames ploting rate vs. images used to merge. Interval = " + str(interval) +" images")
    plt.xlabel("Images that are used to merge from MH04 and MH05. (MH04:2000, MH05:0)")
    plt.ylabel("absolute_translational_error")
    plt.show()

    fileWrite.close()

import os
import matplotlib.pyplot as plt
import numpy as np
import math


if __name__=="__main__":
    #path = '/home/ucrnet/Desktop/workspace/ORBSLAM3/Yunshu_Results/intervals/Logs/'
    #path = '/home/ucrnet/Desktop/workspace/ORBSLAM3/Yunshu_Results/onlineResults/1kMH04+1kMH05/'
    #path = '/home/ucrnet/Desktop/workspace/ORBSLAM3/Yunshu_Results/1024_MH04_0-1000_MH05_0-1000/result/'
    #path = '/home/ucrnet/Desktop/workspace/ORBSLAM3/Yunshu_Results/1030_MH04_0-2000/result/'
    #path = '/home/ucrnet/Desktop/workspace/ORBSLAM3/Yunshu_Results/onlineResults/2kMH04/'
    path = '/home/ucrnet/Desktop/workspace/ORBSLAM3/Yunshu_Results/onlineResults/2kMH04+2.2kMH05/'

    os.chdir(path)
    #fileWrite = open(path+"totalResults.txt", "w+")
    fileWrite = open(path+"keyFrameResultstoImage_ONLINE_.txt", "w+")

    files = sorted(os.listdir(path))

    #initiate an array of [20][4]
    y = []
    y_average = []

    totalKeyframes = []
    totalframes = []
    for i in range(0,20):
        #for j in range(0,4):
        totalKeyframes.append([])
        totalframes.append([])
        y.append([])
        y_average.append([])
    #y = np.empty([20, 1])
    print y

    l = []
    l_keyframe = []

   # interval = 100


    for file in files:
        print(file)

        count = 0
        count2 = 0

       # interval = ""
        if "keyFrameResults_ONLINE_" in str(file) :
            # l is for lable
            print(file.split("keyFrameResults_ONLINE_100_")[1])
            l.append(file.split("keyFrameResults_ONLINE_100_")[1].split(".txt")[0]  + ": keyframes/frames * 100")
            l_keyframe.append(file.split("keyFrameResults_ONLINE_100_")[1].split(".txt")[0] + ": # of keyframes")
            x = []
            sumtemp = 0
            interval = int(str(file).split("ONLINE_")[1].split("_")[0])
           # interval = int(str(file).split("keyFrameResults_ONLINE_")[1].split(".txt")[0])

            file = open(path+file, "r")
            lines = file.read()
            results = lines.split("\n")
            results = filter(None, results)
            for result in results:
                #print(result.split(".rmse ")[1])
                if "total key frames are: " in result:
                    temp = float(result.split("total key frames are: ")[1])
                    totalImages = interval * (1+count)

                    sumtemp =sumtemp + temp
                    x.append(interval * (count))
                    #print(y[count], np.append(y[count], temp))
                    y[count].append(temp/totalImages * 100)

                    #temp2 = float(result.split("total key frames are: ")[1])
                    totalKeyframes[count].append(temp)

                    #print(y)
                    #y[count].append(temp)
                    count = count + 1
                if "total frames are: " in result:
                    temp2 = float(result.split("total frames are: ")[1])
                    totalframes[count2].append(temp2)
                    count2 = count2 + 1

            fileWrite.write(str(file) + ":\n\t")
            print(len(results))
            fileWrite.write(str(sumtemp/len(results)) + "\n\n")

            file.close()

#                plt.title("absolute_translational_error vs. deleted: " + str(interval) +" images")

            print(interval)
    plt.title("key frames to frames or images ploting rates vs. images used to merge. Interval = " + str(interval) +" images")

    print(y)
    yT = np.transpose(y)
    totalKeyframesT = np.transpose(totalKeyframes)
    print(totalKeyframesT)
    for i in range(0, len(l)):
        figure1 = plt.plot(x, yT[i, :], label=l[i])
        figure1 = plt.plot(x, totalKeyframesT[i, :], label=l_keyframe[i])
    plt.legend()
    #plt.xlabel("images that are deleted")
    plt.xlabel("Images that are used to merge from MH04 and MH05. (MH04:1000, MH05:1000)")
    plt.ylabel("total keyframes ploted / keyframe/frame * 100")
    plt.show()

    plt.title("key frames to frames ploting rate vs. images used to merge. Interval = " + str(interval) +" images")
    for i in range(0, len(l)):
        figure2 = plt.plot(x, yT[i, :], label=l[i])

    plt.legend()
    #plt.xlabel("images that are deleted")
    plt.xlabel("Images that are used to merge from MH04 and MH05. (MH04:1000, MH05:1000)")
    plt.ylabel("keyframe/frame * 100")
    plt.show()

    plt.title("key frames to images ploting rate vs. images used to merge. Interval = " + str(interval) +" images")
    for i in range(0, len(l)):
        figure3 = plt.plot(x, totalKeyframesT[i, :], label=l_keyframe[i])

    plt.legend()
    #plt.xlabel("images that are deleted")
    plt.xlabel("Images that are used to merge from MH04 and MH05. (MH04:1000, MH05:1000)")
    plt.ylabel("total keyframes ploted")
    plt.show()

    totalframesT = np.transpose(totalframes)
    plt.title("frames to images ploting rate vs. images used to merge. Interval = " + str(interval) +" images")
    for i in range(0, len(l)):
        figure4 = plt.plot(x, totalframesT[i, :], label=l_keyframe[i])

    plt.legend()
    #plt.xlabel("images that are deleted")
    plt.xlabel("Images that are used to merge from MH04 and MH05. (MH04:2000, MH05:0000)")
    plt.ylabel("total frames ploted")
    plt.show()

    for i in range(0,20):
        y_average[i].append(sum(y[i]))
    print(y_average)
    figure2 =plt.plot(x,y_average)
    plt.title("average akey frames ploting rate vs. images used to merge. Interval = " + str(interval) +" images")
    plt.xlabel("Images that are used to merge from MH04 and MH05. (MH04:2000, MH05:0)")
    plt.ylabel("absolute_translational_error")
    plt.show()

    fileWrite.close()

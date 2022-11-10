import os
import matplotlib.pyplot as plt
import numpy as np
import math


if __name__=="__main__":
    #path = '/home/ucrnet/Desktop/workspace/ORBSLAM3/Yunshu_Results/intervals/Logs/'
    path = '/home/ucrnet/Desktop/workspace/ORBSLAM3/Yunshu_Results/onlineResults/1kMH04+1kMH05/'
    #path = '/home/ucrnet/Desktop/workspace/ORBSLAM3/Yunshu_Results/onlineResults/2kMH04+1kMH05/'

    os.chdir(path)
    #fileWrite = open(path+"totalResults.txt", "w+")
    fileWrite = open(path+"totalResults_ONLINE.txt", "w+")

    files = sorted(os.listdir(path))

    #initiate an array of [20][4]
    y = []
    y_average = []
    l = []
    for i in range(0,20):
        #for j in range(0,4):
            y.append([])
            y_average.append([])
    #y = np.empty([20, 1])
    print y

    for file in files:
        print(file)

        count = 0

       # interval = ""
        if "log_result_online_100" in str(file) :
            l.append(file.split("log_result_online_100_")[1].split(".txt")[0])
            x = []
            sumtemp = 0
            interval = int(str(file).split("online_")[1].split("_")[0])
            #interval = int(str(file).split("online_")[1].split(".txt")[0])

            file = open(path+file, "r")
            lines = file.read()
            results = lines.split("\n")
            results = filter(None, results)
            for result in results:
                print(result.split(".rmse ")[1])
                temp = float(result.split(".rmse ")[1].split(" m")[0])

                sumtemp =sumtemp + temp
                x.append(interval * (count))
                print(y[count], np.append(y[count], temp))
                y[count] = np.append(y[count], temp)
                #print(y)
                #y[count].append(temp)
                count = count + 1

            fileWrite.write(str(file) + ":\n\t")
            print(len(results))
            fileWrite.write(str(sumtemp/len(results)) + "\n\n")

            file.close()

#                plt.title("absolute_translational_error vs. deleted: " + str(interval) +" images")
    print(y)
    print(interval)
    plt.title("absolute_translational_error vs. images used to merge. Interval = " + str(interval) +" images")
    yT = np.transpose(y)
    print(yT[0, :])
    for i in range(0, len(l)):
        figure1 = plt.plot(x, yT[i, :], label=l[i])
    plt.legend()
    #plt.xlabel("images that are deleted")
    plt.xlabel("Images that are used to merge from MH04 and MH05. (MH04:1000, MH05:1000)")
    plt.ylabel("absolute_translational_error")
    plt.show()

    for i in range(0,20):
        y_average[i].append(sum(y[i])/len(y[i]))
    print(y_average)
    figure2 =plt.plot(x,y_average)
    plt.title("average absolute_translational_error vs. images used to merge. Interval = " + str(interval) +" images")
    plt.xlabel("Images that are used to merge from MH04 and MH05. (MH04:2000, MH05:1000)")
    plt.ylabel("absolute_translational_error")
    plt.show()

    fileWrite.close()

import os
import matplotlib.pyplot as plt
import numpy as np
import math


if __name__=="__main__":
    #path = '/home/ucrnet/Desktop/workspace/ORBSLAM3/Yunshu_Results/intervals/Logs/'
    #path = '/home/ucrnet/Desktop/workspace/ORBSLAM3/Yunshu_Results/onlineResults/1kMH04+1kMH05/'
    #p = sys.argv[1]
    #path = '/home/ucrnet/Desktop/workspace/ORBSLAM3/Yunshu_Results/1020_MH04_1000-2000_MH05_1000-2200/RESULTS/'
    path = '/home/ucrnet/Desktop/workspace/ORBSLAM3/Yunshu_Results/1030_MH04_0-2000/result/'

    os.chdir(path)
    #fileWrite = open(path+"totalResults.txt", "w+")
    interval = 100

    fileWrite = open(path+"keyFrameResults_ONLINE_" + str(interval) +".txt", "a")

    files = sorted(os.listdir(path))

    #initiate an array of [20][4]
    y = []
    y_average = []
    #for i in range(0,30):
        #for j in range(0,4):
    #        y.append([])
    #        y_average.append([])
    #y = np.empty([20, 1])
   # print y
    x = []
    for file in files:
        print(file)

        count = 0

       # interval = ""
        if "f_dataset-MH" in str(file) and ".pdf" not in str(file) :
            #for the frames file
            if "kf_dataset-MH" not in str(file):

                sumtemp = 0
               # interval = int(str(file).split("online_")[1].split("_")[0])
                #interval = int(str(file).split("online_")[1].split(".txt")[0])

                f_file = open(path+file, "r")
                lines = f_file.read()
                f_length= lines.split("\n")
                f_length = len(filter(None, f_length))
                print("f_length", f_length)





                for kf_file in files:
                    #print(kf_file)
                    if str(file) in str(kf_file) and str(file) != str(kf_file) and ".pdf" not in str(kf_file) :
                         #for the frames file
                             print(file, kf_file)
                             sumtemp = 0
                            # interval = int(str(file).split("online_")[1].split("_")[0])
                             #interval = int(str(file).split("online_")[1].split(".txt")[0])

                             kf_fileReader = open(path+kf_file, "r")
                             lines = kf_fileReader.read()
                             kf_length = lines.split("\n")
                             kf_length = len(filter(None, kf_length))

                             print("kf_length", kf_length)




                #           print(len(f_length))
                fileWrite.write(str(file) + ":\n\t")
                #print(f_length)
                fileWrite.write("total images are: " + str(count*interval) + "\n\t")
                print(f_length)
                fileWrite.write("total frames are: " + str(f_length) + "\n\t")
                print(f_length)
                fileWrite.write("total key frames are: " + str(kf_length) + "\n")
                print(kf_length)
                fileWrite.write("keyframeRate of " + str(file) + " is: " + str(kf_length*1.0/f_length) + "\n\n")
                print("keyframeRate is: ", str(kf_length*1.0/f_length))
                f_file.close()
                kf_fileReader.close()

    print(y)
    print(interval)


    fileWrite.close()

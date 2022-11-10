import os
import matplotlib.pyplot as plt


if __name__=="__main__":
    #path = '/home/ucrnet/Desktop/workspace/ORBSLAM3/Yunshu_Results/intervals/Logs/'
    path = '/home/ucrnet/Desktop/workspace/ORBSLAM3/'
    os.chdir(path)
    #fileWrite = open(path+"totalResults.txt", "w+")
    fileWrite = open(path+"totalResults_ONLINE.txt", "w+")

    files = sorted(os.listdir(path))
    x = []
    y = []
    for file in files:
        count = 0
        x = []
        y = []
        interval = ""
        if "log_result_online_100" in str(file) :
            sum = 0
            interval = int(str(file).split("online_")[1].split(".txt")[0])

            file = open(path+file, "r")
            lines = file.read()
            results = lines.split("\n")
            results = filter(None, results)
            for result in results:
                print(result.split(".rmse ")[1])
                temp = float(result.split(".rmse ")[1].split(" m")[0])

                sum =sum + temp
                x.append(interval * (count))
                y.append(temp)
                count = count + 1

            fileWrite.write(str(file) + ":\n\t")
            print(len(results))
            fileWrite.write(str(sum/len(results)) + "\n\n")

            file.close()
            if interval != "":
#                plt.title("absolute_translational_error vs. deleted: " + str(interval) +" images")
                plt.title("absolute_translational_error vs. images used to merge. Interval = " + str(interval) +" images")
                plt.plot(x, y)
                #plt.xlabel("images that are deleted")
                plt.xlabel("Images that are used to merge from MH04 and MH05. (MH04:0-1000, MH05:0-1000)")
                plt.ylabel("absolute_translational_error")
                plt.show()

            fileWrite.close()

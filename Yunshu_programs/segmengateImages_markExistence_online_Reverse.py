import os
import sys

if __name__=="__main__":
    date = sys.argv[1]
    interval = int(sys.argv[2])
    #print(sys.argv[sys.argc-1])


    timeStampFile_path = '/home/ucrnet/Desktop/workspace/ORBSLAM3/Examples/Monocular/EuRoC_TimeStamps/'
    timeStampFile_name = 'MH05.txt'

    resultSava_path = '/home/ucrnet/Desktop/workspace/ORBSLAM3/Yunshu_Results/' + date + '/deletedResults2/'
    if not os.path.exists(resultSava_path):
        os.makedirs(resultSava_path)
    resultSava_fileName = ""

    timeStampFile = open(timeStampFile_path+timeStampFile_name, "r")
    timeStampFileString = timeStampFile.read()
    timeStampFileLines = timeStampFileString.split("\n")


    #interval = 50

    #write the resulting files
    startIndex = 10
    endIndex = 18
    for i in range(startIndex, endIndex):
        start = i  * interval
        end = endIndex * interval
        #start = 1000
       # end = 1750
        print(start)
        print(end)
        #stamp are the starting and ending stamp in the sourceFile [stamp[0], stamp[1]]
        resultSava_fileName = timeStampFile_name.split(".")[0] + "_" + str(i) + "_" + str(interval) + ".txt"
        resultSava_file = open(resultSava_path + resultSava_fileName, "w")
        missingFramesFile = open(resultSava_path+'missingFramesFile' + "_" +timeStampFile_name, "a")
        missingFramesFile.write(timeStampFileLines[start] + ', ' + timeStampFileLines[end] + '\n')


        timeStampList = timeStampFileLines[start : end]
        timeStampListReverse = timeStampList.reverse()
        for j in timeStampList:
                #when timestamp(i) is not in the deleting timestamp range: do
                resultSava_file.write(j)
                resultSava_file.write("\n")
                print(j)
            #else:
                #resultSava_file.write( str(i))
                #resultSava_file.write("\n")
        resultSava_file.close()

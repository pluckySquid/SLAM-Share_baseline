import os
import sys

if __name__=="__main__":
    date = sys.argv[1]
    interval = int(sys.argv[2])
    #print(sys.argv[sys.argc-1])


    timeStampFile_path = '/home/ucrnet/Desktop/workspace/ORBSLAM3/Examples/Monocular/EuRoC_TimeStamps/'
    timeStampFile_name = 'MH04.txt'

    resultSava_path = '/home/ucrnet/Desktop/workspace/ORBSLAM3/Yunshu_Results/' + date + '/skipFrames/'
    if not os.path.exists(resultSava_path):
        os.makedirs(resultSava_path)
    resultSava_fileName = ""

    timeStampFile = open(timeStampFile_path+timeStampFile_name, "r")
    timeStampFileString = timeStampFile.read()
    timeStampFileLines = timeStampFileString.split("\n")


    #interval = 50

    #write the resulting files

        #stamp are the starting and ending stamp in the sourceFile [stamp[0], stamp[1]]
    resultSava_fileName = timeStampFile_name.split(".")[0] + "gap"+ str(interval)+ ".txt"
    resultSava_file = open(resultSava_path + resultSava_fileName, "a")
    missingFramesFile = open(resultSava_path+'missingFramesFilegap' + str(interval)  + '.txt', "a")


    for j in range(len(timeStampFileLines)):
            #when timestamp(i) is not in the deleting timestamp range: do
        if (j /  (interval+1)) % (interval + 1) == 0:
            resultSava_file.write(timeStampFileLines[j])
            resultSava_file.write("\n")
        else:
            if j < len(timeStampFileLines)-1:
                missingFramesFile.write(timeStampFileLines[j] + ', ' + timeStampFileLines[j + 1] + '\n')
                print(j)
        #else:
            #resultSava_file.write( str(i))
            #resultSava_file.write("\n")
    resultSava_file.close()

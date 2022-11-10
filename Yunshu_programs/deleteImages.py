import os
import sys

if __name__=="__main__":
    date = sys.argv[1]
    #print(sys.argv[sys.argc-1])
    open_path = '/home/ucrnet/Desktop/workspace/ORBSLAM3/Yunshu_Results/' + date + '/'
    file_name = "MH04_imageSequences.txt"

    if not os.path.exists(open_path):
        os.makedirs('open_path')

    file1 = open(open_path + file_name, "r")
    #print(file1.read())

    stampsString = file1.read()
    stampsLines = stampsString.splitlines()
    stamps = []
    for i in stampsLines:
        stamps.append(i.split(", "))
        print(i.split(", "))

    print(stamps)

    timeStampFile_path = '/home/ucrnet/Desktop/workspace/ORBSLAM3/Examples/Monocular/EuRoC_TimeStamps/'
    timeStampFile_name = 'MH04.txt'
    resultSava_path = '/home/ucrnet/Desktop/workspace/ORBSLAM3/Yunshu_Results/' + date + '/deletedResults/'
    if not os.path.exists(resultSava_path):
        os.makedirs(resultSava_path)
    resultSava_fileName = ""

    timeStampFile = open(timeStampFile_path+timeStampFile_name, "r")
    timeStampFileString = timeStampFile.read()
    timeStampFileLines = timeStampFileString.split("\n")

    #count is the number of the current deleting sequence
    count = 0
    #write the resulting files
    for stamp in stamps:
        #stamp are the starting and ending stamp in the sourceFile [stamp[0], stamp[1]]
        resultSava_fileName = timeStampFile_name.split(".")[0] + "_" + str(count) + ".txt"
        resultSava_file = open(resultSava_path + resultSava_fileName, "a")
        for i in timeStampFileLines:
            #i is the timestamp of the image
            if i < stamp[0] or i > stamp[1]:
                #when timestamp(i) is not in the deleting timestamp range: do
                resultSava_file.write(i)
                resultSava_file.write("\n")
                print(i)
            #else:
                #resultSava_file.write( str(i))
                #resultSava_file.write("\n")
        count = count + 1
        resultSava_file.close()

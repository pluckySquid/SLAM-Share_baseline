import os
import sys

if __name__=="__main__":
    date = sys.argv[1]
    #interval = int(sys.argv[2])
    #print(sys.argv[sys.argc-1])


    timeStampFile_path = '/home/ucrnet/Desktop/workspace/dataset/sequences/00/image_0/'


    resultSava_path = '/home/ucrnet/Desktop/workspace/ORBSLAM3/Yunshu_Results/dataset/' + date + '/deletedResults/'
    if not os.path.exists(resultSava_path):
        os.makedirs(resultSava_path)
    resultSava_fileName = "00.txt"
    resultSava_file = open(resultSava_path + resultSava_fileName, "w+")
    files = sorted(os.listdir(timeStampFile_path))

    #interval = 50

    #write the resulting files
    for file in files:


        #stamp are the starting and ending stamp in the sourceFile [stamp[0], stamp[1]]
        resultSava_fileName = file.split(".")[0]
        print(resultSava_fileName)
        resultSava_file.write(resultSava_fileName + "\n")





    resultSava_file.close()

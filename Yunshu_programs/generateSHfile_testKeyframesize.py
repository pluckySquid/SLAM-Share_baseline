import os
import sys
import subprocess
import glob

def number(x):
    return(x.split("_")[1])

def excute(file, keyframesize_file):
    subprocess.call(["./" +file])
    writeFile(keyframesize_file)

def writeFile(keyframesize_file):
    keyframesize_file.write( str(file).split(".")[0] + ".osa " + "size is: " + str(os.path.getsize("/home/ucrnet/Desktop/workspace/ORBSLAM3/"+str(file).split(".")[0] + ".osa")) + "\n\n")


if __name__=="__main__":
    date = sys.argv[1]
    interval = sys.argv[2]
    print(date)




    resultSava_path = '/home/ucrnet/Desktop/workspace/ORBSLAM3/Yunshu_programs/Shellscommends/testKeyFramesize/'
    if not os.path.exists(resultSava_path):
        os.makedirs(resultSava_path)
    resultSava_fileName = "shellCommands"

    keyframesizeFile = "KFsize.txt"
    keyframesize_file = open(resultSava_path + keyframesizeFile, "a")


    os.chdir(resultSava_path)

    #date = date.split("_")[0]
    #write the resulting files
    for i in range(0,100):


        resultSava_fileName = "shellCommands" + "_" + str(i).zfill(3) + ".sh"
        resultSava_file = open(resultSava_path + resultSava_fileName, "w")

        resultSava_file.write("#!/bin/bash\n")
        resultSava_file.write("pathDatasetEuroc='/home/ucrnet/Desktop/workspace/slamdata' #Example, it is necesary to change it by the dataset path\n")

        D = 'cd /home/ucrnet/Desktop/workspace/ORBSLAM3/\n'

        A = "echo " + resultSava_fileName.split(".sh")[0] + " | ./Examples/Monocular/mono_euroc ./Vocabulary/ORBvoc.txt ./Examples/Monocular/EuRoC.yaml \"$pathDatasetEuroc\"/MH04 ./Examples/Monocular/EuRoC_TimeStamps/MH04.txt " + resultSava_fileName.split(".sh")[0] + "\n"
        

        #resultSava_file.write("dir\n")
        resultSava_file.write(D)
        #resultSava_file.write("dir\n")
        resultSava_file.write(A)
       # resultSava_file.write(B)

        resultSava_file.close()

        os.chmod(resultSava_fileName, 0777)
        #subprocess.call(["./run.sh"])



    os.chdir(resultSava_path)

    files = sorted(os.listdir(resultSava_path))

    #files = sorted(os.listdir(resultSava_path), key=lambda x: int(os.path.splitext(x)[0]))

    print(files)

    #resultSava_path = '/home/ucrnet/Desktop/workspace/ORBSLAM3/Yunshu_programs/Shellscommends/' + interval + '/' + date + '/'


    for file in files:

       if ".sh" in file:
           #with open(file, 'r') as f:
              print(file)
              excute(file, keyframesize_file)
              

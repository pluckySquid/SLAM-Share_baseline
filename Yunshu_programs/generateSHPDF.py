import os
import sys
import subprocess
import glob

def number(x):
    return(x.split("_")[1])
if __name__=="__main__":
    date = sys.argv[1]
    interval = sys.argv[2]
    #print(sys.argv[sys.argc-1])




    resultSava_path = '/home/ucrnet/Desktop/workspace/ORBSLAM3/Yunshu_programs/Shellscommends2/' + interval + '/' + date + '/'
    if not os.path.exists(resultSava_path):
        os.makedirs(resultSava_path)
    resultSava_fileName = "shellCommands"



    os.chdir(resultSava_path)

    #write the resulting files
    for i in range(2000/int(interval)):


        resultSava_fileName = "shellCommands" + "_" + str(i).zfill(3) + ".sh"
        resultSava_file = open(resultSava_path + resultSava_fileName, "a")

        resultSava_file.write("#!/bin/bash\n")
        resultSava_file.write("pathDatasetEuroc='/home/ucrnet/Desktop/workspace/slamdata' #Example, it is necesary to change it by the dataset path\n")

        D = 'cd /home/ucrnet/Desktop/workspace/ORBSLAM3/\n'

       # A = "./Examples/Monocular/mono_euroc ./Vocabulary/ORBvoc.txt ./Examples/Monocular/EuRoC.yaml \" $pathDatasetEuroc\"/MH04 ./Yunshu_Results/0923/deletedResults2/MH04_" +str(i) +".txt \"$pathDatasetEuroc\"/MH05 ./Examples/Monocular/EuRoC_TimeStamps/MH05.txt dataset-MH0405-0923_"+str(i) + "\n"
        B = "python2 evaluation/evaluate_ate_scale_color_final.py evaluation/Ground_truth/EuRoC_left_cam/merged_GT_samples.txt kf_dataset-MH0405-0923_" + str(i) +".txt --plot kf_dateset-MH0405-0923_" + str(i) +".pdf "+ str(i) +" Yunshu_Results/0923/deletedResults2/missingFramesFile.txt"

        #resultSava_file.write("dir\n")
        resultSava_file.write(D)
        #resultSava_file.write("dir\n")
        resultSava_file.write(A)
        #resultSava_file.write(B)


        resultSava_file.close()

        os.chmod(resultSava_fileName, 3333)


    os.chdir(resultSava_path)

    files = sorted(os.listdir(resultSava_path))

    #files = sorted(os.listdir(resultSava_path), key=lambda x: int(os.path.splitext(x)[0]))

    print(files)

    #resultSava_path = '/home/ucrnet/Desktop/workspace/ORBSLAM3/Yunshu_programs/Shellscommends/' + interval + '/' + date + '/'


    for file in files:

       if ".sh" in file:
           #with open(file, 'r') as f:
              print(file)
              subprocess.call(["./" +file])

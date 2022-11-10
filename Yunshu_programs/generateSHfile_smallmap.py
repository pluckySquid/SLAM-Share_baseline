import os
import sys
import subprocess
import glob

def number(x):
    return(x.split("_")[1])
if __name__=="__main__":





    resultSava_path = '/home/ucrnet/Desktop/workspace/ORBSLAM3/Yunshu_programs/Shellscommends/smallmaps/'
    if not os.path.exists(resultSava_path):
        os.makedirs(resultSava_path)
    resultSava_fileName = "shellCommands"


    smallmap_frames = [239, 415, 538, 772, 981, 1123, 1323, 1446, 1534, 1774, 1879, 2095,	2152]
    # half baseline bandwidth
    #smallmap_frames = [300, 503, 598, 895, 1108, 1259, 1455, 1548, 1600, 1870, 2026, 2233, 2268]
    print(smallmap_frames)
    os.chdir(resultSava_path)

    #date = date.split("_")[0]
    #write the resulting files
    for j in range(7, 12):
        #get small map first
        D = 'cd /home/ucrnet/Desktop/workspace/ORBSLAM3/\n'
        T = "sudo echo smallmap" + str(j) + " | ./Examples/Monocular/mono_euroc ./Vocabulary/ORBvoc.txt ./Examples/Monocular/EuRoC.yaml \"$pathDatasetEuroc\"/MH05 ./Examples/Monocular/EuRoC_TimeStamps/MH05.txt  \"$pathDatasetEuroc\"MH04 ./Examples/Monocular/EuRoC_TimeStamps/MH04.txt " + str(j) + " \n"
        resultSava_fileName = "getSmallMap" + str(j) +".sh"
        resultSava_file = open(resultSava_path + resultSava_fileName, "w")
        resultSava_file.write("#!/bin/bash\n")
        resultSava_file.write("pathDatasetEuroc='/home/ucrnet/Desktop/workspace/slamdata/'\n")
        resultSava_file.write(D)
        
        resultSava_file.write(T)
        resultSava_file.close()
        os.chmod(resultSava_fileName, 7777)
        #subprocess.call(["./" +resultSava_fileName])
        print("small map generated")

        for i in range(0,j * 3 - 2):
            

            resultSava_fileName = "smallmapResult" + "_" + str(j).zfill(3) + "_" + str(i).zfill(3) + ".sh"
            resultSava_file = open(resultSava_path + resultSava_fileName, "w")

            resultSava_file.write("#!/bin/bash\n")
            resultSava_file.write("pathDatasetEuroc='/home/ucrnet/Desktop/workspace/slamdata/' #Example, it is necesary to change it by the dataset path\n")

            D = 'cd /home/ucrnet/Desktop/workspace/ORBSLAM3/\n'


    # A = "echo " + resultSava_fileName.split(".sh")[0] + " | ./Examples/Monocular/mono_euroc ./Vocabulary/ORBvoc.txt ./Examples/Monocular/EuRoC.yaml \"$pathDatasetEuroc\"/MH04 ./Yunshu_Results/" + date +"/deletedResults2/MH04_" +str(i) + "_" +interval+".txt \"$pathDatasetEuroc\"/MH05 ./Yunshu_Results/" +date +"/deletedResults2/MH05_"+str(i)+"_"+str(interval) +".txt dataset-MH0405-"+date+"_"+str(i).zfill(3) + "\n"
    #        B = "python2 evaluation/evaluate_ate_scale_color_final_markBoth_Online.py evaluation/Ground_truth/EuRoC_left_cam/merged_GT_samples.txt kf_dataset-MH0405-"+date+"_" + str(i).zfill(3) +".txt --plot kf_dataset-MH0405-"+interval+"_" + str(i).zfill(3) +".pdf "+ str(i) +" Yunshu_Results/"+date+"/deletedResults2/missingFramesFile_MH04.txt " +str(i)+" Yunshu_Results/" + date+"/deletedResults2/missingFramesFile_MH05.txt"
            # {   echo y;    echo password;  }
            A = "{   echo " + resultSava_fileName.split(".sh")[0] + ";    echo " + resultSava_fileName.split(".sh")[0] + ";  } | ./Examples/Monocular/mono_euroc_load_2-load1Do2 ./Vocabulary/ORBvoc.txt ./Examples/Monocular/EuRoC.yaml \"$pathDatasetEuroc\"/MH05 ./Examples/Monocular/EuRoC_TimeStamps/MH05.txt dataset-MH_testMerge_1129 smallmap" + str(j) + ".osa " + str(smallmap_frames[j]) +" \n"
            #B = "python2 evaluation/evaluate_ate_scale_color_final_markBoth_Online.py evaluation/Ground_truth/EuRoC_left_cam/merged_GT_samples.txt kf_dataset-MH0405-"+"_" + str(j).zfill(3) +".txt --plot kf_dataset-MH0405-"+"_" + str(j).zfill(3) +".pdf "+ str(j) +" Yunshu_Results/deletedResults2/missingFramesFile_MH04.txt " +str(i+1)+" Yunshu_Results/" + date+"/deletedResults2/missingFramesFile_MH05.txt"
            B = "python2 evaluation/evaluate_ate_scale_color_MarkAll.py evaluation/Ground_truth/EuRoC_left_cam/merged_GT_samples.txt kf_" + resultSava_fileName.split(".sh")[0]+ ".txt --plot "+ resultSava_fileName.split(".sh")[0]  + ".pdf"
            #resultSava_file.write("dir\n")
            
            resultSava_file.write(D)
            #resultSava_file.write("dir\n")
            resultSava_file.write(A)
            resultSava_file.write(B)


            resultSava_file.close()

            os.chmod(resultSava_fileName, 7777)
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
              subprocess.call(["./" +file])

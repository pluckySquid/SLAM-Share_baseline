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
    smallmap_frames = [300, 503, 598, 895, 1108, 1259, 1455, 1548, 1600, 1870, 2026, 2233, 2268]
 #delay
    #smallmap_frames = [176,326, 478, 649, 855, 985, 1193, 1344, 1476, 1681, 1734, 1927, 2038]
    #smallmap_frames = [192, 342, 494, 665, 872, 1002, 1209, 1360, 1483, 1697, 1750, 1944, 2054]
    print(smallmap_frames)
    os.chdir(resultSava_path)

    #date = date.split("_")[0]
    #write the resulting files
    for j in range(0, 13):
        
        print("small map generated")

        for i in range(0, 1 ):
            

            #get small map first
            D = 'cd /home/ucrnet/Desktop/workspace/ORBSLAM3/\n'
            resultSava_fileName = "getSmallMap" + str(j) + "_" + str(i) +".sh"
            T = "{   echo " + resultSava_fileName.split(".sh")[0] + ";    echo " + resultSava_fileName.split(".sh")[0] + ";  } | ./Examples/Monocular/mono_euroc ./Vocabulary/ORBvoc.txt ./Examples/Monocular/EuRoC.yaml \"$pathDatasetEuroc\"/MH05 ./Examples/Monocular/EuRoC_TimeStamps/MH05.txt  \"$pathDatasetEuroc\"/MH04 ./Examples/Monocular/EuRoC_TimeStamps/MH04.txt \"$pathDatasetEuroc\"/MH05 ./Examples/Monocular/EuRoC_TimeStamps/MH05.txt " + str(j) + " space " + str(smallmap_frames[j])+ " \n"
            # s = 0
            # for t in range (0,13):
            #     if (150 * j + 150 < smallmap_frames[t]):
            #         break
            #     s = t
            
            # T = "{   echo " + resultSava_fileName.split(".sh")[0] + ";    echo " + resultSava_fileName.split(".sh")[0] + ";  } | ./Examples/Monocular/mono_euroc ./Vocabulary/ORBvoc.txt ./Examples/Monocular/EuRoC.yaml \"$pathDatasetEuroc\"/MH05 ./Examples/Monocular/EuRoC_TimeStamps/MH05.txt  \"$pathDatasetEuroc\"/MH04 ./Examples/Monocular/EuRoC_TimeStamps/MH04.txt \"$pathDatasetEuroc\"/MH05 ./Examples/Monocular/EuRoC_TimeStamps/MH05.txt " + str(s) + " space " + str(j * 150 + 150 )+ " \n"

            resultSava_file = open(resultSava_path + resultSava_fileName, "w")
            resultSava_file.write("#!/bin/bash\n")
            resultSava_file.write("pathDatasetEuroc='/home/ucrnet/Desktop/workspace/slamdata/'\n")
            resultSava_file.write(D)
            
            resultSava_file.write(T)

            os.chmod(resultSava_fileName, 7777)
            #subprocess.call(["./" +resultSava_fileName])

            B = "python2 evaluation/evaluate_ate_scale_color_MarkAll.py evaluation/Ground_truth/EuRoC_left_cam/merged_GT_samples.txt kf_" + resultSava_fileName.split(".sh")[0]+ ".txt --plot "+ resultSava_fileName.split(".sh")[0]  + ".pdf"

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

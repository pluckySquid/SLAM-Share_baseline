import os
import sys
import subprocess
import glob

def number(x):
    return(x.split("_")[1])
if __name__=="__main__":




    targetFilePath = '/home/ucrnet/Desktop/workspace/ORBSLAM3/results/onetime//13/'
    targetFilePath = '/home/ucrnet/Desktop/workspace/ORBSLAM3/results/onetime/delay/6/'
    #targetFilePath = '/home/ucrnet/Desktop/workspace/ORBSLAM3/results/onetime/noTC/4/'
    # targetFilePath = '/home/ucrnet/Desktop/workspace/ORBSLAM3/results/onetime/MH05Alone/9/'
    # targetFilePath = '/home/ucrnet/Desktop/workspace/ORBSLAM3/results/onetime/MH0405-MH05/11/'

    resultSava_path = '/home/ucrnet/Desktop/workspace/ORBSLAM3/Yunshu_programs/Shellscommends/plotKF/'
    resultSava_path = '/home/ucrnet/Desktop/workspace/ORBSLAM3/Yunshu_programs/Shellscommends/plotKF/'
    if not os.path.exists(resultSava_path):
        os.makedirs(resultSava_path)
    resultSava_fileName = "shellCommands"


#get small map first
    D = 'cd /home/ucrnet/Desktop/workspace/ORBSLAM3/\n'
    resultSava_fileName = "plotATE.sh"          
    resultSava_file = open(resultSava_path + resultSava_fileName, "w")
    resultSava_file.write("#!/bin/bash\n")
    resultSava_file.write("pathDatasetEuroc='/home/ucrnet/Desktop/workspace/slamdata/'\n")
    resultSava_file.write(D)
    

    os.chdir(targetFilePath)

    targetFiles = sorted(os.listdir(targetFilePath), key=lambda x: int(x.split(".")[0].split("_smallmap")[1]))

    print(targetFiles)


    for file in targetFiles:

        if "kf_" in file:
           #with open(file, 'r') as f:
            print(file)


            B = "python2 evaluation/evaluate_ate_scale_color_MarkAll.py evaluation/Ground_truth/EuRoC_left_cam/merged_GT_samples.txt " + targetFilePath + file + " --plot "+ file.split(".text")[0]  + ".pdf \n"
            
            resultSava_file.write(B)
            D = 'cd /home/ucrnet/Desktop/workspace/ORBSLAM3/\n'
            resultSava_file.write(D)


        
        
        
    resultSava_file.close()
    
    
        #subprocess.call(["./run.sh"])


    
    os.chdir(resultSava_path)
    os.chmod(resultSava_fileName, 7777)

    files = sorted(os.listdir(resultSava_path))

    #files = sorted(os.listdir(resultSava_path), key=lambda x: int(os.path.splitext(x)[0]))

    print(files)

    #resultSava_path = '/home/ucrnet/Desktop/workspace/ORBSLAM3/Yunshu_programs/Shellscommends/' + interval + '/' + date + '/'


    for file in files:

       if ".sh" in file:
           #with open(file, 'r') as f:
              print(file)
              subprocess.call(["./" +file])

#!/bin/bash
pathDatasetEuroc='/home/ucrnet/Desktop/workspace/slamdata' #Example, it is necesary to change it by the dataset path
cd /home/ucrnet/Desktop/workspace/ORBSLAM3/
shellCommands_078 | ./Examples/Monocular/mono_euroc ./Vocabulary/ORBvoc.txt ./Examples/Monocular/EuRoC.yaml "$pathDatasetEuroc"/MH04 ./Yunshu_Results/0901/deletedResults2/MH04_78.txt dataset-MH04-0901_78
python2 evaluation/evaluate_ate_scale_color_final.py evaluation/Ground_truth/EuRoC_left_cam/merged_GT_samples.txt kf_dataset-MH04-0901_78.txt --plot kf_dateset-MH04-0901_78.pdf 78 Yunshu_Results/0901/deletedResults2/missingFramesFile.txt
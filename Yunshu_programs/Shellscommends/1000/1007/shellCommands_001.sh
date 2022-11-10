#!/bin/bash
pathDatasetEuroc='/home/ucrnet/Desktop/workspace/slamdata' #Example, it is necesary to change it by the dataset path
cd /home/ucrnet/Desktop/workspace/ORBSLAM3/
shellCommands_001 | ./Examples/Monocular/mono_euroc ./Vocabulary/ORBvoc.txt ./Examples/Monocular/EuRoC.yaml "$pathDatasetEuroc"/MH04 ./Yunshu_Results/1007/deletedResults2/MH04_0.txt "$pathDatasetEuroc"/MH05 ./Yunshu_Results/1007/deletedResults2/MH05_01201.txt dataset-MH0405-1007_new3
python2 evaluation/evaluate_ate_scale_color_final.py evaluation/Ground_truth/EuRoC_left_cam/merged_GT_samples.txt kf_dataset-MH0405-1007_new3.txt --plot kf_dateset-MH0405-1000_new4.pdf 1 Yunshu_Results/1007/deletedResults2/missingFramesFile.txt

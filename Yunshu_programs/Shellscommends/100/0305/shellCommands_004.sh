#!/bin/bash
pathDatasetEuroc='/home/ucrnet/Desktop/workspace/slamdata' #Example, it is necesary to change it by the dataset path
cd /home/ucrnet/Desktop/workspace/ORBSLAM3/
echo shellCommands_004 | ./Examples/Monocular/mono_euroc ./Vocabulary/ORBvoc.txt ./Examples/Monocular/EuRoC.yaml "$pathDatasetEuroc"/MH04 ./Yunshu_Results/0305/deletedResults2/MH04_9_100.txt "$pathDatasetEuroc"/MH05 ./Yunshu_Results/0305/deletedResults2/MH05_4_20.txt dataset-MH0405-0305_004
python2 evaluation/evaluate_ate_scale_color_final_markBoth_Online.py evaluation/Ground_truth/EuRoC_left_cam/merged_GT_samples.txt kf_dataset-MH0405-0305_004.txt --plot kf_dataset-MH0405-20_004.pdf 9 Yunshu_Results/0305/deletedResults2/missingFramesFile_MH04.txt 4 Yunshu_Results/0305/deletedResults2/missingFramesFile_MH05.txt
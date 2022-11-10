#!/bin/bash
pathDatasetEuroc='/home/ucrnet/Desktop/workspace/slamdata' #Example, it is necesary to change it by the dataset path
cd /home/ucrnet/Desktop/workspace/ORBSLAM3/
shellCommands_018 | ./Examples/Monocular/mono_euroc ./Vocabulary/ORBvoc.txt ./Examples/Monocular/EuRoC.yaml "$pathDatasetEuroc"/MH05 ./Yunshu_Results/1025_MH05_1000-2200/deletedResults2/MH05_18_100.txt dataset-MH05-1025_MH05_1000-2200_18
python2 evaluation/evaluate_ate_scale_color_final_markBoth_Online.py evaluation/Ground_truth/EuRoC_left_cam/merged_GT_samples.txt kf_dataset-MH05-1025_MH05_1000-2200_18.txt --plot kf_dateset-MH05-100_18.pdf -1 Yunshu_Results/1025_MH05_1000-2200/deletedResults2/missingFramesFile_MH04.txt 8 Yunshu_Results/1025_MH05_1000-2200/deletedResults2/missingFramesFile_MH05.txt
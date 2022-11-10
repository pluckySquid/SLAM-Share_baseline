#!/bin/bash
pathDatasetEuroc='/home/ucrnet/Desktop/workspace/slamdata' #Example, it is necesary to change it by the dataset path
cd /home/ucrnet/Desktop/workspace/ORBSLAM3/
echo shellCommands_010 | ./Examples/Monocular/mono_euroc ./Vocabulary/ORBvoc.txt ./Examples/Monocular/EuRoC.yaml "$pathDatasetEuroc"/MH04 ./Yunshu_Results/0322/deletedResults2/MH04_10_100.txt dataset-MH04-0322_010
python2 evaluation/evaluate_ate_scale_color_final_markBoth_Online.py evaluation/Ground_truth/EuRoC_left_cam/merged_GT_samples.txt kf_dataset-MH04-0322_010.txt --plot kf_dateset-MH04-100_010.pdf 0 Yunshu_Results/0322/deletedResults2/missingFramesFile_MH04.txt -1 Yunshu_Results/0322/deletedResults2/missingFramesFile_MH05.txt
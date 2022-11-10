#!/bin/bash
pathDatasetEuroc='/home/ucrnet/Desktop/workspace/slamdata' #Example, it is necesary to change it by the dataset path
cd /home/ucrnet/Desktop/workspace/ORBSLAM3/
echo shellCommands_010 | ./Examples/Monocular/mono_euroc ./Vocabulary/ORBvoc.txt ./Examples/Monocular/EuRoC.yaml "$pathDatasetEuroc"/MH05 ./Yunshu_Results/0531/deletedResults2/MH05_10_150.txt dataset-MH05-0531_10
python2 evaluation/evaluate_ate_scale_color_final_markBoth_Online.py evaluation/Ground_truth/EuRoC_left_cam/merged_GT_samples.txt kf_dataset-MH05-0531_10.txt --plot kf_dateset-MH05-150_10.pdf -1 Yunshu_Results/0531/deletedResults2/missingFramesFile_MH04.txt 10 Yunshu_Results/0531/deletedResults2/missingFramesFile_MH05.txt
#!/bin/bash
pathDatasetEuroc='/home/ucrnet/Desktop/workspace/slamdata' #Example, it is necesary to change it by the dataset path
cd /home/ucrnet/Desktop/workspace/ORBSLAM3/
echo shellCommands_016 | ./Examples/Monocular/mono_euroc ./Vocabulary/ORBvoc.txt ./Examples/Monocular/EuRoC.yaml "$pathDatasetEuroc"/MH05 ./Yunshu_Results/0531/deletedResults2/MH05_16_150.txt dataset-MH05-0531_16
python2 evaluation/evaluate_ate_scale_color_final_markBoth_Online.py evaluation/Ground_truth/EuRoC_left_cam/merged_GT_samples.txt kf_dataset-MH05-0531_16.txt --plot kf_dateset-MH05-150_16.pdf -1 Yunshu_Results/0531/deletedResults2/missingFramesFile_MH04.txt 16 Yunshu_Results/0531/deletedResults2/missingFramesFile_MH05.txt
#!/bin/bash
pathDatasetEuroc='/home/ucrnet/Desktop/workspace/slamdata' #Example, it is necesary to change it by the dataset path
cd /home/ucrnet/Desktop/workspace/ORBSLAM3/
shellCommands_021 | ./Examples/Monocular/mono_euroc ./Vocabulary/ORBvoc.txt ./Examples/Monocular/EuRoC.yaml "$pathDatasetEuroc"/MH04 ./Yunshu_Results/1020/deletedResults2/MH04_9_100.txt "$pathDatasetEuroc"/MH05 ./Yunshu_Results/1020/deletedResults2/MH05_21_100.txt dataset-MH0405-1020_21
python2 evaluation/evaluate_ate_scale_color_final_markBoth_Online.py evaluation/Ground_truth/EuRoC_left_cam/merged_GT_samples.txt kf_dataset-MH0405-1020_21.txt --plot kf_dateset-MH0405-100_21.pdf 9 Yunshu_Results/1020/deletedResults2/missingFramesFile_MH04.txt 11 Yunshu_Results/1020/deletedResults2/missingFramesFile_MH05.txt
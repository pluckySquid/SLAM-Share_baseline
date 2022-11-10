#!/bin/bash
pathDatasetEuroc='/home/ucrnet/Desktop/workspace/slamdata' #Example, it is necesary to change it by the dataset path
cd /home/ucrnet/Desktop/workspace/ORBSLAM3/
echo shellCommands_020 | ./Examples/Monocular/mono_euroc ./Vocabulary/ORBvoc.txt ./Examples/Monocular/EuRoC.yaml "$pathDatasetEuroc"/MH04 ./Yunshu_Results/onlineATE/deletedResults2/MH04_21_100.txt "$pathDatasetEuroc"/MH05 ./Yunshu_Results/onlineATE/deletedResults2/MH05_20_100.txt dataset-MH0405-onlineATE_020
python2 evaluation/evaluate_ate_scale_color_final_markBoth_Online.py evaluation/Ground_truth/EuRoC_left_cam/merged_GT_samples.txt kf_dataset-MH0405-onlineATE_020.txt --plot kf_dataset-MH0405-100_020.pdf 21 Yunshu_Results/onlineATE/deletedResults2/missingFramesFile_MH04.txt 20 Yunshu_Results/onlineATE/deletedResults2/missingFramesFile_MH05.txt
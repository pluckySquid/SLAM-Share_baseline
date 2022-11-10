#!/bin/bash
pathDatasetEuroc='/home/ucrnet/Desktop/workspace/slamdata' #Example, it is necesary to change it by the dataset path
cd /home/ucrnet/Desktop/workspace/ORBSLAM3/
shellCommands_011 | ./Examples/Monocular/mono_euroc ./Vocabulary/ORBvoc.txt ./Examples/Monocular/EuRoC.yaml "$pathDatasetEuroc"/MH04 ./Yunshu_Results/10203/deletedResults2/MH04_9_100.txt "$pathDatasetEuroc"/MH05 ./Yunshu_Results/10203/deletedResults2/MH05_11_100.txt dataset-MH0405-10203_11
python2 evaluation/evaluate_ate_scale_color_final_markBoth_Online.py evaluation/Ground_truth/EuRoC_left_cam/merged_GT_samples.txt kf_dataset-MH0405-10203_11.txt --plot kf_dateset-MH0405-100_11.pdf 9 Yunshu_Results/10203/deletedResults2/missingFramesFile_MH04.txt 11 Yunshu_Results/10203/deletedResults2/missingFramesFile_MH05.txt
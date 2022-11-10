#!/bin/bash
pathDatasetEuroc='/home/ucrnet/Desktop/workspace/slamdata' #Example, it is necesary to change it by the dataset path
cd /home/ucrnet/Desktop/workspace/ORBSLAM3/
echo shellCommands_013 | ./Examples/Monocular/mono_euroc ./Vocabulary/ORBvoc.txt ./Examples/Monocular/EuRoC.yaml "$pathDatasetEuroc"/MH04 ./Yunshu_Results/0607/deletedResults2/MH04_13_150.txt "$pathDatasetEuroc"/MH05 ./Yunshu_Results/0607/deletedResults2/MH05_14_150.txt dataset-MH0405-0607_013
python2 evaluation/evaluate_ate_scale_color_final_markBoth_Online.py evaluation/Ground_truth/EuRoC_left_cam/merged_GT_samples.txt kf_dataset-MH0405-0607_013.txt --plot kf_dataset-MH0405-150_013.pdf 13 Yunshu_Results/0607/deletedResults2/missingFramesFile_MH04.txt 14 Yunshu_Results/0607/deletedResults2/missingFramesFile_MH05.txt
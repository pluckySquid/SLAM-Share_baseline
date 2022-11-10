#!/bin/bash
pathDatasetEuroc='/home/ucrnet/Desktop/workspace/slamdata' #Example, it is necesary to change it by the dataset path
cd /home/ucrnet/Desktop/workspace/ORBSLAM3/
shellCommands_000 | ./Examples/Monocular/mono_euroc ./Vocabulary/ORBvoc.txt ./Examples/Monocular/EuRoC.yaml "$pathDatasetEuroc"/MH04 ./Yunshu_Results/1030_MH04_1000-2000/deletedResults2/MH04_0_100.txt dataset-MH04-1030_MH04_1000-2000_0
python2 evaluation/evaluate_ate_scale_color_final_markBoth_Online.py evaluation/Ground_truth/EuRoC_left_cam/merged_GT_samples.txt kf_dataset-MH04-1030_MH04_1000-2000_0.txt --plot kf_dateset-MH04-100_0.pdf 0 Yunshu_Results/1030_MH04_1000-2000/deletedResults2/missingFramesFile_MH04.txt -1 Yunshu_Results/1030_MH04_1000-2000/deletedResults2/missingFramesFile_MH05.txt
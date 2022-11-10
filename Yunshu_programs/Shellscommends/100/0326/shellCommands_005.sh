#!/bin/bash
pathDatasetEuroc='/home/ucrnet/Desktop/workspace/slamdata' #Example, it is necesary to change it by the dataset path
cd /home/ucrnet/Desktop/workspace/ORBSLAM3/
echo MH04-5 | ./Examples/Monocular/mono_euroc ./Vocabulary/ORBvoc.txt ./Examples/Monocular/EuRoC.yaml "$pathDatasetEuroc"/MH04 ./Yunshu_Results/0326/deletedResults2/MH04_5_100.txt dataset-MH04-0326_005
python2 evaluation/evaluate_ate_scale_color_final_markBoth_Online.py evaluation/Ground_truth/EuRoC_left_cam/merged_GT_samples.txt kf_dataset-MH04-0326_005.txt --plot kf_dateset-MH04-100_005.pdf -5 Yunshu_Results/0326/deletedResults2/missingFramesFile_MH04.txt -1 Yunshu_Results/0326/deletedResults2/missingFramesFile_MH04.txt
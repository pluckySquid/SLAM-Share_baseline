#!/bin/bash
pathDatasetEuroc='/home/ucrnet/Desktop/workspace/slamdata' #Example, it is necesary to change it by the dataset path
cd /home/ucrnet/Desktop/workspace/ORBSLAM3/
shellCommands_006 | ./Examples/Monocular/mono_euroc ./Vocabulary/ORBvoc.txt ./Examples/Monocular/EuRoC.yaml "$pathDatasetEuroc"/MH04 ./Yunshu_Results/0928/deletedResults2/MH04_6.txt "$pathDatasetEuroc"/MH05 ./Examples/Monocular/EuRoC_TimeStamps/MH05.txt dataset-MH0405-0928_6
python2 evaluation/evaluate_ate_scale_color_final.py evaluation/Ground_truth/EuRoC_left_cam/merged_GT_samples.txt kf_dataset-MH0405-0928_6.txt --plot kf_dateset-MH0405-0928_6.pdf 6 Yunshu_Results/0928/deletedResults2/missingFramesFile.txt
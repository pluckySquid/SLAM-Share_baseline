#!/bin/bash
pathDatasetEuroc='/home/ucrnet/Desktop/workspace/slamdata' #Example, it is necesary to change it by the dataset path
cd /home/ucrnet/Desktop/workspace/ORBSLAM3/
echo shellCommands_005 | ./Examples/Monocular/mono_euroc ./Vocabulary/ORBvoc.txt ./Examples/Monocular/EuRoC.yaml "$pathDatasetEuroc"/MH05 ./Yunshu_Results/0323/deletedResults2/MH05_5_100.txt dataset-MH05-0323_5
python2 evaluation/evaluate_ate_scale_color_final_markBoth_Online.py evaluation/Ground_truth/EuRoC_left_cam/merged_GT_samples.txt kf_dataset-MH05-0323_5.txt --plot kf_dateset-MH05-100_5.pdf -1 Yunshu_Results/0323/deletedResults2/missingFramesFile_MH04.txt 5 Yunshu_Results/0323/deletedResults2/missingFramesFile_MH05.txt
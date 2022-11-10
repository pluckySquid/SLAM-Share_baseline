#!/bin/bash
pathDatasetEuroc='/home/ucrnet/Desktop/workspace/slamdata' #Example, it is necesary to change it by the dataset path
cd /home/ucrnet/Desktop/workspace/ORBSLAM3/
echo shellCommands_017 | ./Examples/Monocular/mono_euroc ./Vocabulary/ORBvoc.txt ./Examples/Monocular/EuRoC.yaml "$pathDatasetEuroc"/MH05 ./Yunshu_Results/0323/deletedResults2/MH05_17_100.txt dataset-MH05-0323_17
python2 evaluation/evaluate_ate_scale_color_final_markBoth_Online.py evaluation/Ground_truth/EuRoC_left_cam/merged_GT_samples.txt kf_dataset-MH05-0323_17.txt --plot kf_dateset-MH05-100_17.pdf -1 Yunshu_Results/0323/deletedResults2/missingFramesFile_MH04.txt 17 Yunshu_Results/0323/deletedResults2/missingFramesFile_MH05.txt
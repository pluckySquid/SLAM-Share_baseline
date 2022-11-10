#!/bin/bash
pathDatasetEuroc='/home/ucrnet/Desktop/workspace/slamdata' #Example, it is necesary to change it by the dataset path
cd /home/ucrnet/Desktop/workspace/ORBSLAM3/
echo shellCommands_011 | ./Examples/Monocular/mono_euroc ./Vocabulary/ORBvoc.txt ./Examples/Monocular/EuRoC.yaml "$pathDatasetEuroc"/MH04 ./Yunshu_Results/0319/deletedResults2/MH04_11_100.txt "$pathDatasetEuroc"/MH05 ./Yunshu_Results/0319/deletedResults2/MH05_11_100.txt dataset-MH0405-0319_011
python2 evaluation/evaluate_ate_scale_color_final_markBoth_Online.py evaluation/Ground_truth/EuRoC_left_cam/merged_GT_samples.txt kf_dataset-MH0405-0319_011.txt --plot kf_dataset-MH0405-100_011.pdf 11 Yunshu_Results/0319/deletedResults2/missingFramesFile_MH04.txt 11 Yunshu_Results/0319/deletedResults2/missingFramesFile_MH05.txt
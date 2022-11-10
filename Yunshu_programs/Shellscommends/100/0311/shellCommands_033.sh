#!/bin/bash
pathDatasetEuroc='/home/ucrnet/Desktop/workspace/slamdata' #Example, it is necesary to change it by the dataset path
cd /home/ucrnet/Desktop/workspace/ORBSLAM3/
echo shellCommands_033 | ./Examples/Monocular/mono_euroc ./Vocabulary/ORBvoc.txt ./Examples/Monocular/EuRoC.yaml "$pathDatasetEuroc"/MH04 ./Yunshu_Results/0311/deletedResults2/MH04_12_100.txt "$pathDatasetEuroc"/MH04 ./Yunshu_Results/0311/deletedResults2/MH05_33_100.txt dataset-MH0405-0311_033
python2 evaluation/evaluate_ate_scale_color_final_markBoth_Online.py evaluation/Ground_truth/EuRoC_left_cam/merged_GT_samples.txt kf_dataset-MH0405-0311_033.txt --plot kf_dataset-MH0405-100_033.pdf 12 Yunshu_Results/0311/deletedResults2/missingFramesFile_MH04.txt 33 Yunshu_Results/0311/deletedResults2/missingFramesFile_MH05.txt
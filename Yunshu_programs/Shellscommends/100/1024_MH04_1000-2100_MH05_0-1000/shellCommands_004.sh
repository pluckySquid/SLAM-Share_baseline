#!/bin/bash
pathDatasetEuroc='/home/ucrnet/Desktop/workspace/slamdata' #Example, it is necesary to change it by the dataset path
cd /home/ucrnet/Desktop/workspace/ORBSLAM3/
shellCommands_004 | ./Examples/Monocular/mono_euroc ./Vocabulary/ORBvoc.txt ./Examples/Monocular/EuRoC.yaml "$pathDatasetEuroc"/MH04 ./Yunshu_Results/1024_MH04_1000-2100_MH05_0-1000/deletedResults2/MH04_19_100.txt "$pathDatasetEuroc"/MH05 ./Yunshu_Results/1024_MH04_1000-2100_MH05_0-1000/deletedResults2/MH05_4_100.txt dataset-MH0405-1024_MH04_1000-2100_MH05_0-1000_4
python2 evaluation/evaluate_ate_scale_color_final_markBoth_Online.py evaluation/Ground_truth/EuRoC_left_cam/merged_GT_samples.txt kf_dataset-MH0405-1024_MH04_1000-2100_MH05_0-1000_4.txt --plot kf_dataset-MH0405-100_4.pdf 9 Yunshu_Results/1024_MH04_1000-2100_MH05_0-1000/deletedResults2/missingFramesFile_MH04.txt 4 Yunshu_Results/1024_MH04_1000-2100_MH05_0-1000/deletedResults2/missingFramesFile_MH05.txt
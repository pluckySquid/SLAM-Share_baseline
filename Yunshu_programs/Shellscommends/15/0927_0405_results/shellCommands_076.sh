#!/bin/bash
pathDatasetEuroc='/home/ucrnet/Desktop/workspace/slamdata' #Example, it is necesary to change it by the dataset path
cd /home/ucrnet/Desktop/workspace/ORBSLAM3/
shellCommands_076 | ./Examples/Monocular/mono_euroc ./Vocabulary/ORBvoc.txt ./Examples/Monocular/EuRoC.yaml "$pathDatasetEuroc"/MH04 ./Yunshu_Results/0927/deletedResults2/MH04_76.txt "$pathDatasetEuroc"/MH05 ./Examples/Monocular/EuRoC_TimeStamps/MH05.txt dataset-MH0405-0927_76
python2 evaluation/evaluate_ate_scale_color_final_saveResults.py evaluation/Ground_truth/EuRoC_left_cam/merged_GT_samples.txt kf_dataset-MH0405-0927_76.txt --plot kf_dateset-MH0405-15_76.pdf 76 Yunshu_Results/0927/deletedResults2/missingFramesFile.txt
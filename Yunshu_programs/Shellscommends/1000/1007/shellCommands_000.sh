#!/bin/bash
pathDatasetEuroc='/home/ucrnet/Desktop/workspace/slamdata' #Example, it is necesary to change it by the dataset path
cd /home/ucrnet/Desktop/workspace/ORBSLAM3/
shellCommands_000 | ./Examples/Monocular/mono_euroc ./Vocabulary/ORBvoc.txt ./Examples/Monocular/EuRoC.yaml "$pathDatasetEuroc"/MH04 ./Yunshu_Results/1007/deletedResults2/MH04_01201.txt "$pathDatasetEuroc"/MH05 ./Yunshu_Results/1007/deletedResults2/MH05_01201.txt dataset-MH0405-1007_new0
python2 evaluation/evaluate_ate_scale_color_final_markBoth.py evaluation/Ground_truth/EuRoC_left_cam/merged_GT_samples.txt kf_dataset-MH0405-1007_new0.txt --plot kf_dateset-MH0405-1000_new0.pdf 0 Yunshu_Results/1007/deletedResults2/missingFramesFile.txt

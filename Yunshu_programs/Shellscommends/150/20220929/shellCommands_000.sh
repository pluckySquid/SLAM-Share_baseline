#!/bin/bash
pathDatasetEuroc='/home/ucrnet/Desktop/workspace/slamdata' #Example, it is necesary to change it by the dataset path
cd /home/ucrnet/Desktop/workspace/ORBSLAM3/
echo MH04-0 | ./Examples/Monocular/mono_euroc ./Vocabulary/ORBvoc.txt ./Examples/Monocular/EuRoC.yaml "$pathDatasetEuroc"/MH04 ./Yunshu_Results/20220929/deletedResults2/MH04_0_150.txt dataset-MH04-20220929_000
python2 evaluation/evaluate_ate_scale_color_final_markBoth_Online.py evaluation/Ground_truth/EuRoC_left_cam/merged_GT_samples.txt kf_dataset-MH04-20220929_000.txt --plot kf_dateset-MH04-150_000.pdf -10 Yunshu_Results/20220929/deletedResults2/missingFramesFile_MH04.txt -1 Yunshu_Results/20220929/deletedResults2/missingFramesFile_MH04.txt
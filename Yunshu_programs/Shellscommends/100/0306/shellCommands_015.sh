#!/bin/bash
pathDatasetEuroc='/home/ucrnet/Desktop/workspace/slamdata' #Example, it is necesary to change it by the dataset path
cd /home/ucrnet/Desktop/workspace/ORBSLAM3/
python2 evaluation/evaluate_ate_scale_color_final_markBoth_Online.py evaluation/Ground_truth/EuRoC_left_cam/merged_GT_samples.txt kf_dataset-MH0405-0306_015.txt --plot kf_dataset-MH0405-20_015.pdf 9 Yunshu_Results/0306/deletedResults2/missingFramesFile_MH04.txt 15 Yunshu_Results/0306/deletedResults2/missingFramesFile_MH05.txt
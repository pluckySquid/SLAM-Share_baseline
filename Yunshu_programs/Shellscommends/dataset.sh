#!/bin/bash
pathDatasetEuroc='/home/ucrnet/Desktop/workspace/dateaset/sequences' #Example, it is necesary to change it by the dataset path
cd /home/ucrnet/Desktop/workspace/ORBSLAM3/
./Examples/Monocular/mono_euroc ./Vocabulary/ORBvoc.txt ./Examples/Monocular/EuRoC.yaml "$pathDatasetEuroc"/00 ./"$pathDatasetEuroc"/00/times.txt dataset-00
python2 evaluation/evaluate_ate_scale.py evaluation/Ground_truth/EuRoC_left_cam/merged_GT_samples.txt kf_dataset-MH04-1030_MH04_1000-2000_0.txt --plot kf_dateset-MH04-100_0.pdf 0 Yunshu_Results/1030_MH04_1000-2000/deletedResults2/missingFramesFile_MH04.txt -1 Yunshu_Results/1030_MH04_1000-2000/deletedResults2/missingFramesFile_MH05.txt

#!/bin/bash
pathDatasetEuroc='/home/ucrnet/Desktop/workspace/slamdata/'
cd /home/ucrnet/Desktop/workspace/ORBSLAM3/
{   echo getSmallMap12_41;    echo getSmallMap12_41;  } | ./Examples/Monocular/mono_euroc_load_2 ./Vocabulary/ORBvoc.txt ./Examples/Monocular/EuRoC.yaml "$pathDatasetEuroc"/MH05 ./Examples/Monocular/EuRoC_TimeStamps/MH05.txt  "$pathDatasetEuroc"/MH04 ./Examples/Monocular/EuRoC_TimeStamps/MH04.txt "$pathDatasetEuroc"/MH05 ./Examples/Monocular/EuRoC_TimeStamps/MH05.txt 13 space 2100 
python2 evaluation/evaluate_ate_scale_color_MarkAll.py evaluation/Ground_truth/EuRoC_left_cam/merged_GT_samples.txt kf_getSmallMap12_41.txt --plot getSmallMap12_41.pdf
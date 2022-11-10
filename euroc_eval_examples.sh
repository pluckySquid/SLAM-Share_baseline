#!/bin/bash
pathDatasetEuroc='/home/ucrnet/Desktop/workspace/slamdata' #Example, it is necesary to change it by the dataset path

# Single Session Example (Pure visual)
#echo "Launching MH01 with Stereo sensor"
#./Examples/Stereo/stereo_euroc ./Vocabulary/ORBvoc.txt ./Examples/Stereo/EuRoC.yaml "$pathDatasetEuroc"/MH01 ./Examples/Stereo/EuRoC_TimeStamps/MH01.txt dataset-MH01_stereo
echo "------------------------------------"

#echo "Evaluation of MH01 trajectory with Monocular sensor"
# python2 evaluation/evaluate_ate_scale.py evaluation/Ground_truth/EuRoC_left_cam/MH01_GT.txt f_dataset-MH01.txt --plot MH01_mono.pdf
#python2 evaluation/evaluate_ate_scale.py evaluation/Ground_truth/EuRoC_left_cam/MH02_GT.txt f_dataset-MH02.txt --plot MH02_mono.pdf
#python2 evaluation/evaluate_ate_scale.py evaluation/Ground_truth/EuRoC_left_cam/MH03_GT.txt kf_dataset-MH03.txt --plot MH03_mono.pdf
#python2 evaluation/evaluate_ate_scale.py evaluation/Ground_truth/EuRoC_left_cam/MH04_GT.txt f_dataset-MH04.txt --plot MH04_mono.pdf
# python2 evaluation/evaluate_ate_scale.py evaluation/Ground_truth/EuRoC_left_cam/MH05_GT.txt kf_dataset-MH05.txt --plot MH05_mono.pdf

#echo "Evaluation of MH01 trajectory with Stereo sensor"
#python2 evaluation/evaluate_ate_scale.py evaluation/Ground_truth/EuRoC_left_cam/MH01_GT.txt f_dataset-MH01_stereo.txt --plot MH01_stereo.pdf
#merged_GT_samples


#python2 evaluation/evaluate_ate_scale.py evaluation/Ground_truth/EuRoC_left_cam/merged_GT_samples.txt kf_dataset-MH_ALL_merge.txt --plot MH_ALL.pdf

python2 evaluation/evaluate_ate_scale_color_MarkRed.py evaluation/Ground_truth/EuRoC_left_cam/merged_GT_samples.txt kf_dataset-MH0405_0913.txt --plot kf_0913_origine.pdf
#python2 evaluation/evaluate_ate_scale_color_MarkRed.py evaluation/Ground_truth/EuRoC_left_cam/merged_GT_samples.txt kf_dataset-MH0405_0912_0.txt --plot kf_0912_0.pdf

#python2 evaluation/evaluate_ate_scale.py evaluation/Ground_truth/EuRoC_left_cam/merged_GT_samples.txt kf_dataset-MH0405_0911.txt --plot kf_0911.pdf

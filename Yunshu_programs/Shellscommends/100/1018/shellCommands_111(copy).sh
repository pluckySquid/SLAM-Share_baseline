#!/bin/bash
pathDatasetEuroc='/home/ucrnet/Desktop/workspace/slamdata' #Example, it is necesary to change it by the dataset path
cd /home/ucrnet/Desktop/workspace/ORBSLAM3/
shellCommands_000 | ./Examples/Monocular/mono_euroc ./Vocabulary/ORBvoc.txt ./Examples/Monocular/EuRoC.yaml "$pathDatasetEuroc"/MH04 ./Yunshu_Results/1018/deletedResults2/MH04_0_100.txt dataset-MH04-1018_0
python2 evaluation/evaluate_ate_scale_color_final_markBoth_Online.py evaluation/Ground_truth/EuRoC_left_cam/merged_GT_samples.txt kf_dataset-MH04-1018_0.txt --plot kf_dateset-MH04-100_0.pdf 0 Yunshu_Results/1018/deletedResults2/missingFramesFile_MH04.txt -1 Yunshu_Results/1018/deletedResults2/missingFramesFile_MH05.txt



cd /home/ucrnet/Desktop/workspace/ORBSLAM3/
shellCommands_000 | ./Examples/Monocular/mono_euroc ./Vocabulary/ORBvoc.txt ./Examples/Monocular/EuRoC.yaml "$pathDatasetEuroc"/MH04 ./Yunshu_Results/1018/deletedResults2/MH04_1_100.txt dataset-MH04-1018_1
python2 evaluation/evaluate_ate_scale_color_final_markBoth_Online.py evaluation/Ground_truth/EuRoC_left_cam/merged_GT_samples.txt kf_dataset-MH04-1018_1.txt --plot kf_dateset-MH04-100_1.pdf 1 Yunshu_Results/1018/deletedResults2/missingFramesFile_MH04.txt -1 Yunshu_Results/1018/deletedResults2/missingFramesFile_MH05.txt


cd /home/ucrnet/Desktop/workspace/ORBSLAM3/
shellCommands_000 | ./Examples/Monocular/mono_euroc ./Vocabulary/ORBvoc.txt ./Examples/Monocular/EuRoC.yaml "$pathDatasetEuroc"/MH04 ./Yunshu_Results/1018/deletedResults2/MH04_2_100.txt dataset-MH04-1018_2
python2 evaluation/evaluate_ate_scale_color_final_markBoth_Online.py evaluation/Ground_truth/EuRoC_left_cam/merged_GT_samples.txt kf_dataset-MH04-1018_2.txt --plot kf_dateset-MH04-100_2.pdf 2 Yunshu_Results/1018/deletedResults2/missingFramesFile_MH04.txt -1 Yunshu_Results/1018/deletedResults2/missingFramesFile_MH05.txt


cd /home/ucrnet/Desktop/workspace/ORBSLAM3/
shellCommands_000 | ./Examples/Monocular/mono_euroc ./Vocabulary/ORBvoc.txt ./Examples/Monocular/EuRoC.yaml "$pathDatasetEuroc"/MH04 ./Yunshu_Results/1018/deletedResults2/MH04_3_100.txt dataset-MH04-1018_3
python2 evaluation/evaluate_ate_scale_color_final_markBoth_Online.py evaluation/Ground_truth/EuRoC_left_cam/merged_GT_samples.txt kf_dataset-MH04-1018_3.txt --plot kf_dateset-MH04-100_3.pdf 3 Yunshu_Results/1018/deletedResults2/missingFramesFile_MH04.txt -1 Yunshu_Results/1018/deletedResults2/missingFramesFile_MH05.txt


cd /home/ucrnet/Desktop/workspace/ORBSLAM3/
shellCommands_000 | ./Examples/Monocular/mono_euroc ./Vocabulary/ORBvoc.txt ./Examples/Monocular/EuRoC.yaml "$pathDatasetEuroc"/MH04 ./Yunshu_Results/1018/deletedResults2/MH04_4_100.txt dataset-MH04-1018_4
python2 evaluation/evaluate_ate_scale_color_final_markBoth_Online.py evaluation/Ground_truth/EuRoC_left_cam/merged_GT_samples.txt kf_dataset-MH04-1018_4.txt --plot kf_dateset-MH04-100_4.pdf 4 Yunshu_Results/1018/deletedResults2/missingFramesFile_MH04.txt -1 Yunshu_Results/1018/deletedResults2/missingFramesFile_MH05.txt

cd /home/ucrnet/Desktop/workspace/ORBSLAM3/
shellCommands_000 | ./Examples/Monocular/mono_euroc ./Vocabulary/ORBvoc.txt ./Examples/Monocular/EuRoC.yaml "$pathDatasetEuroc"/MH04 ./Yunshu_Results/1018/deletedResults2/MH04_5_100.txt dataset-MH04-1018_5
python2 evaluation/evaluate_ate_scale_color_final_markBoth_Online.py evaluation/Ground_truth/EuRoC_left_cam/merged_GT_samples.txt kf_dataset-MH04-1018_5.txt --plot kf_dateset-MH04-100_5.pdf 5 Yunshu_Results/1018/deletedResults2/missingFramesFile_MH04.txt -1 Yunshu_Results/1018/deletedResults2/missingFramesFile_MH05.txt

cd /home/ucrnet/Desktop/workspace/ORBSLAM3/
shellCommands_000 | ./Examples/Monocular/mono_euroc ./Vocabulary/ORBvoc.txt ./Examples/Monocular/EuRoC.yaml "$pathDatasetEuroc"/MH04 ./Yunshu_Results/1018/deletedResults2/MH04_6_100.txt dataset-MH04-11018_6
python2 evaluation/evaluate_ate_scale_color_final_markBoth_Online.py evaluation/Ground_truth/EuRoC_left_cam/merged_GT_samples.txt kf_dataset-MH04-1018_6.txt --plot kf_dateset-MH04-100_6.pdf 6 Yunshu_Results/1018/deletedResults2/missingFramesFile_MH04.txt -1 Yunshu_Results/1018/deletedResults2/missingFramesFile_MH05.txt

cd /home/ucrnet/Desktop/workspace/ORBSLAM3/
shellCommands_000 | ./Examples/Monocular/mono_euroc ./Vocabulary/ORBvoc.txt ./Examples/Monocular/EuRoC.yaml "$pathDatasetEuroc"/MH04 ./Yunshu_Results/1018/deletedResults2/MH04_7_100.txt dataset-MH04-1018_7
python2 evaluation/evaluate_ate_scale_color_final_markBoth_Online.py evaluation/Ground_truth/EuRoC_left_cam/merged_GT_samples.txt kf_dataset-MH04-1018_7.txt --plot kf_dateset-MH04-100_7.pdf 7 Yunshu_Results/1018/deletedResults2/missingFramesFile_MH04.txt -1 Yunshu_Results/1018/deletedResults2/missingFramesFile_MH05.txt

cd /home/ucrnet/Desktop/workspace/ORBSLAM3/
shellCommands_000 | ./Examples/Monocular/mono_euroc ./Vocabulary/ORBvoc.txt ./Examples/Monocular/EuRoC.yaml "$pathDatasetEuroc"/MH04 ./Yunshu_Results/1018/deletedResults2/MH04_8_100.txt dataset-MH04-1018_8
python2 evaluation/evaluate_ate_scale_color_final_markBoth_Online.py evaluation/Ground_truth/EuRoC_left_cam/merged_GT_samples.txt kf_dataset-MH04-1018_8.txt --plot kf_dateset-MH04-100_8.pdf 8 Yunshu_Results/1018/deletedResults2/missingFramesFile_MH04.txt -1 Yunshu_Results/1018/deletedResults2/missingFramesFile_MH05.txt

cd /home/ucrnet/Desktop/workspace/ORBSLAM3/
shellCommands_000 | ./Examples/Monocular/mono_euroc ./Vocabulary/ORBvoc.txt ./Examples/Monocular/EuRoC.yaml "$pathDatasetEuroc"/MH04 ./Yunshu_Results/1018/deletedResults2/MH04_9_100.txt dataset-MH04-1018_9
python2 evaluation/evaluate_ate_scale_color_final_markBoth_Online.py evaluation/Ground_truth/EuRoC_left_cam/merged_GT_samples.txt kf_dataset-MH04-1018_9.txt --plot kf_dateset-MH04-100_9.pdf 9 Yunshu_Results/1018/deletedResults2/missingFramesFile_MH04.txt -1 Yunshu_Results/1018/deletedResults2/missingFramesFile_MH05.txt





cd /home/ucrnet/Desktop/workspace/ORBSLAM3/
shellCommands_000 | ./Examples/Monocular/mono_euroc ./Vocabulary/ORBvoc.txt ./Examples/Monocular/EuRoC.yaml "$pathDatasetEuroc"/MH04 ./Yunshu_Results/1018/deletedResults2/MH04_9_100.txt "$pathDatasetEuroc"/MH05 ./Yunshu_Results/1018/deletedResults2/MH05_10_100.txt dataset-MH0405-1018_0
python2 evaluation/evaluate_ate_scale_color_final_markBoth_Online.py evaluation/Ground_truth/EuRoC_left_cam/merged_GT_samples.txt kf_dataset-MH0405-1018_0.txt --plot kf_dateset-MH0405-100_0.pdf 9 Yunshu_Results/1018/deletedResults2/missingFramesFile_MH04.txt 0 Yunshu_Results/1018/deletedResults2/missingFramesFile_MH05.txt



cd /home/ucrnet/Desktop/workspace/ORBSLAM3/
shellCommands_000 | ./Examples/Monocular/mono_euroc ./Vocabulary/ORBvoc.txt ./Examples/Monocular/EuRoC.yaml "$pathDatasetEuroc"/MH04 ./Yunshu_Results/1018/deletedResults2/MH04_9_100.txt "$pathDatasetEuroc"/MH05 ./Yunshu_Results/1018/deletedResults2/MH05_11_100.txt dataset-MH0405-1018_1
python2 evaluation/evaluate_ate_scale_color_final_markBoth_Online.py evaluation/Ground_truth/EuRoC_left_cam/merged_GT_samples.txt kf_dataset-MH0405-1018_1.txt --plot kf_dateset-MH0405-100_1.pdf 9 Yunshu_Results/1018/deletedResults2/missingFramesFile_MH04.txt 1 Yunshu_Results/1018/deletedResults2/missingFramesFile_MH05.txt



cd /home/ucrnet/Desktop/workspace/ORBSLAM3/
shellCommands_000 | ./Examples/Monocular/mono_euroc ./Vocabulary/ORBvoc.txt ./Examples/Monocular/EuRoC.yaml "$pathDatasetEuroc"/MH04 ./Yunshu_Results/1018/deletedResults2/MH04_9_100.txt "$pathDatasetEuroc"/MH05 ./Yunshu_Results/1018/deletedResults2/MH05_12_100.txt dataset-MH0405-1018_2
python2 evaluation/evaluate_ate_scale_color_final_markBoth_Online.py evaluation/Ground_truth/EuRoC_left_cam/merged_GT_samples.txt kf_dataset-MH0405-1018_2.txt --plot kf_dateset-MH0405-100_2.pdf 9 Yunshu_Results/1018/deletedResults2/missingFramesFile_MH04.txt 2 Yunshu_Results/1018/deletedResults2/missingFramesFile_MH05.txt


cd /home/ucrnet/Desktop/workspace/ORBSLAM3/
shellCommands_000 | ./Examples/Monocular/mono_euroc ./Vocabulary/ORBvoc.txt ./Examples/Monocular/EuRoC.yaml "$pathDatasetEuroc"/MH04 ./Yunshu_Results/1018/deletedResults2/MH04_9_100.txt "$pathDatasetEuroc"/MH05 ./Yunshu_Results/1018/deletedResults2/MH05_13_100.txt dataset-MH0405-1018_3
python2 evaluation/evaluate_ate_scale_color_final_markBoth_Online.py evaluation/Ground_truth/EuRoC_left_cam/merged_GT_samples.txt kf_dataset-MH0405-1018_3.txt --plot kf_dateset-MH0405-100_3.pdf 9 Yunshu_Results/1018/deletedResults2/missingFramesFile_MH04.txt 3 Yunshu_Results/1018/deletedResults2/missingFramesFile_MH05.txt


cd /home/ucrnet/Desktop/workspace/ORBSLAM3/
shellCommands_000 | ./Examples/Monocular/mono_euroc ./Vocabulary/ORBvoc.txt ./Examples/Monocular/EuRoC.yaml "$pathDatasetEuroc"/MH04 ./Yunshu_Results/1018/deletedResults2/MH04_9_100.txt "$pathDatasetEuroc"/MH05 ./Yunshu_Results/1018/deletedResults2/MH05_14_100.txt dataset-MH0405-1018_4
python2 evaluation/evaluate_ate_scale_color_final_markBoth_Online.py evaluation/Ground_truth/EuRoC_left_cam/merged_GT_samples.txt kf_dataset-MH0405-1018_4.txt --plot kf_dateset-MH0405-100_4.pdf 9 Yunshu_Results/1018/deletedResults2/missingFramesFile_MH04.txt 4 Yunshu_Results/1018/deletedResults2/missingFramesFile_MH05.txt


cd /home/ucrnet/Desktop/workspace/ORBSLAM3/
shellCommands_000 | ./Examples/Monocular/mono_euroc ./Vocabulary/ORBvoc.txt ./Examples/Monocular/EuRoC.yaml "$pathDatasetEuroc"/MH04 ./Yunshu_Results/1018/deletedResults2/MH04_9_100.txt "$pathDatasetEuroc"/MH05 ./Yunshu_Results/1018/deletedResults2/MH05_15_100.txt dataset-MH0405-1018_5
python2 evaluation/evaluate_ate_scale_color_final_markBoth_Online.py evaluation/Ground_truth/EuRoC_left_cam/merged_GT_samples.txt kf_dataset-MH0405-1018_5.txt --plot kf_dateset-MH0405-100_5.pdf 9 Yunshu_Results/1018/deletedResults2/missingFramesFile_MH04.txt 5 Yunshu_Results/1018/deletedResults2/missingFramesFile_MH05.txt


cd /home/ucrnet/Desktop/workspace/ORBSLAM3/
shellCommands_000 | ./Examples/Monocular/mono_euroc ./Vocabulary/ORBvoc.txt ./Examples/Monocular/EuRoC.yaml "$pathDatasetEuroc"/MH04 ./Yunshu_Results/1018/deletedResults2/MH04_9_100.txt "$pathDatasetEuroc"/MH05 ./Yunshu_Results/1018/deletedResults2/MH05_16_100.txt dataset-MH0405-1018_6
python2 evaluation/evaluate_ate_scale_color_final_markBoth_Online.py evaluation/Ground_truth/EuRoC_left_cam/merged_GT_samples.txt kf_dataset-MH0405-1018_6.txt --plot kf_dateset-MH0405-100_6.pdf 9 Yunshu_Results/1018/deletedResults2/missingFramesFile_MH04.txt 6 Yunshu_Results/1018/deletedResults2/missingFramesFile_MH05.txt



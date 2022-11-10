./Examples/Stereo/stereo_kitti ./Vocabulary/ORBvoc.txt ./Examples/Stereo/KITTI00-02.yaml ../dataset/sequences/00/

./Examples/Monocular/mono_kitti ./Vocabulary/ORBvoc.txt ./Examples/Monocular/EuRoC.yaml ../dataset/sequences/00/


./Examples/Monocular/mono_euroc ./Vocabulary/ORBvoc.txt ./Examples/Monocular/EuRoC.yaml ../dataset/sequences/00/ ./Yunshu_Results/dataset/1114/deletedResults/00.txt dataset-00-1114


python2 evaluation/evaluate_ate_scale_color_final_markBoth_Online.py evaluation/Ground_truth/EuRoC_left_cam/merged_GT_samples.txt kf_dataset-MH05-1107_MH04_None_MH05_0-2200_0.txt --plot kf_dateset-MH05-100_0.pdf -1 Yunshu_Results/1107_MH04_None_MH05_0-2200/deletedResults2/missingFramesFile_MH04.txt 0 Yunshu_Results/1107_MH04_None_MH05_0-2200/deletedResults2/missingFramesFile_MH05.txt

python2 evaluation/evaluate_forDataset.py evaluation/Ground_truth/dataset/poses/00.txt CameraTrajectory.txt --plot CameraTrajectory_1114.pdf

python2 evaluation/evaluate_ate_scale_dataset.py evaluation/Ground_truth/dataset/poses/00.txt CameraTrajectory.txt --plot CameraTrajectory_1114.pdf

python2 evaluation/evaluate_ate_scale_dataset.py evaluation/Ground_truth/dataset/poses/00.txt KeyFrameTrajectory.txt --plot CameraTrajectory_1114_1.pdf

python2 evaluation/evaluate_ate_scale_dataset.py Ground_truth/dataset/xyzGroundTruth/00.txt KeyFrameTrajectory.txt --plot CameraTrajectory_1116_1.pdf

python2 evaluation/evaluate_ate_scale_dataset.py evaluation/Ground_truth/EuRoC_left_cam/merged_GT_samples.txt kf_dataset-MH0405_0909.txt --plot kf_0909.pdf


./Examples/Stereo/stereo_kitti ./Vocabulary/ORBvoc.txt ./Examples/Stereo/KITTI00-02.yaml ../dataset/sequences/06/

python2 evaluation/evaluate_ate_scale_dataset.py Ground_truth/dataset/xyzGroundTruth_withR/00.txt KeyFrameTrajectory.txt --plot CameraTrajectory_1117_0.pdf


python2 evaluation/evaluate_ate_scale_dataset.py Ground_truth/dataset/xyzGroundTruth/06.txt estimatedTrajactory/CameraTrajectory_06.txt --plot CameraTrajectory_1117_06.pdf

python2 evaluation/evaluate_ate_scale_dataset.py estimatedTrajactory/CameraTrajectory_06.txt Ground_truth/dataset/xyzGroundTruth/06.txt --plot CameraTrajectory_1117_06.pdf






./Examples/Monocular/mono_euroc_load_2 ./Vocabulary/ORBvoc.txt ./Examples/Monocular/EuRoC.yaml "$pathDatasetEuroc"/MH01 ./Examples/Monocular/EuRoC_TimeStamps/MH01.txt dataset-MH_testMerge_1129 ./MH04_1129.osa ./MH05_1129.osa

./Examples/Monocular/mono_euroc ./Vocabulary/ORBvoc.txt ./Examples/Monocular/EuRoC.yaml "$pathDatasetEuroc"/MH04 ./Examples/Monocular/EuRoC_TimeStamps/MH04.txt "$pathDatasetEuroc"/MH05 ./Examples/Monocular/EuRoC_TimeStamps/MH05.txt dataset-MH0405_0909

pathDatasetEuroc='/home/ucrnet/Desktop/workspace/slamdata'
./Examples/Monocular/mono_euroc_load_2 ./Vocabulary/ORBvoc.txt ./Examples/Monocular/EuRoC.yaml "$pathDatasetEuroc"/MH05 ./Examples/Monocular/EuRoC_TimeStamps/MH05.txt dataset-MH_testMerge_1129 ./MH04_1129.osa

python2 evaluation/evaluate_ate_scale_dataset.py evaluation/Ground_truth/EuRoC_left_cam/merged_GT_samples.txt KeyFrameTrajectory.txt --plot CameraTrajectory_1206.pdf


./Examples/Monocular/mono_euroc_load_2 ./Vocabulary/ORBvoc.txt ./Examples/Monocular/EuRoC.yaml "$pathDatasetEuroc"/MH04 ./Examples/Monocular/EuRoC_TimeStamps/MH04.txt "$pathDatasetEuroc"/MH05 ./Examples/Monocular/EuRoC_TimeStamps/MH05.txt dataset-MH0405_1207













./Examples/Monocular/mono_euroc_load_2 ./Vocabulary/ORBvoc.txt ./Examples/Monocular/EuRoC.yaml "$pathDatasetEuroc"/MH01 ./Examples/Monocular/EuRoC_TimeStamps/MH01.txt dataset-MH_testMerge_1129 ./MH04_1129.osa ./MH05_1129.osa

python2 evaluation/evaluate_ate_scale_dataset.py evaluation/Ground_truth/EuRoC_left_cam/merged_GT_samples.txt kf_dataset-MH_testMerge_1129.txt --plot kf_1129.pdf






./Examples/Monocular/mono_euroc_load_2 ./Vocabulary/ORBvoc.txt ./Examples/Monocular/EuRoC.yaml "$pathDatasetEuroc"/MH04 ./Examples/Monocular/EuRoC_TimeStamps/MH04.txt "$pathDatasetEuroc"/MH05 ./Examples/Monocular/EuRoC_TimeStamps/MH05.txt dataset-MH0405_1208












CS 135 demo
./Examples/Monocular/mono_euroc_load_2 ./Vocabulary/ORBvoc.txt ./Examples/Monocular/EuRoC.yaml "$pathDatasetEuroc"/MH04 ./Examples/Monocular/EuRoC_TimeStamps/MH04.txt "$pathDatasetEuroc"/MH05 ./Examples/Monocular/EuRoC_TimeStamps/MH05.txt dataset-MH0405_1208
python2 evaluation/evaluate_ate_scale_color_MarkAll.py evaluation/Ground_truth/EuRoC_left_cam/merged_GT_samples.txt kf_dataset-MH0405_1208.txt --plot kf_1208.pdf





./Examples/Monocular/mono_euroc_load_2_100images ./Vocabulary/ORBvoc.txt ./Examples/Monocular/EuRoC.yaml "$pathDatasetEuroc"/MH04 ./Examples/Monocular/EuRoC_TimeStamps/MH04.txt "$pathDatasetEuroc"/MH05 ./Examples/Monocular/EuRoC_TimeStamps/MH05.txt dataset-MH0405_1208
python2 evaluation/evaluate_ate_scale_color_MarkAll.py evaluation/Ground_truth/EuRoC_left_cam/merged_GT_samples.txt kf_dataset-MH0405_1208.txt --plot kf_1208.pdf




204 project:
flash-stack-8: 
pathDatasetEuroc='/home/adhak001/slam'
#for client
./Examples/Monocular/mono_euroc_load_2_100images ./Vocabulary/ORBvoc.txt ./Examples/Monocular/EuRoC.yaml "$pathDatasetEuroc"/mh04 ./Examples/Monocular/EuRoC_TimeStamps/MH04.txt "$pathDatasetEuroc"/MH05 ./Examples/Monocular/EuRoC_TimeStamps/MH05.txt dataset-MH0405_1208

or sudo ./Examples/Monocular/mono_euroc_load_2_100images ./Vocabulary/ORBvoc.txt ./Examples/Monocular/EuRoC.yaml '/home/adhak001/slam'/mh04 ./Examples/Monocular/EuRoC_TimeStamps/MH04.txt "$pathDatasetEuroc"/MH05 ./Examples/Monocular/EuRoC_TimeStamps/MH05.txt dataset-MH0405_1208

./Examples/Monocular/mono_euroc ./Vocabulary/ORBvoc.txt ./Examples/Monocular/EuRoC.yaml "$pathDatasetEuroc"/mh04 ./Examples/Monocular/EuRoC_TimeStamps/MH04.txt "$pathDatasetEuroc"/MH05 ./Examples/Monocular/EuRoC_TimeStamps/MH05.txt dataset-MH0405_0909


or
./Examples/Monocular/mono_euroc_load_2 ./Vocabulary/ORBvoc.txt ./Examples/Monocular/EuRoC.yaml "$pathDatasetEuroc"/MH04 ./Examples/Monocular/EuRoC_TimeStamps/MH04.txt "$pathDatasetEuroc"/MH05 ./Examples/Monocular/EuRoC_TimeStamps/MH05.txt dataset-MH0405_1208


flashstack-7:
#for server
./Examples/Monocular/mono_euroc_load_2_server ./Vocabulary/ORBvoc.txt ./Examples/Monocular/EuRoC.yaml "$pathDatasetEuroc"/MH04 ./Examples/Monocular/EuRoC_TimeStamps/MH04.txt "$pathDatasetEuroc"/MH05 ./Examples/Monocular/EuRoC_TimeStamps/MH05.txt dataset-MH0405_1207



Local:
./Examples/Monocular/mono_euroc_load_2_100images ./Vocabulary/ORBvoc.txt ./Examples/Monocular/EuRoC.yaml "$pathDatasetEuroc"/MH04 ./Examples/Monocular/EuRoC_TimeStamps/MH04.txt "$pathDatasetEuroc"/MH05 ./Examples/Monocular/EuRoC_TimeStamps/MH05.txt dataset-MH0405_1207






#small map 
 ./Examples/Monocular/mono_euroc_load_2-load1Do2 ./Vocabulary/ORBvoc.txt ./Examples/Monocular/EuRoC.yaml "$pathDatasetEuroc"/MH05 ./Examples/Monocular/EuRoC_TimeStamps/MH05.txt dataset-MH_testMerge_1129 ./0.osa

./Examples/Monocular/mono_euroc ./Vocabulary/ORBvoc.txt ./Examples/Monocular/EuRoC.yaml "$pathDatasetEuroc"/MH04 ./Examples/Monocular/EuRoC_TimeStamps/MH04.txt dataset-MH0405_0909

./Examples/Monocular/mono_euroc_load_2-load1Do2 ./Vocabulary/ORBvoc.txt ./Examples/Monocular/EuRoC.yaml "$pathDatasetEuroc"/MH04 ./Examples/Monocular/EuRoC_TimeStamps/MH04.txt dataset-MH_testMerge_1129 MH04-10.osa



./Examples/Monocular/mono_euroc ./Vocabulary/ORBvoc.txt ./Examples/Monocular/EuRoC.yaml "$pathDatasetEuroc"/MH05 ./Examples/Monocular/EuRoC_TimeStamps/MH05.txt "$pathDatasetEuroc"/MH04 ./Examples/Monocular/EuRoC_TimeStamps/MH04.txt dataset-MH0405_0909

./Examples/Monocular/mono_euroc_load_2-load1Do2 ./Vocabulary/ORBvoc.txt ./Examples/Monocular/EuRoC.yaml "$pathDatasetEuroc"/MH05 ./Examples/Monocular/EuRoC_TimeStamps/MH05.txt dataset-MH_testMerge_1129 results/smallmap/multiple6kf/smallmap0.osa

	#test ate
	~/Desktop/workspace/ORBSLAM3/Yunshu_programs$ python3 plotTime.py 

	#plot
	python2 evaluation/evaluate_ate_scale_color_MarkAll.py evaluation/Ground_truth/EuRoC_left_cam/merged_GT_samples.txt results/smallmap/first-trial/multiple6kf/baseline_half/smallmap3/kf_smallmap3.osa.txt --plot kf_1208.pdf



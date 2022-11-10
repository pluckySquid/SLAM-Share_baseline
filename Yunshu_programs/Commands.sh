pathDatasetEuroc='/home/ucrnet/Desktop/workspace/slamdata'

# run mono_euroc_load_2 when giving no arguments as the image input, where mono_euroc_load_2 has the hardcoded .osa file on line 103
./Examples/Monocular/mono_euroc_load_2 ./Vocabulary/ORBvoc.txt ./Examples/Monocular/EuRoC.yaml "$pathDatasetEuroc"/MH01 ./Examples/Monocular/EuRoC_TimeStamps/MH01.txt 



# run mono_euroc_load_2 when giving 4 arguments as the 2 images folder
./Examples/Monocular/mono_euroc_load_2 ./Vocabulary/ORBvoc.txt ./Examples/Monocular/EuRoC.yaml "$pathDatasetEuroc"/MH04 ./Examples/Monocular/EuRoC_TimeStamps/MH04.txt "$pathDatasetEuroc"/MH05 ./Examples/Monocular/EuRoC_TimeStamps/MH05.txt dataset-MH0405_1207



#For mono_euroc_load_2-load1Do2: load a .osa file, then read in images and then do merge.
./Examples/Monocular/mono_euroc_load_2-load1Do2 ./Vocabulary/ORBvoc.txt ./Examples/Monocular/EuRoC.yaml "$pathDatasetEuroc"/MH05 ./Examples/Monocular/EuRoC_TimeStamps/MH05.txt dataset-MH_testMerge_1129 ./MH04_1129.osa

#merging two maps with both given input
./Examples/Monocular/mono_euroc_load_2 ./Vocabulary/ORBvoc.txt ./Examples/Monocular/EuRoC.yaml "$pathDatasetEuroc"/MH01 ./Examples/Monocular/EuRoC_TimeStamps/MH01.txt dataset-MH_testMerge_1129 ./MH04_1129.osa ./MH05_1129.osa


#mono_euroc_load_2_100images for every 100 images read from both A and B, load the previews .osa file and then merge these 200 images
./Examples/Monocular/mono_euroc_load_2_100images ./Vocabulary/ORBvoc.txt ./Examples/Monocular/EuRoC.yaml "$pathDatasetEuroc"/MH04 ./Examples/Monocular/EuRoC_TimeStamps/MH04.txt "$pathDatasetEuroc"/MH05 ./Examples/Monocular/EuRoC_TimeStamps/MH05.txt dataset-MH0405_1207




#to use segment (Needs to change the start and end in segmengateImages_markExistence_online.py)
python2 ./Yunshu_programs/segmengateImages_markExistence_online.py 0210 100

./Examples/Monocular/mono_euroc ./Vocabulary/ORBvoc.txt ./Examples/Monocular/EuRoC.yaml "$pathDatasetEuroc"/MH04 ./Yunshu_Results/0210/deletedResults2/MH04_9_100.txt "$pathDatasetEuroc"/MH05 ./Yunshu_Results/0210/deletedResults2/MH05_9_100.txt dataset-MH0405-0210_MH04_0-1000_MH05_1000-2200_21

python2 evaluation/evaluate_ate_scale_color_final_markBoth_Online.py evaluation/Ground_truth/EuRoC_left_cam/merged_GT_samples.txt kf_dataset-MH0405-0210_MH04_0-1000_MH05_1000-2200_21.txt --plot kf_dataset-MH0405-100_21.pdf 9 Yunshu_Results/0210/deletedResults2/missingFramesFile_MH04.txt 0 Yunshu_Results/0210/deletedResults2/missingFramesFile_MH05.txt


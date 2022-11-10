pathDatasetEuroc='/home/ucrnet/Desktop/workspace/slamdata'

# run mono_euroc_load_2 when giving no arguments as the image input, where mono_euroc_load_2 has the hardcoded .osa file on line 103
./Examples/Monocular/mono_euroc_load_2 ./Vocabulary/ORBvoc.txt ./Examples/Monocular/EuRoC.yaml "$pathDatasetEuroc"/MH01 ./Examples/Monocular/EuRoC_TimeStamps/MH01.txt 



# run mono_euroc_load_2 when giving 4 arguments as the 2 images folder
./Examples/Monocular/mono_euroc_load_2 ./Vocabulary/ORBvoc.txt ./Examples/Monocular/EuRoC.yaml "$pathDatasetEuroc"/MH04 ./Examples/Monocular/EuRoC_TimeStamps/MH04.txt "$pathDatasetEuroc"/MH05 ./Examples/Monocular/EuRoC_TimeStamps/MH05.txt dataset-MH0405_1207



#For mono_euroc_load_2-load1Do2: load a .osa file, then read in images and then do merge.
./Examples/Monocular/mono_euroc_load_2-load1Do2 ./Vocabulary/ORBvoc.txt ./Examples/Monocular/EuRoC.yaml "$pathDatasetEuroc"/MH05 ./Examples/Monocular/EuRoC_TimeStamps/MH05.txt dataset-MH_testMerge_1129 ./MH04_1129.osa


#mono_euroc_load_2_100images for every 100 images read from both A and B, load the previews .osa file and then merge these 200 images
./Examples/Monocular/mono_euroc_load_2_100images ./Vocabulary/ORBvoc.txt ./Examples/Monocular/EuRoC.yaml "$pathDatasetEuroc"/MH04 ./Examples/Monocular/EuRoC_TimeStamps/MH04.txt "$pathDatasetEuroc"/MH05 ./Examples/Monocular/EuRoC_TimeStamps/MH05.txt dataset-MH0405_1207





./Examples/Monocular/mono_euroc ./Vocabulary/ORBvoc.txt ./Examples/Monocular/EuRoC.yaml "$pathDatasetEuroc"/MH04 ./Examples/Monocular/EuRoC_TimeStamps/MH04.txt dataset-MH04-0909


./Examples/Monocular/mono_euroc_load_2_server ./Vocabulary/ORBvoc.txt ./Examples/Monocular/EuRoC.yaml "$pathDatasetEuroc"/MH04 ./Examples/Monocular/EuRoC_TimeStamps/MH04.txt "$pathDatasetEuroc"/MH05 ./Examples/Monocular/EuRoC_TimeStamps/MH05.txt dataset-MH0405_1207





/home/adhak001/slam/mh04
echo MH04-3 | ./Examples/Monocular/mono_euroc ./Vocabulary/ORBvoc.txt ./Examples/Monocular/EuRoC.yaml ./home/adhak001/slam/mh04 ./0324/MH04_3_100.txt dataset-MH04-0326_003

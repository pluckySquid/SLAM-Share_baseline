#!/bin/bash
pathDatasetEuroc='/home/xukan/Desktop/workspace/slamdata' #Example, it is necesary to change it by the dataset path

#------------------------------------
# Monocular Examples
#echo "Launching MH01 with Monocular sensor"
#./Examples/Monocular/mono_euroc ./Vocabulary/ORBvoc.txt ./Examples/Monocular/EuRoC.yaml "$pathDatasetEuroc"/MH01 ./Examples/Monocular/EuRoC_TimeStamps/MH01.txt "$pathDatasetEuroc"/MH02_small ./Examples/Monocular/EuRoC_TimeStamps/MH02_small.txt dataset-MH01_mono
#!/bin/bash
pathDatasetEuroc='/home/xukan/Desktop/workspace/slamdata' #Example, it is necesary to change it by the dataset path

#------------------------------------
# Monocular Examples
echo "Launching MH01 with Monocular sensor"
./Examples/Monocular/mono_euroc_load_2 ./Vocabulary/ORBvoc.txt ./Examples/Monocular/EuRoC.yaml "$pathDatasetEuroc"/MH02_small ./Examples/Monocular/EuRoC_TimeStamps/MH02_small.txt dataset-MH_testMerge_0809

import mono_euroc
import evaluate_ate_scale_color_MarkRed
import os

pathDataORBSLAM3='/home/ucrnet/Desktop/workspace/ORBSLAM3/'
pathDatasetEuroc='/home/ucrnet/Desktop/workspace/slamdata'
os.chdir(pathDataORBSLAM3)
f1 = open(path+"Vocabulary/ORBvoc.txt", "r")
f2 = open(path+"Examples/Monocular/EuRoC.yaml", "r")
f3 = open(path+"Yunshu_Results/0915/testSmall/MH04_0.txt", "r")
f4 = open(path+"Examples/Monocular/EuRoC_TimeStamps/MH05.txt", "r")
f4 = open(path+"Examples/Monocular/EuRoC_TimeStamps/MH05.txt", "r")


mono_euroc(f1, f2, "$pathDatasetEuroc/MH04", f3, "$pathDatasetEuroc/MH05", f4, "dataset-MH0405-0915_0_missingFrames")
#mono_euroc(./Examples/Monocular/mono_euroc ./Vocabulary/ORBvoc.txt ./Examples/Monocular/EuRoC.yaml "$pathDatasetEuroc"/MH04 ./Yunshu_Results/0915/deletedResults/MH04_0.txt "$pathDatasetEuroc"/MH05 ./Examples/Monocular/EuRoC_TimeStamps/MH05.txt dataset-MH0405-0915_0 )

evaluate_ate_scale_color_MarkRed("evaluation/Ground_truth/EuRoC_left_cam/merged_GT_samples.txt", "kf_dataset-MH0405-0915_0.txt", "--plot", "kf_dataset-MH0405-0915_0_missingFrames.txt" "--plot" "kf_dateset-MH0405-0915_0.pdf")

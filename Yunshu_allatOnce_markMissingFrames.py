import Examples/Monocular/mono_euroc
import evaluation/evaluate_ate_scale_color_MarkRed

mono_euroc(./Vocabulary/ORBvoc.txt ./Examples/Monocular/EuRoC.yaml "$pathDatasetEuroc"/MH04 ./Yunshu_Results/0915/testSmall/MH04_0.txt "$pathDatasetEuroc"/MH05 ./Examples/Monocular/EuRoC_TimeStamps/MH05.txt dataset-MH0405-0915_0_missingFrames)
mono_euroc(./Examples/Monocular/mono_euroc ./Vocabulary/ORBvoc.txt ./Examples/Monocular/EuRoC.yaml "$pathDatasetEuroc"/MH04 ./Yunshu_Results/0915/deletedResults/MH04_0.txt "$pathDatasetEuroc"/MH05 ./Examples/Monocular/EuRoC_TimeStamps/MH05.txt dataset-MH0405-0915_0 )

evaluate_ate_scale_color_MarkRed(evaluation/Ground_truth/EuRoC_left_cam/merged_GT_samples.txt kf_dataset-MH0405-0915_0.txt --plot kf_dataset-MH0405-0915_0_missingFrames.txt --plot kf_dateset-MH0405-0915_0.pdf)

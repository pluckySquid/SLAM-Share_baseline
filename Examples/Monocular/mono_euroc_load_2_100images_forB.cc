/**
* This file is part of ORB-SLAM3
*
* Copyright (C) 2017-2020 Carlos Campos, Richard Elvira, Juan J. Gómez Rodríguez, José M.M. Montiel and Juan D. Tardós, University of Zaragoza.
* Copyright (C) 2014-2016 Raúl Mur-Artal, José M.M. Montiel and Juan D. Tardós, University of Zaragoza.
*
* ORB-SLAM3 is free software: you can redistribute it and/or modify it under the terms of the GNU General Public
* License as published by the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*
* ORB-SLAM3 is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even
* the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License along with ORB-SLAM3.
* If not, see <http://www.gnu.org/licenses/>.
*/



#include<iostream>
#include<algorithm>
#include<fstream>
#include<chrono>
#include <sys/time.h>
#include <time.h>

#include<opencv2/core/core.hpp>

#include<System.h>

using namespace std;

void LoadImages(const string &strImagePath, const string &strPathTimes,
                vector<string> &vstrImages, vector<double> &vTimeStamps);

int main(int argc, char **argv)
{
    if(argc < 5)
    {
        cerr << endl << "Usage: ./mono_euroc_load_2 path_to_vocabulary path_to_settings path_to_sequence_folder_1 path_to_times_file_1 (path_to_image_folder_2 path_to_times_file_2 ... path_to_image_folder_N path_to_times_file_N) (trajectory_file_name)" << endl;
        return 1;
    }

    const int num_seq = (argc-3)/2;
    cout << "num_seq = " << num_seq << endl;
    bool bFileName= (((argc-3) % 2) == 1);
    string file_name;
    double firstTime = 0;
    double loadTimeSeq[2] = {0,0};
    double saveTimeSeq = 0;
    //double saveTimeSeq[2] = [0, 0];

    if (bFileName)
    {
        file_name = string(argv[argc-1]);
        cout << "file name: " << file_name << endl;
    }

    // Load all sequences:
    int seq;
    vector< vector<string> > vstrImageFilenames;
    vector< vector<double> > vTimestampsCam;
    vector<int> nImages;

    vstrImageFilenames.resize(num_seq);
    vTimestampsCam.resize(num_seq);
    nImages.resize(num_seq);



    struct timeval start0, end0, loadTempStart, loadTempEnd;


    int tot_images = 0;
    for (seq = 0; seq<num_seq; seq++)
    {
        cout << "Loading images for sequence " << seq << "...";
        gettimeofday(&start0, NULL);
        LoadImages(string(argv[(2*seq)+3]) + "/mav0/cam0/data", string(argv[(2*seq)+4]), vstrImageFilenames[seq], vTimestampsCam[seq]);
        gettimeofday(&end0, NULL);
        double elapsed = ((end0.tv_sec - start0.tv_sec) * 1000) + (end0.tv_usec / 1000 - start0.tv_usec / 1000);
        loadTimeSeq[seq] = elapsed;
        cout << "LOADED!" << endl;

        nImages[seq] = vstrImageFilenames[seq].size();
        tot_images += nImages[seq];
    }

    // Vector for tracking time statistics
    vector<float> vTimesTrack;
    vTimesTrack.resize(tot_images);

    cout << endl << "-------" << endl;
    cout.precision(17);


    gettimeofday(&start0, NULL);
    // Create SLAM system. It initializes all system threads and gets ready to process frames.
    //ORB_SLAM3::System SLAM(argv[1],argv[2],ORB_SLAM3::System::MONOCULAR, true);
    //ORB_SLAM3::System SLAM(argv[1],argv[2],ORB_SLAM3::System::MONOCULAR, true, 0, "", "./04262021_2maps.osa", "./04262021_2maps.osa");
   //ORB_SLAM3::System SLAM(argv[1],argv[2],ORB_SLAM3::System::MONOCULAR, true, 0, "", "./MH04_0909.osa", "./MH05_0909.osa" );

  // ORB_SLAM3::System SLAM(argv[1],argv[2],ORB_SLAM3::System::MONOCULAR, true, 0, "", "./tempB0.osa", "./MH05_0909.osa" );
    ORB_SLAM3::System SLAM(argv[1],argv[2],ORB_SLAM3::System::MONOCULAR, true);
   /// ORB_SLAM3::System SLAM_2(argv[1],argv[2],ORB_SLAM3::System::MONOCULAR, true);

    cout << "loaded both" << " ******************* " << endl;

  //  ORB_SLAM3::System SLAM(argv[1],argv[2],ORB_SLAM3::System::MONOCULAR, true, 0, "", "./testmap.osa");



        // Main loop
    cv::Mat im;
    int proccIm = 0;
    seq = 0;
    for(int ni=0; ni<nImages[0]; ni++, proccIm++)
    {
            // *********************** Yunshu ************************************//
                        // load the binary file is the same as the buffer, so all we need is to load the binary file but not need to update the buffer because they are the same

                        cout << "ni:  " << ni << " ******************* " << endl;


            if(ni % 100 == 0 && ni> 0 )
            {
                //read .osa file
                cout << "*****************read .osa file:  " << " ******************* " << endl;

               // gettimeofday(&loadTempStart, NULL);
               cout << "ni / 100 - 1:  " << "temp" + std::to_string(ni / 100 - 1) + ".osa" << " ******************* " << endl;
               //bool isRead = SLAM.LoadAtlas("MH05_0909.osa",1);
                bool isRead = SLAM.LoadAtlas_second("tempB" + std::to_string(ni / 100 - 1) + ".osa",1);

                cout << "*****************LoadAtlas is done, now set loadMap:  " << " ******************* " << endl;

               SLAM.setLoadMap_Yunshu (isRead);
               cout << "------press enter to continue------" << endl;
           	string tmp;
              	getline(cin,tmp);

              SLAM.ChangeTempMap_Yunshu(isRead);

    //            cout << "------press enter to continue------" << endl;

    //            	getline(cin,tmp);

  //std::getline (std::cin, no);                //ORB_SLAM3::System SLAM(argv[1],argv[2],ORB_SLAM3::System::MONOCULAR, true, 0, "temp.osa" );
            //   SLAM.MergeTwoMaps_Yunshu();

                gettimeofday(&loadTempEnd, NULL);
                double elapsed = ((loadTempEnd.tv_sec - loadTempStart.tv_sec) * 1000) + (loadTempEnd.tv_usec / 1000 - loadTempStart.tv_usec / 1000);
                cout << "*****************Load map elapsed time:  " << elapsed << " ******************* " << endl;

                //SLAM.ChangeDataset();
                cout << "*****************dataset changed" << " ******************* " << endl;

            }
            // *********************** Yunshu ************************************//


            // Read image from file ********** Do A
            im = cv::imread(vstrImageFilenames[seq][ni],CV_LOAD_IMAGE_UNCHANGED);
            double tframe = vTimestampsCam[seq][ni];


            //cout << "Here:  "  << " ******************* " << endl;

            if(im.empty())
            {
                cerr << endl << "Failed to load image at: "
                     <<  vstrImageFilenames[seq][ni] << endl;
                return 1;
            }

    #ifdef COMPILEDWITHC11
            std::chrono::steady_clock::time_point t1 = std::chrono::steady_clock::now();
    #else
            std::chrono::monotonic_clock::time_point t1 = std::chrono::monotonic_clock::now();
    #endif

            // Pass the image to the SLAM system
            // cout << "tframe = " << tframe << endl;
           // cout << "Here1:  "  << " ******************* " << endl;

            SLAM.TrackMonocular(im,tframe); // TODO change to monocular_inertial
           // cout << "Here2:  "  << " ******************* " << endl;

    #ifdef COMPILEDWITHC11
            //cout << "Here7:  "  << " ******************* " << endl;

            std::chrono::steady_clock::time_point t2 = std::chrono::steady_clock::now();
    #else
            std::chrono::monotonic_clock::time_point t2 = std::chrono::monotonic_clock::now();
           // cout << "Here8:  "  << " ******************* " << endl;

    #endif
            //cout << "Here6:  "  << " ******************* " << endl;

            double ttrack= std::chrono::duration_cast<std::chrono::duration<double> >(t2 - t1).count();

            vTimesTrack[ni]=ttrack;

            // Wait to load the next frame
            double T=0;
            if(ni<nImages[seq]-1)
                T = vTimestampsCam[seq][ni+1]-tframe;
            else if(ni>0)
                T = tframe-vTimestampsCam[seq][ni-1];

            if(ttrack<T)
                usleep((T-ttrack)*1e6); // 1e6

                    //************Yunshu************

                    //cout << "ni: " << ni << endl;
            //cout << "Here5:  "  << " ******************* " << endl;


            if(ni % 2000 == 1999 && ni > 0)
            {


                cout << "Changing the dataset" << endl;

                       // SLAM.ChangeDataset();
                // Read image from file ********** Do B

                   //SLAM.ChangeDataset();

                   cout << "ni % 100: " << ni  % 100<< endl;
                //   SLAM.Shutdown();

             //      SLAM.SaveAtlas_Yunshu("B" + std::to_string(ni / 100));


                //save osa file


                //SLAM.Shutdown();

            }
    //************Yunshu************



    //    if(seq < num_seq - 1)
   //     {

    //        gettimeofday(&end0, NULL);
    //        double elapsed = ((end0.tv_sec - start0.tv_sec) * 1000) + (end0.tv_usec / 1000 - start0.tv_usec / 1000);
     //       cout << "*****************First elapsed time:  " << elapsed << " ******************* " << endl;
    //        cout << endl << " *** Ready for the second trajectory? ***";
     //       string saveFileName;
     //       getline(cin,saveFileName);


    //        cout << "Changing the dataset" << endl;
//
     //       SLAM.ChangeDataset();

     //       firstTime = elapsed;

        //    gettimeofday(&start0, NULL);
//

   //     }

    }
    // Stop all threads
    SLAM.Shutdown();

    gettimeofday(&end0, NULL);
    double elapsed = ((end0.tv_sec - start0.tv_sec) * 1000) + (end0.tv_usec / 1000 - start0.tv_usec / 1000);
    cout << "*****************Second elapsed time:  " << elapsed << " ******************* " << endl;


    cout << "*****************Total elapsed time:  " << firstTime + elapsed << " ******************* " << endl;
    // Save camera trajectory

    gettimeofday(&start0, NULL);
    if (bFileName)
    {
        const string kf_file =  "kf_" + string(argv[argc-1]) + ".txt";
        const string f_file =  "f_" + string(argv[argc-1]) + ".txt";
        SLAM.SaveTrajectoryEuRoC(f_file);
        SLAM.SaveKeyFrameTrajectoryEuRoC(kf_file);
    }
    else
    {
        SLAM.SaveTrajectoryEuRoC("CameraTrajectory.txt");
        SLAM.SaveKeyFrameTrajectoryEuRoC("KeyFrameTrajectory.txt");
    }
    gettimeofday(&end0, NULL);
    elapsed = ((end0.tv_sec - start0.tv_sec) * 1000) + (end0.tv_usec / 1000 - start0.tv_usec / 1000);
    saveTimeSeq = elapsed;
    cout << "*****************loading  time for seq1:  " << loadTimeSeq[0]  <<" ******************* " << endl;
    cout << "*****************loading  time for seq2:  " << loadTimeSeq[1]  <<" ******************* " << endl;
    cout << "*****************save  time:  " << saveTimeSeq << " ******************* " << endl;

    return 0;
    //save ends



}

void LoadImages(const string &strImagePath, const string &strPathTimes,
                vector<string> &vstrImages, vector<double> &vTimeStamps)
{
    ifstream fTimes;
    fTimes.open(strPathTimes.c_str());
    vTimeStamps.reserve(5000);
    vstrImages.reserve(5000);
    while(!fTimes.eof())
    {
        string s;
        getline(fTimes,s);
        if(!s.empty())
        {
            stringstream ss;
            ss << s;
            vstrImages.push_back(strImagePath + "/" + ss.str() + ".png");
            double t;
            ss >> t;
            vTimeStamps.push_back(t/1e9);

        }
    }
}

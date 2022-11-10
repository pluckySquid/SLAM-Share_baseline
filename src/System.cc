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



#include "System.h"
#include "Converter.h"
#include <thread>
#include <pangolin/pangolin.h>
#include <iomanip>
#include <openssl/md5.h>
#include <boost/serialization/base_object.hpp>
#include <boost/serialization/string.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/binary_iarchive.hpp>
#include <boost/archive/binary_oarchive.hpp>
#include <boost/archive/xml_iarchive.hpp>
#include <boost/archive/xml_oarchive.hpp>
#include <sys/time.h>
#include <time.h>


#define _XOPEN_SOURCE 700

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <signal.h>

#include <arpa/inet.h>
#include <fcntl.h>
#include <netdb.h>                      /* getprotobyname */
#include <netinet/in.h>
#include <sys/stat.h>
#include <sys/socket.h>
#include <unistd.h>


//volatile int signo_taken;
#define MAXFILES        1000000


namespace ORB_SLAM3
{

Verbose::eLevel Verbose::th = Verbose::VERBOSITY_NORMAL;

System::System(const string &strVocFile, const string &strSettingsFile, const eSensor sensor,
               const bool bUseViewer, const int initFr, const string &strSequence, const string &strLoadingFile, const string &strLoadingFile_second):
    mSensor(sensor), mpViewer(static_cast<Viewer*>(NULL)), mbReset(false), mbResetActiveMap(false),
    mbActivateLocalizationMode(false), mbDeactivateLocalizationMode(false)
{
    // Output welcome message
    cout << "strSettingsFile"<<  strSettingsFile <<
    "ORB-SLAM3 Copyright (C) 2017-2020 Carlos Campos, Richard Elvira, Juan J. Gómez, José M.M. Montiel and Juan D. Tardós, University of Zaragoza." << endl <<
    "ORB-SLAM2 Copyright (C) 2014-2016 Raúl Mur-Artal, José M.M. Montiel and Juan D. Tardós, University of Zaragoza." << endl <<
    "This program comes with ABSOLUTELY NO WARRANTY;" << endl  <<
    "This is free software, and you are welcome to redistribute it" << endl <<
    "under certain conditions. See LICENSE.txt." << endl << endl;

    cout << "Input sensor was set to: ";

    if(mSensor==MONOCULAR)
        cout << "Monocular" << endl;
    else if(mSensor==STEREO)
        cout << "Stereo" << endl;
    else if(mSensor==RGBD)
        cout << "RGB-D" << endl;
    else if(mSensor==IMU_MONOCULAR)
        cout << "Monocular-Inertial" << endl;
    else if(mSensor==IMU_STEREO)
        cout << "Stereo-Inertial" << endl;

    //Check settings file
    cv::FileStorage fsSettings(strSettingsFile.c_str(), cv::FileStorage::READ);
    if(!fsSettings.isOpened())
    {
       cerr << "Failed to open settings file at: " << strSettingsFile << endl;
       exit(-1);
    }

    bool loadedAtlas = false;

    //----
    //Load ORB Vocabulary
    //xukan commented /**/
   
/*
    //Create KeyFrame Database
    mpKeyFrameDatabase = new KeyFrameDatabase(*mpVocabulary);

    //Create the Atlas
    //mpMap = new Map();
    mpAtlas = new Atlas(0);*/
    //----


    struct timeval start0, start1, start2, start3, start4, start5, end0, mergeStart, mergeEnd;
    ofstream file_out;
    file_out.open("timeseris.txt", std::ios_base::app);

    gettimeofday(&start0, NULL);

    if(strLoadingFile.empty())
    {
        
        //Load ORB Vocabulary
	cout << "In if strLoadingFile.empty()" << endl;

     cout << endl << "Loading ORB Vocabulary. This could take a while..." << endl;

    mpVocabulary = new ORBVocabulary();
    bool bVocLoad = mpVocabulary->loadFromTextFile(strVocFile);
    if(!bVocLoad)
    {
        cerr << "Wrong path to vocabulary. " << endl;
        cerr << "Falied to open at: " << strVocFile << endl;
        exit(-1);
    }
    cout << "Vocabulary loaded!" << endl << endl;

        //Create KeyFrame Database
        mpKeyFrameDatabase = new KeyFrameDatabase(*mpVocabulary);

        //Create the Atlas
        //mpMap = new Map();
        mpAtlas = new Atlas(0);

    }
    else
    {
        //Load ORB Vocabulary
	cout << "In if else strLoadingFile.empty()" << endl;

     cout << endl << "Loading ORB Vocabulary. This could take a while..." << endl;

    mpVocabulary = new ORBVocabulary();
    bool bVocLoad = mpVocabulary->loadFromTextFile(strVocFile);
    if(!bVocLoad)
    {
        cerr << "Wrong path to vocabulary. " << endl;
        cerr << "Falied to open at: " << strVocFile << endl;
        exit(-1);
    }
    cout << "Vocabulary loaded!" << endl << endl;
        gettimeofday(&start1, NULL);
        // Load the file with an earlier session
	//clock_t start = clock();
	struct timeval start, end;
	//gettimeofday(&start2, NULL);
mpKeyFrameDatabase = new KeyFrameDatabase(*mpVocabulary);

        //clock_t start = clock();
        
gettimeofday(&start3, NULL);
    gettimeofday(&start0, NULL);

    
    file_out << "Merging two maps, first load start time at: " << start3.tv_sec  * 1000000 + start3.tv_usec << endl;

        bool isRead = LoadAtlas(strLoadingFile,BINARY_FILE);


        if(!isRead)
        {
            cout << "Error to load the file, please try with other session file or vocabulary file" << endl;
            exit(-1);
        }
       // YUnshu Commented
        //mpKeyFrameDatabase = new KeyFrameDatabase(*mpVocabulary);


        cout << "atlas is done loading. need postload"<< endl;


        mpAtlas->PostLoad();
        //cout << "KF in DB: " << mpKeyFrameDatabase->mnNumKFs << "; words: " << mpKeyFrameDatabase->mnNumWords << endl;

        loadedAtlas = true;
        cout << "atlas is done loading. postload is done"<< endl;
        //cout << "1. first load atlas map mpAtlas->GetAllKeyFrames().size(): " << mpAtlas->GetAllKeyFrames().size() << endl;

        mpAtlas->CreateNewMap();

        //clock_t timeElapsed = clock() - start;
        //unsigned msElapsed = timeElapsed / (CLOCKS_PER_SEC / 1000);
        //cout << "Binary file read in " << msElapsed << " ms" << endl;
	gettimeofday(&end, NULL);
	double elapsed = ((end.tv_sec - start.tv_sec) * 1000)
        	+ (end.tv_sec / 1000 - start.tv_sec / 1000);


    
    //file_out.open("timeseris.txt", std::ios_base::app);
    file_out << "Merging two maps, first load finish time at: " << end.tv_sec  * 1000000 + end.tv_usec << endl;

    double e = (end.tv_sec * 1000000 + end.tv_usec)  - (start3.tv_sec * 1000000 + start3.tv_usec );
    file_out << "Merging two maps, first loading takes: " << e << endl;


	cout << "elapsed time in loading .bin file: " << elapsed << endl;

        //usleep(10*1000*1000);
	vector<Map*> vm = mpAtlas->GetAllMaps();

    cout << "first load atlas map mpAtlas->GetAllKeyFrames().size(): " << mpAtlas->GetAllKeyFrames().size() << endl;
	cout << "first load atlas map size: " << vm.size() << endl;
	cout << "------press enter to continue------" << endl;
	string tmp;
    for(int i = 0; i < vm.size(); i++){
    		//mpAtlas->CreateNewMap();//old map, not _second
    		Map* m = vm[i];
    		cout << "m->GetAllKeyFrames(): " << m->GetAllKeyFrames().size()<< endl;
    }
    


    	//getline(cin,tmp);
    }


    if (mSensor==IMU_STEREO || mSensor==IMU_MONOCULAR)
        mpAtlas->SetInertialSensor();

    //Create Drawers. These are used by the Viewer
    mpFrameDrawer = new FrameDrawer(mpAtlas);
    mpMapDrawer = new MapDrawer(mpAtlas, strSettingsFile);

    //Initialize the Tracking thread
    //(it will live in the main thread of execution, the one that called this constructor)
    cout << "Seq. Name: " << strSequence << endl;
    mpTracker = new Tracking(this, mpVocabulary, mpFrameDrawer, mpMapDrawer,
                             mpAtlas, mpKeyFrameDatabase, strSettingsFile, mSensor, strSequence);
                             
    //Initialize the Local Mapping thread and launch
    mpLocalMapper = new LocalMapping(this, mpAtlas, mSensor==MONOCULAR || mSensor==IMU_MONOCULAR, mSensor==IMU_MONOCULAR || mSensor==IMU_STEREO, strSequence);
    mptLocalMapping = new thread(&ORB_SLAM3::LocalMapping::Run,mpLocalMapper);
    mpLocalMapper->mInitFr = initFr;
    mpLocalMapper->mThFarPoints = fsSettings["thFarPoints"];


    // mpLocalMapper1 = new LocalMapping(this, mpAtlas_small, mSensor==MONOCULAR || mSensor==IMU_MONOCULAR, mSensor==IMU_MONOCULAR || mSensor==IMU_STEREO, strSequence);
    // mptLocalMapping = new thread(&ORB_SLAM3::LocalMapping::Run,mpLocalMapper1);
    // mpLocalMapper1->mInitFr = initFr;
    // mpLocalMapper1->mThFarPoints = fsSettings["thFarPoints"];
    // if(mpLocalMapper1->mThFarPoints!=0)
    // {
    //     cout << "Discard points further than " << mpLocalMapper1->mThFarPoints << " m from current camera" << endl;
    //     mpLocalMapper1->mbFarPoints = true;
    // }
    // else
    //     mpLocalMapper1->mbFarPoints = false;



    if(mpLocalMapper->mThFarPoints!=0)
    {
        cout << "Discard points further than " << mpLocalMapper->mThFarPoints << " m from current camera" << endl;
        mpLocalMapper->mbFarPoints = true;
    }
    else
        mpLocalMapper->mbFarPoints = false;

    //Initialize the Loop Closing thread and launch
    // mSensor!=MONOCULAR && mSensor!=IMU_MONOCULAR
    mpLoopCloser = new LoopClosing(mpAtlas, mpKeyFrameDatabase, mpVocabulary, mSensor!=MONOCULAR); // mSensor!=MONOCULAR);
    mpLoopCloser1 = new LoopClosing(mpAtlas_small, mpKeyFrameDatabase, mpVocabulary, mSensor!=MONOCULAR); // mSensor!=MONOCULAR);

    mptLoopClosing = new thread(&ORB_SLAM3::LoopClosing::Run, mpLoopCloser);
    mptLoopClosing1 = new thread(&ORB_SLAM3::LoopClosing::Run, mpLoopCloser1);


    //Initialize the Viewer thread and launch
    if(bUseViewer)
    {
        mpViewer = new Viewer(this, mpFrameDrawer,mpMapDrawer,mpTracker,strSettingsFile);
        mptViewer = new thread(&Viewer::Run, mpViewer);
        mpTracker->SetViewer(mpViewer);
        mpLoopCloser->mpViewer = mpViewer;
        mpViewer->both = mpFrameDrawer->both;
    }

    //Set pointers between threads
    mpTracker->SetLocalMapper(mpLocalMapper);
    mpTracker->SetLoopClosing(mpLoopCloser);

    mpLocalMapper->SetTracker(mpTracker);
    mpLocalMapper->SetLoopCloser(mpLoopCloser);

    mpLoopCloser->SetTracker(mpTracker);
    mpLoopCloser->SetLocalMapper(mpLocalMapper);



        //YUnshu add for actually load map A
        
    // vector<Map*> vm = mpAtlas->GetAllMaps();
    //     for(int i = 0; i < vm.size(); i++){

    // 		Map* m = vm[i];
    // 		mpAtlas->GetCurrentMap()->mpKFlowerID = m->mpKFlowerID;	
    // 		mpAtlas->SetReferenceMapPoints(m->GetReferenceMapPoints());

    // 	    }

    //         int counter = 0;
    //         int addingKFs = 0;
    // 	    for(int i = 0; i < vm.size(); i++){
    // 		    Map* m = vm[i];
    // 		    std::vector<KeyFrame*> vkf = m->GetAllKeyFrames();
    //             int numofKF = vkf.size();
                
    //     		for(auto k : vkf){
    //                 mpLoopCloser->InsertKeyFrame(k);
    //                 cout << "counter now is: " << counter << endl;
    //                 addingKFs++;

    //                 counter++;
    //                 cout << " mpAtlas->GetAllMapPoints().size() " << mpAtlas->GetAllMapPoints().size()<<endl;

    //     		}
	//        }

    //        while(1){
    //            cout << "addingKFs: " << addingKFs <<endl;
    //            cout << "mpLoopCloser->totalKeyframesInsertion: " << mpLoopCloser->totalKeyframesInsertion <<endl;
    //            cout<< "howManyCorrectLoops: " << mpLoopCloser->howManyCorrectLoops << endl;
 
    //             if(mpLoopCloser->totalKeyframesInsertion < addingKFs){
    //                 cout<< "just waiting " << mpLoopCloser->totalKeyframesInsertion<<endl;
    //                 cout<< "howManyCorrectLoops: " << mpLoopCloser->howManyCorrectLoops << endl;
    //                 usleep(1000);
    //             }                    
    //             else{
    //                 cout<< "mpLoopCloser->totalKeyframesInsertion should be stopped: " << mpLoopCloser->totalKeyframesInsertion << endl;
    //                 file_out << "System breaks when correctLoops over: " << mpLoopCloser->howManyCorrectLoops << endl;                    
    //                 mpLoopCloser->RequestFinish();
    //                 break;
    //             }
    //        }
    //         cout << " mpAtlas->GetAllKeyFrames().size() " << mpAtlas->GetAllKeyFrames().size()<<endl;

    //         cout << " mpAtlas->GetAllMapPoints().size() " << mpAtlas->GetAllMapPoints().size()<<endl;
    //         //exit(0);
                //End



    Verbose::SetTh(Verbose::VERBOSITY_QUIET);

    if(!strLoadingFile_second.empty()){//second map
    //setLoadMap_Yunshu(true);
    //return ;
        gettimeofday(&start2, NULL);
        
    //file_out.open("timeseris.txt", std::ios_base::app);
    file_out << "Merging two maps, second load start time at: " << start2.tv_sec  * 1000000 + start2.tv_usec << endl;
                cout << " mpAtlas->GetAllKeyFrames().size() " << mpAtlas->GetAllKeyFrames().size()<<endl;

        bool isRead = LoadAtlas_second(strLoadingFile_second,BINARY_FILE);
    	cout << "***** second load starts*****, strLoadingFile_second: " << strLoadingFile_second << endl;
    	if(isRead){
                cout << " mpAtlas->GetAllMapPoints().size() " << mpAtlas->GetAllMapPoints().size()<<endl;

                mpAtlas_second->PostLoad_second();
    	    vector<Map*> vm = mpAtlas_second->GetAllMaps();
            cout << "total maps in mpAtlas_second: " << vm.size() <<endl;
//exit(0);
            gettimeofday(&start3, NULL);
    file_out << "Merging two maps, second load ends time at: " << start3.tv_sec  * 1000000 + start3.tv_usec << endl;
double e = (start3.tv_sec * 1000000 + start3.tv_usec)  - (start2.tv_sec * 1000000 + start2.tv_usec );
    file_out << "Merging two maps, second loading takes: " << e << endl;

    	    //create a new map to copy
    	    mpAtlas->CreateNewMap();
    	    //cout << "CountMaps(): " << mpAtlas_second->CountMaps() << endl;
    	    //cout << "***** second load 01***** vm size: " << vm.size() << endl;

    	    //mpAtlas->SetKeyFrameDababase(mpKeyFrameDatabase);
                //mpAtlas->SetORBVocabulary(mpVocabulary);
                gettimeofday(&mergeStart, NULL);
    	    for(int i = 0; i < vm.size(); i++){
    		//mpAtlas->CreateNewMap();//old map, not _second
    		Map* m = vm[i];
    		mpAtlas->GetCurrentMap()->mpKFlowerID = m->mpKFlowerID;
    		cout << "load_second 01" << endl;
    		for(auto k : m->GetAllKeyFrames()){
    	//	    mpAtlas->AddKeyFrame(k, true);//skip a buggy line in Map::AddKeyFrame

            }
    		cout << "load_second 02" << endl;

    		for(auto mp : m->GetAllMapPoints()){
                cout << " mpAtlas->GetAllMapPoints().size() " << mpAtlas->GetAllMapPoints().size()<<endl;
    	//	    mpAtlas->AddMapPoint(mp);
    		}
            //exit(0);
    		cout << "load_second 03" << endl;
    		mpAtlas->SetReferenceMapPoints(m->GetReferenceMapPoints());
    		cout << "load_second 04" << endl;
    	    }
    	    cout << "*******FINISHED FIRST STEP TO MERGE TWO MAPS*******" << endl;
            

            gettimeofday(&end0, NULL);
            int counter = 0;
            int addingKFs = 0;
    	    for(int i = 0; i < vm.size(); i++){
    		    Map* m = vm[i];
    		    std::vector<KeyFrame*> vkf = m->GetAllKeyFrames();
                int numofKF = vkf.size();
                
        		for(auto k : vkf){

                   // mpLoopCloser->InsertKeyFrame(k);
                    //if(counter >120 && counter <= 150){
                        if( counter < 250){
                    //    usleep(1000);
                        mpLoopCloser->InsertKeyFrame(k);
                            cout << "counter now is: " << counter << endl;
                            addingKFs++;
                    }
                    counter++;
                    cout << " mpAtlas->GetAllMapPoints().size() " << mpAtlas->GetAllMapPoints().size()<<endl;
                    //exit(0);
        		    //cout << "------press enter to continue------vkf size: " << vkf.size() << endl;
        		    //string tmp;
                    //getline(cin,tmp);
                    // while(true){
                    //     {
                    //         unique_lock<mutex> lock(mpLoopCloser->passedCheckingMutex);
                    //         if(!mpLoopCloser->passedChecking){
                    //             mpLoopCloser->InsertKeyFrame(k);
                    //             mpLoopCloser->passedChecking = true;
                    //             break;
                    //         }
                    //     }
                    //     usleep(1000);
                    // }
                    //usleep(100000);
                    //mpLoopCloser->InsertKeyFrame(k);
        		}
	       }

           //Yunshu commands: stop when keyframes added > addingKFSs or when number of correctLoops() > whenManyCorrectLoops
           int whenManyCorrectLoops = 7;
           cout << "addingKFs: " << addingKFs <<endl;
           cout << "mpLoopCloser->totalKeyframesInsertion: " << mpLoopCloser->totalKeyframesInsertion <<endl;
           //exit(0);
        //    while(1){
        //        cout << "addingKFs: " << addingKFs <<endl;
        //        cout << "mpLoopCloser->totalKeyframesInsertion: " << mpLoopCloser->totalKeyframesInsertion <<endl;
        //      usleep(1000);
        //    }
           while(1){
               cout << "addingKFs: " << addingKFs <<endl;
               cout << "mpLoopCloser->totalKeyframesInsertion: " << mpLoopCloser->totalKeyframesInsertion <<endl;
                if(mpLoopCloser->totalKeyframesInsertion < addingKFs){
                    cout<< "just waiting " << mpLoopCloser->totalKeyframesInsertion<<endl;
                    cout<< "howManyCorrectLoops: " << mpLoopCloser->howManyCorrectLoops << endl;
                    usleep(1000);
                }                    
                else{
                    cout<< "mpLoopCloser->totalKeyframesInsertion should be stopped: " << mpLoopCloser->totalKeyframesInsertion << endl;
                    file_out << "System breaks when correctLoops over: " << mpLoopCloser->howManyCorrectLoops << endl;                    
                    mpLoopCloser->RequestFinish();
                    break;
                }
                    

                if(mpLoopCloser->howManyCorrectLoops >= whenManyCorrectLoops){
                    file_out << "mpLoopCloser->totalKeyframesInsertion" <<mpLoopCloser->totalKeyframesInsertion << endl;
                    file_out << "System breaks when correctLoops over: " << mpLoopCloser->howManyCorrectLoops << endl;
                    mpLoopCloser->RequestFinish();
                    break;
                    
                }   
                //yunshu commented out last on July 18th 2022  
                //if(mpLoopCloser->mergeLocalFinished){
               //     mpLoopCloser->RequestFinish();
               //     break;
               // }
                //exit(0);
	       }
        //     mpLoopCloser->Run();
        //    for(int i = 0; i < vm.size(); i++){
    	// 	    Map* m = vm[i];
    	// 	    std::vector<KeyFrame*> vkf = m->GetAllKeyFrames();
        //         int numofKF = vkf.size();
        //         cout << "m->GetAllKeyFrames(): " << numofKF<< endl;
        // 		for(auto k : vkf){
        //                 if( counter < 250){

        //             mpLoopCloser->InsertKeyFrame(k);
        //                 cout << "counter now is: " << counter << endl;
        //                 addingKFs++;
        //             }
        //             counter++;
        //             cout << " mpAtlas->GetAllMapPoints().size() " << mpAtlas->GetAllMapPoints().size()<<endl;
               
        // 		}

                    
        //             //usleep(30000000);
        //             // break;
        //         cout<< "just waiting " << endl;
        //     }
	    }
        gettimeofday(&mergeEnd, NULL);
    double mergeTime = (mergeEnd.tv_sec * 1000000 + mergeEnd.tv_usec)  - (mergeStart.tv_sec * 1000000 + mergeStart.tv_usec );
    file_out << "entire merging time is: " << mergeTime<< endl;


        mpAtlas_second->clearAtlas();
        gettimeofday(&end0, NULL);
    file_out << "Merging two maps, merging finish time at: " << end0.tv_sec  * 1000000 + end0.tv_usec << endl;
    double e = (end0.tv_sec * 1000000 + end0.tv_usec)  - (start0.tv_sec * 1000000 + start0.tv_usec );
    file_out << "Merging two maps, second loading takes: " << e << endl;
    cout << "e value is: " << e<< endl;
    }
    string tmp_second;
    cout << " mpAtlas->GetAllKeyFrames().size() " << mpAtlas->GetAllKeyFrames().size()<<endl;
     
   // saveSmallAtlas();

}




void System::saveAllFiles() {
const string kf_file =  "kf_client.txt";
        const string f_file =  "f_client.txt";
        SaveTrajectoryEuRoC(f_file);
        SaveKeyFrameTrajectoryEuRoC(kf_file);
        //SaveAtlas_Yunshu("AB.osa");

}




int System::getAllKFSize(){
    return mpAtlas->GetAllKeyFrames().size();
}



// client


int System::client(int port, char * clientFileName) {
    int PORTSIZE = 5;
	struct addrinfo hints, *res;
	char *server_hostname = "169.235.26.43";
	char file_path[BUFSIZ];
	char *server_reply = NULL;
	char *user_input = NULL;
	char buffer[BUFSIZ];
	int filefd;
	int sockfd;
	struct stat st;
	ssize_t read_return;
	struct hostent *hostent;
	unsigned short server_port = 8080;
	char portNum[PORTSIZE];
	char remote_file[BUFSIZ];
	int select;
	char *client_server_files[MAXFILES];
	int i = 0;
	int j;

	// char filename_to_send[BUFSIZ];

	// if (argc != 3) {
	// 	fprintf(stderr, "Usage   ./client  <ip>  <port>\n");
	// 	exit (EXIT_FAILURE);
	// }

	// server_hostname = argv[1];
	//server_port = strtol(argv[2], NULL, 10);
    server_port = port;

    struct timeval start0;
    gettimeofday(&start0, NULL);
    ofstream file_out;
    file_out.open("timeseris.txt", std::ios_base::app);
    file_out << "client start sending time at: " << start0.tv_sec  * 1000000 + start0.tv_usec << endl;

	/* Prepare hint (socket address input). */
	//hostent = gethostbyname(server_hostname);
	

	memset(&hints, 0, sizeof hints);
	hints.ai_family = AF_INET;          // ipv4
	hints.ai_socktype = SOCK_STREAM;    // tcp
	hints.ai_flags = AI_PASSIVE;        // fill in my IP for me

	sprintf(portNum, "%d", server_port);
	getaddrinfo(server_hostname, portNum, &hints, &res);

	sockfd = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
	if (sockfd == -1) {
        printf("error: sockfd\n");
		perror("socket");


		//exit (EXIT_FAILURE);
	}

	/* Do the actual connection. */
	if (connect(sockfd, res->ai_addr, res->ai_addrlen) == -1) {
        printf("error: lost\n");
		perror("connect");
		//return EXIT_FAILURE;
	}

	
	

	// NOTES:
	// (1) instead of using signo_taken as is done, below there are alternate
	//     ways to handle signals with sigsetjmp and siglongjmp
	// (2) but the main reason to _not_ do this is to prevent the handler
	//     from messing up a file transfer
	//while (!signo_taken) {
		puts("connected to the server");


		while (1) {
			// NOTE: not a bug, but it helps the user to output the menu each
			// time

			printf("back again \n\n\n\n");

				memset(file_path, 0, sizeof file_path);
				//scanf("%s", file_path);
                //clientFileName = "/results/0531-forLast/MH04/MH04-0.osa";
                strcpy(file_path, clientFileName);
				printf("file_path %s\n", file_path);

				filefd = open(file_path, O_RDONLY);
				if (filefd == -1) {
					perror("open send file");
					// exit(EXIT_FAILURE);
					break;
				}

				// get the file's byte length
				if (fstat(filefd, &st) < 0) {
					perror("stat send file");
					// exit(EXIT_FAILURE);
					close(filefd);
					break;
				}


				// send file name to server
				memset(remote_file, 0, sizeof(remote_file));

				sprintf(remote_file, "%lld,%s", (long long) st.st_size,
						file_path);

				send(sockfd, remote_file, sizeof(remote_file), 0);

				


//std::stringstream ss;
//    boost::archive::binary_oarchive oa(ss);
//printf("ss.str().length() %d \n", ss.str().length());
 //   oa << mpAtlas;

//printf("oa,size() %d \n", oa.size());
  //  printf("ss.str().length() %d \n", ss.str().length());
//send(sockfd,ss.str().c_str(),ss.str().length(),0);
    
//exit(EXIT_FAILURE);
 //           oa << mpAtlas;


				while (1) {
					read_return = read(filefd, buffer, BUFSIZ);
                    //read_return = oa << mpAtlas;;
					if (read_return == 0)
						break;

					if (read_return == -1) {
						perror("read");
						// exit(EXIT_FAILURE);
						break;
					}

					if (write(sockfd, buffer, read_return) == -1) {
                        //https://cpp.hotexamples.com/examples/-/Socket/send/cpp-socket-send-method-examples.html
                           // Show::write("\n  client sent : " + std::string(buffer));
						perror("write");
						// exit(EXIT_FAILURE);
						break;
					}
                    printf("read_return %d \n", read_return);
				}

				close(filefd);


				if (i < MAXFILES)
					client_server_files[i++] = strdup(file_path);

                //printf("client_server_files ", sizeof(client_server_files) );

				puts("file complete");



                // struct timeval end0,
                // gettimeofday(&end0, NULL);
                // //std::string strMicroSec = lexical_cast<std::string>(end0.tv_sec);
                // ofstream file_out;
                // file_out.open("timeseris.txt", std::ios_base::app);
                // file_out << "server received time at: " << end0.tv_sec << endl;
                //printf("signo_taken ", signo_taken );
                free(user_input);
	free(server_reply);
close(sockfd);
	return 0;

				break;

                printf("back again 1\n\n\n\n");

			
			

		}
        free(user_input);
	free(server_reply);
	exit (EXIT_SUCCESS);
	
cout << "------press enter to continue 2------" << endl;
                string tmp;
               	getline(cin,tmp);
	
}





void System::server(){

// string pathSaveFileName = "./temp.osa";
//     std::remove(pathSaveFileName.c_str());

// char *data = new char[BUFSIZ];

// 	int received = recv(connect_socket, data, BUFSIZ, 0);

//  std::ofstream ofs(pathSaveFileName, std::ios::binary);
//              boost::archive::binary_oarchive oa(ofs);

//              oa << data;

}












void System::writeKeyframesize(){
    //write how many keyframes into log file_name
            ofstream file_out;
            file_out.open("log_result_online_100.txt", std::ios_base::app);
            file_out << "total keyframes: " << mpAtlas->GetAllKeyFrames().size() << endl;
}

void System::setLoadMap_Yunshu(bool isRead, string clientLoadingfile){
 //isRead = isread;

 //ChangeDataset();
  cout << "*****setLoadMap_Yunshu 0 " << endl;

//  vector<Map*> vpMaps = mpAtlas->GetAllMaps();
//     Map* pBiggerMap;
//     int numMaxKFs = 0;
//     for(Map* pMap :vpMaps)
//     {
//         mpKeyFrameDatabase -> clearMap(pMap);
//     }
//  cout << "*****setLoadMap_Yunshu 0.05 " << endl;

 
 //mpAtlas->PreSave();
 mpAtlas = new Atlas(0);
 cout << "*****setLoadMap_Yunshu 0.1 " << endl;

mpAtlas->clearMap();
 mpAtlas->clearAtlas();
 cout << "*****setLoadMap_Yunshu 0.5 " << endl;

 //mpAtlas->clearMap();

cout << "*****setLoadMap_Yunshu 1 " << endl;

///LoadAtlas("MH0405-10.osa", BINARY_FILE);
//Yunshu TODO
LoadAtlas("clientLoadingfile", BINARY_FILE);


cout << "*****setLoadMap_Yunshu 2 " << endl;
mpAtlas->PostLoad();
//mpAtlas->CreateNewMap();

mpLocalMapper->mInitFr = 0;

 cout << "*****first set ended " << endl;




}

bool System::MergeTwoMaps_Yunshu(string filename, int type){


LoadAtlas_second(filename,type);
        mpAtlas_second->PostLoad_second();

        vector<Map*> vm = mpAtlas_second->GetAllMaps();
   // mpAtlas->CreateNewMap();


   cout << "first load atlas map size: " << vm.size() << endl;

  //  mpAtlas->CreateNewMap();


    for(int i = 0; i < vm.size(); i++){
    //mpAtlas->CreateNewMap();//old map, not _second
    Map* m = vm[i];
    mpAtlas->GetCurrentMap()->mpKFlowerID = m->mpKFlowerID;
    cout << "load_second 01" << endl;
    for(auto k : m->GetAllKeyFrames()){
        mpAtlas->AddKeyFrame(k, true);//skip a buggy line in Map::AddKeyFrame
    }
    cout << "load_second 02" << endl;
    for(auto mp : m->GetAllMapPoints()){
        mpAtlas->AddMapPoint(mp);
    }
    cout << "load_second 03" << endl;
    mpAtlas->SetReferenceMapPoints(m->GetReferenceMapPoints());
    cout << "load_second 04" << endl;
    }
    cout << "*******FINISHED FIRST STEP TO MERGE TWO MAPS*******" << endl;
    for(int i = 0; i < vm.size(); i++){
        Map* m = vm[i];
        std::vector<KeyFrame*> vkf = m->GetAllKeyFrames();
        //vkf->UpdateConnections();
        int counter = 0;
        for(auto k : vkf){
            cout << "------counter: " << counter << endl;

            cout << "------k: " << k << endl;
            cout << "------vm.size() size: " << vm.size() << endl;
            cout << "------press enter to continue------vkf size: " << vkf.size() << endl;


            //string tmp;
            //getline(cin,tmp);
            
            while(true){
                {
                    //unique_lock<mutex> lock(mpLoopCloser->mMutexLoopQueue);
                    unique_lock<mutex> lockpassed(mpLoopCloser->passedCheckingMutex);

                    if(!mpLoopCloser->passedChecking){
                        cout << "!mpLoopCloser->passedChecking "  << !mpLoopCloser->passedChecking<< endl;

                        mpLoopCloser->InsertKeyFrame(k);
                        
                        mpLoopCloser->passedChecking = true;
                        break;
                    }
                }
                usleep(1000);
            }
            usleep(1000);
            //mpLoopCloser->InsertKeyFrame(k);..

            counter++;
          //  if (counter >= 10)
          //      break;
        }
        cout << "all keyframes has been added, total keyframes added: " << counter << endl;

    }



//mpAtlas->PostLoad();

//mpAtlas->CreateNewMap();

return true;

}

void System::ChangeTempMap_Yunshu(string B){



const int initFr = 0;


    LoadAtlas(B,BINARY_FILE);


        cout << "atlas is done loading. need postload"<< endl;


        mpAtlas->PostLoad();
        //cout << "KF in DB: " << mpKeyFrameDatabase->mnNumKFs << "; words: " << mpKeyFrameDatabase->mnNumWords << endl;

        

        //mpAtlas->CreateNewMap();


        LoadAtlas_second(B,BINARY_FILE);
    	//cout << "***** second load starts*****, strLoadingFile_second: " << strLoadingFile_second << endl;
    	if(true){

                mpAtlas_second->PostLoad_second();
    	    vector<Map*> vm = mpAtlas_second->GetAllMaps();
    	    //create a new map to copy
    	    mpAtlas->CreateNewMap();
    	    //cout << "CountMaps(): " << mpAtlas_second->CountMaps() << endl;
    	    //cout << "***** second load 01***** vm size: " << vm.size() << endl;

    	    //mpAtlas->SetKeyFrameDababase(mpKeyFrameDatabase);
                //mpAtlas->SetORBVocabulary(mpVocabulary);
    	    for(int i = 0; i < vm.size(); i++){
    		//mpAtlas->CreateNewMap();//old map, not _second
    		Map* m = vm[i];
    		mpAtlas->GetCurrentMap()->mpKFlowerID = m->mpKFlowerID;
    		cout << "load_second 01" << endl;
    		for(auto k : m->GetAllKeyFrames()){
    		    mpAtlas->AddKeyFrame(k, true);//skip a buggy line in Map::AddKeyFrame
    		}
    		cout << "load_second 02" << endl;
    		for(auto mp : m->GetAllMapPoints()){
    		    mpAtlas->AddMapPoint(mp);
    		}
    		cout << "load_second 03" << endl;
    		mpAtlas->SetReferenceMapPoints(m->GetReferenceMapPoints());
    		cout << "load_second 04" << endl;
    	    }
    	    cout << "*******FINISHED FIRST STEP TO MERGE TWO MAPS*******" << endl;
            
    	    for(int i = 0; i < vm.size(); i++){
    		    Map* m = vm[i];
    		    std::vector<KeyFrame*> vkf = m->GetAllKeyFrames();
        		for(auto k : vkf){
        		    //cout << "------press enter to continue------vkf size: " << vkf.size() << endl;
        		    //string tmp;
                    //getline(cin,tmp);
                    while(true){
                        {
                            unique_lock<mutex> lock(mpLoopCloser->passedCheckingMutex);
                            if(!mpLoopCloser->passedChecking){
                                mpLoopCloser->InsertKeyFrame(k);
                                mpLoopCloser->passedChecking = true;
                                break;
                            }
                        }
                        usleep(1000);
                    }
                    //usleep(100000);
                    //mpLoopCloser->InsertKeyFrame(k);
        		}
	       }
	    }

        cout << "Merging now done" << endl;
        const string kf_file =  "kf_server.txt";
        const string f_file =  "f_server.txt";
        SaveTrajectoryEuRoC(f_file);
        SaveKeyFrameTrajectoryEuRoC(kf_file);
        SaveAtlas_Yunshu("AB.osa");
    
    
    
    cout << "before mpAtlas clearMap " << endl;
        

            cout << "before mpAtlas_second clearMap " << endl;



//mpAtlas = new Atlas(0);
mpAtlas->clearMap();
        //mpAtlas_second->clearMap();

        cout << "Merging now done" << endl;
        cout << "mpAtlas->CountMaps();" << mpAtlas->CountMaps() << endl;

        mpAtlas->clearAtlas();
        mpAtlas_second->clearAtlas();
        
        
        

mpLocalMapper->mInitFr = initFr;


        return;

    



}


void System::deepCopyAtlas(Atlas* mpAtlas_temp, Atlas* mpAtlas){
    
}

// void System::deepCopyMappoints(MapPoint* mpAtlas_temp, Atlas* mpAtlas){
    
// }


void System::saveSmallAtlas(int num){
//just for ate experiment:
    mpLocalMapper->RequestFinish();
    mpLoopCloser->RequestFinish();
    if(mpViewer)
    {
        mpViewer->RequestFinish();
        while(!mpViewer->isFinished())
            usleep(5000);
    }
    

    // Wait until all thread have effectively stopped
    while(!mpLocalMapper->isFinished() || !mpLoopCloser->isFinished() || mpLoopCloser->isRunningGBA())
    {
        if(!mpLocalMapper->isFinished())
            cout << "mpLocalMapper is not finished" << endl;
        if(!mpLoopCloser->isFinished())
            cout << "Shutdown:: mpLoopCloser is not finished" << endl;
        if(mpLoopCloser->isRunningGBA()){
            cout << "mpLoopCloser is running GBA" << endl;
            cout << "break anyway..." << endl;
            break;
        }
        usleep(5000);
    }
    
    if(mpViewer)
        pangolin::BindToContext("ORB-SLAM2: Map Viewer");

////finish














    struct timeval smallstart0, smallend0;
    struct timeval start0, end0, presaveStart0, presaveEnd0;
    gettimeofday(&smallstart0, NULL);
    ofstream file_out;
    file_out.open("timeseris.txt", std::ios_base::app);
    file_out << "Before Loading atlas: start0: " << smallstart0.tv_sec * 1000000 + smallstart0.tv_usec<< endl;
    mpAtlas_small = new Atlas(0);
   // Atlas* mpAtlas_temp = new Atlas(1000);
    //mpAtlas_temp = mpAtlas;
    int allKeyframeSize = mpAtlas->GetAllKeyFrames().size();
    if (allKeyframeSize <= 6)
        {
            SaveAtlas_Yunshu("temp");
        }
    else{
            string resultSava_path = "/home/ucrnet/Desktop/workspace/ORBSLAM3/Yunshu_programs/Shellscommends/testKeyFramesize/";
            string keyframesizeFile = "KFsize.txt";
            ofstream myfile;
            myfile.open(resultSava_path + keyframesizeFile, std::ios_base::app);
            myfile << "keyframe number: " << mpAtlas->GetAllKeyFrames().size() << "\n";

            
            // cout << endl << "small--------Enter the name of the file if you want to save the current Atlas session. To exit press ENTER: ";

             
             gettimeofday(&start0, NULL);
            // string saveFileName;
            // getline(cin,saveFileName);
            string saveFileName;
            saveFileName = "smallMapMultiple6KF" + std::to_string((num));
            if(!saveFileName.empty())
            {
                //clock_t start = clock();

                // Save the current session
                gettimeofday(&presaveStart0, NULL);
                
                gettimeofday(&presaveEnd0, NULL);
                double elapsed = ((presaveEnd0.tv_sec - presaveStart0.tv_sec) * 1000) + (presaveEnd0.tv_sec / 1000 - presaveStart0.tv_sec / 1000);

                cout << "*****************save BINARY_FILE  presave time:  " << elapsed << " ******************* " << endl;

                string pathSaveFileName = "./";
                pathSaveFileName = pathSaveFileName.append(saveFileName);
                pathSaveFileName = pathSaveFileName.append(".osa");

                //string strVocabularyChecksum = CalculateCheckSum(mStrVocabularyFilePath,TEXT_FILE);
                //std::size_t found = mStrVocabularyFilePath.find_last_of("/\\");
                //string strVocabularyName = mStrVocabularyFilePath.substr(found+1);

                
                
                
                   
                    //oa << strVocabularyName;
                    //oa << strVocabularyChecksum;




                    //mpAtlas_small ->CreateNewMap();
                    vector<Map*> vm = mpAtlas->GetAllMaps();
                    cout << "total maps in mpatlas: " << vm.size() <<endl;
                    cout << "total maps in mpAtlas_small(): " << mpAtlas_small->GetAllMaps().size() <<endl;
                    //exit(0);
                    for(int i = 0; i < vm.size(); i++){
                        Map* m = vm[i];
                        mpAtlas->GetCurrentMap()->mpKFlowerID = m->mpKFlowerID;
                        cout << "load_second 01" << endl;
                        int count = 0;
                        int smallMapPoints = 0;
                        int totalMapPoints = 0;
                        int keyframeSize = m->GetAllKeyFrames().size();

                        vector<KeyFrame*> vpKFs = m->GetAllKeyFrames();
                        sort(vpKFs.begin(),vpKFs.end(),KeyFrame::lId);
                        vector<KeyFrame*> lastNumKF = {};

                        for(auto k : vpKFs){
                            lastNumKF.push_back(k);
                            Map* KFMap = k->GetMap();
                            //Yunshu commands: this following line controls how many keyframes to be inserted into the small map
                            if (count > keyframeSize - num - 1){
                            //if (count >= currentTotalKF){
                                cout << "before UpdateMap: k->GetMapPoints().size()" << k->GetMapPoints().size() << endl;
                                k->UpdateMap(mpAtlas_small->GetCurrentMap());
                                cout << "count " << count << endl;
                                cout << "after UpdateMap: k->GetMapPoints().size()" << k->GetMapPoints().size() << endl;

                               // KeyFrame* pNewKF = new KeyFrame(); 
                               // pNewKF->UpdateMap(mpAtlas_small->GetCurrentMap());
                               // pNewKF->SetKeyFrameDatabase(k->GetKeyFrameDatabase());
                               // mpAtlas_small->AddKeyFrame(pNewKF, true);
                                mpAtlas_small->AddKeyFrame(k, true);//skip a buggy line in Map::AddKeyFrame
                                //set<MapPoint*> spMPs = k->GetMapPoints();
                                smallMapPoints += k->GetMapPoints().size();
                                
                                cout << "mpAtlas_small->GetCurrentMap()" << mpAtlas_small->GetCurrentMap() << endl;
                                
                                // for(auto mp : k->GetMapPoints()){
                                //     //MapPoint* pNewMP = new MapPoint(mp->GetWorldPos(),k,mpAtlas_small->GetCurrentMap());
                                //     //mpAtlas_small->AddMapPoint(pNewMP);
                                // }

                                k->UpdateMap(KFMap);
                            }

                            

                            totalMapPoints += k->GetMapPoints().size();
                            count++;
                        }

                        for (auto mp : m->GetAllMapPoints())  {
                            int time = std::count(lastNumKF.begin(), lastNumKF.end(), mp->GetReferenceKeyFrame());
                            cout << "time: " << time <<endl;
                            if (time) {
                                    Map* mpMap = mp->GetMap();
                                    mp->UpdateMap(mpAtlas_small->GetCurrentMap());
                                    mpAtlas_small->AddMapPoint(mp);
                                    mp->UpdateMap(mpMap);
                                    cout << "mp->GetReferenceKeyFrame()" << mp->GetReferenceKeyFrame() << endl;
                                    //int times = std::count(mp->GetReferenceKeyFrame()->GetMapPoints().begin(), mp->GetReferenceKeyFrame()->GetMapPoints().end(), mp);
                                    //cout << "if mp->GetReferenceKeyFrame()" << times << endl;
                                    
                                    //MapPoint* pNewMP = new MapPoint(mp->GetWorldPos(),mp->GetReferenceKeyFrame(),mpAtlas_small->GetCurrentMap());
                                    //mpAtlas_small->AddMapPoint(pNewMP);
                            }
                        }

                      //  mpAtlas_small->SetKeyFrameDababase(mpKeyFrameDatabase);
                      //  mpAtlas_small->SetORBVocabulary(mpVocabulary);

                       // mpAtlas_small->SetReferenceMapPoints(m->GetReferenceMapPoints());

                        count = 0;
                        cout << "smallMapPoints " << smallMapPoints << endl;                        
                        cout << "totalMapPoints " << totalMapPoints << endl;
                        cout << "keyframeSize " << keyframeSize << endl;
                        cout << "totalMapPoints - smallMapPoints" << totalMapPoints - smallMapPoints<< endl;
                        cout << "m->GetAllMapPoints() " << m->GetAllMapPoints().size() << endl;
                        cout << "mpAtlas_small->GetCurrentMap().size()" << mpAtlas_small->GetAllMapPoints().size() << endl;

                        cout << "count " << count << endl;
                        //exit(0);
                        

                        cout << "mpAtlas_small->GetAllKeyFrames " << mpAtlas_small->GetAllKeyFrames().size() << endl;
                        cout << "mpAtlas_small->GetAllMapPoints() " << mpAtlas_small->GetAllMapPoints().size() << endl;
                        cout << "load_second 03" << endl;
                        cout << "load_second 04" << endl;
                        }
                        //exit(0);

           //usleep(10000);
                cout << "mpAtlas_small->GetAllKeyFrames end: " << mpAtlas_small->GetAllKeyFrames().size() << endl;
                cout << "mpAtlas_small->GetAllMapPoints() " << mpAtlas_small->GetAllMapPoints().size() << endl;
                cout << "mpAtlas->GetAllMapPoints() " << mpAtlas->GetAllMapPoints().size() << endl;
            //exit(0);
            





                                    //save keyframes
                                        vector<Map*> vpMaps = mpAtlas_small->GetAllMaps();
                                        Map* pBiggerMap;
                                        int numMaxKFs = 0;
                                        for(Map* pMap :vpMaps)
                                        {
                                            if(pMap->GetAllKeyFrames().size() > numMaxKFs)
                                            {
                                                numMaxKFs = pMap->GetAllKeyFrames().size();
                                                pBiggerMap = pMap;
                                            }
                                        }

                                        vector<KeyFrame*> vpKFs = pBiggerMap->GetAllKeyFrames();
                                        sort(vpKFs.begin(),vpKFs.end(),KeyFrame::lId);

                                        // Transform all keyframes so that the first keyframe is at the origin.
                                        // After a loop closure the first keyframe might not be at the origin.
                                        ofstream f;
                                        f.open("kf_smallmap " + to_string(num) + ".txt");
                                        f << fixed;

                                        for(size_t i=0; i<vpKFs.size(); i++)
                                        {
                                            KeyFrame* pKF = vpKFs[i];

                                        // pKF->SetPose(pKF->GetPose()*Two);

                                            if(pKF->isBad())
                                                continue;
                                            if (mSensor == IMU_MONOCULAR || mSensor == IMU_STEREO)
                                            {
                                                cv::Mat R = pKF->GetImuRotation().t();
                                                vector<float> q = Converter::toQuaternion(R);
                                                cv::Mat twb = pKF->GetImuPosition();
                                                f << setprecision(6) << 1e9*pKF->mTimeStamp  << " " <<  setprecision(9) << twb.at<float>(0) << " " << twb.at<float>(1) << " " << twb.at<float>(2) << " " << q[0] << " " << q[1] << " " << q[2] << " " << q[3] << endl;

                                            }
                                            else
                                            {
                                                cv::Mat R = pKF->GetRotation();
                                                vector<float> q = Converter::toQuaternion(R);
                                                cv::Mat t = pKF->GetCameraCenter();
                                                f << setprecision(6) << 1e9*pKF->mTimeStamp << " " <<  setprecision(9) << t.at<float>(0) << " " << t.at<float>(1) << " " << t.at<float>(2) << " " << q[0] << " " << q[1] << " " << q[2] << " " << q[3] << endl;
                                            }
                                        }
                                        f.close();











    gettimeofday(&start0, NULL);
    file_out << "Before saving atlas_small: PreSave(): " << presaveStart0.tv_sec  * 1000000 + presaveStart0.tv_usec << endl;
        
                std::cout << "Atlas::PreSave() start" << std::endl;
                mpAtlas_small->PreSave();
                std::cout << "mpKeyFrameDatabase PreSave() start" << std::endl;
                mpKeyFrameDatabase->PreSave();
    gettimeofday(&end0, NULL);          
    elapsed = (end0.tv_sec * 1000000 + end0.tv_usec)  - (start0.tv_sec * 1000000 + start0.tv_usec );
    file_out << "After saving atlas_small: PreSave(): total time: " << elapsed << endl;
    gettimeofday(&start0, NULL);
    file_out << "Before saving atlas_small: serialization time: " << start0.tv_sec  * 1000000 + start0.tv_usec << endl;

 cout << "Starting to write the save binary file" << endl;
                    std::remove(pathSaveFileName.c_str());
                cout << "OK1" << endl;
                    std::ofstream ofs(pathSaveFileName, std::ios::binary);
                cout << "OK2" <<pathSaveFileName <<endl;
                    boost::archive::binary_oarchive oa(ofs);
                cout << "OK3" << endl;
                int test = 5;
                oa << test;
                cout << "OK3.5" << endl;

                oa << mpAtlas_small;
                    //oa << mpAtlas_small;
                cout << "OK4" << endl;
                //Yunshucommented
                // oa << mpKeyFrameDatabase;
                cout << "OK5" << endl;
                    cout << "End to write save binary file" << endl;
    gettimeofday(&end0, NULL);
    elapsed = (end0.tv_sec * 1000000 + end0.tv_usec)  - (start0.tv_sec * 1000000 + start0.tv_usec );
    file_out << "after saving atlas_small: serialization time: " << elapsed << endl;

                currentTotalKF = mpAtlas->GetAllKeyFrames().size();
                cout << "currentTotalKF" << currentTotalKF<< endl;
                //mpAtlas->clearAtlas();






















                mpAtlas_small->clearAtlas();

                //mpAtlas_small->PostLoad();
                
            }

    }
    gettimeofday(&smallend0, NULL);
    file_out << "after small save atlas: smallend0: " << smallend0.tv_sec * 1000000 + smallend0.tv_usec<< endl;
    double elapsed = (smallend0.tv_sec * 1000000 + smallend0.tv_usec)  - (smallstart0.tv_sec * 1000000 + smallstart0.tv_usec );
    file_out << "small total time "<< elapsed << endl;






    
}




void System::addSmallMapKF(int num){
    vector<Map*> vm = mpAtlas->GetAllMaps();
        
    for(int i = 0; i < vm.size(); i++){
        Map* m = vm[i];
        vector<KeyFrame*> vpKFs = m->GetAllKeyFrames();
        sort(vpKFs.begin(),vpKFs.end(),KeyFrame::lId);
        int keyframeSize = m->GetAllKeyFrames().size();
        int count = 0;
        for(auto k : vpKFs){
            
            if (count > keyframeSize - num - 1){
                smallMapKF.push_back(k);
                cout << "smallMapKF.push_back(k)" << count <<endl;
                //cout << "0. smallMapKF size is: " << smallMapKF.size() << endl;

            }
            count ++;
        
        }
        
    }
    cout << "0. smallMapKF size is: " << smallMapKF.size() << endl;
    //exit(0);
}


void System::deleteAtlas(){
//add mappoints to smallmap

    vector<Map*> vm = mpAtlas->GetAllMaps();
    for(int i = 0; i < vm.size(); i++){
        Map* m = vm[i];
        for (auto mp : m->GetAllMapPoints())  {
                int time = std::count(smallMapKF.begin(), smallMapKF.end(), mp->GetReferenceKeyFrame());
                cout << "time: " << time <<endl;
                if (time) {
                    smallMapMP.push_back(mp);
                }
        }
    }
                        

    if(currentAddKF == 0){
        vector<Map*> vm = mpAtlas->GetAllMaps();
                        for(int i = 0; i < vm.size(); i++){
                            Map* m = vm[i];
                            mpAtlas->GetCurrentMap()->mpKFlowerID = m->mpKFlowerID;
                        

                            vector<KeyFrame*> vpKFs = m->GetAllKeyFrames();
                            
    
                            for(auto k : vpKFs){    
                                // int time = std::count(smallMapKF.begin(), smallMapKF.end(), k);
                                // cout << "time: " << time <<endl;
                                // if (time == 0) {
                                //     for (auto mp: k->GetMapPoints()){
                                //         ;
                                //         k->EraseMapPointMatch(mp);
                                //         mp->EraseObservation(k);
                                //     } 
                                // }                       
                                    m->EraseKeyFrame(k);
                            }
                        
                            for (auto mp : m->GetAllMapPoints())  {
                                    m->EraseMapPoint(mp);
                                }
                        }
                        
    }
//mpAtlas->clearAtlas();
    cout << "cleared all maps" << endl;
    cout << "mpAtlas->GetAllMapPoints().size() " << mpAtlas->GetAllMapPoints().size() << endl;
    cout << "mpAtlas->GetAllKeyFrames().size() " << mpAtlas->GetAllKeyFrames().size()<< endl;
}


void System::addSmallAtlas(int num){
//mpAtlas->clearAtlas();
                    num = smallMapKF.size()/13 - 1;

                    cout << "addSmallAtlas " << endl;


    
                    vector<Map*> vm = mpAtlas->GetAllMaps();
                    cout << "total maps in mpatlas: " << vm.size() <<endl;

                    for(int i = 0; i < vm.size(); i++){
                        Map* m = vm[i];
                        mpAtlas->GetCurrentMap()->mpKFlowerID = m->mpKFlowerID;

                        sort(smallMapKF.begin(),smallMapKF.end(),KeyFrame::lId);

                        cout << "smallMapKF.size() " <<  smallMapKF.size() <<endl;


                        int addKFCounter = 0;
                        for(auto k : smallMapKF){
                            if (currentAddKF >= smallMapKF.size() || addKFCounter - currentAddKF> num){
                                currentAddKF = addKFCounter;
                                break;
                            }
                            addKFCounter ++;
                            if (addKFCounter < currentAddKF){
                                continue;
                            }
                            
                            cout << "here" << endl;

                           // Map* KFMap = k->GetMap();  
                           // k->UpdateMap(mpAtlas->GetCurrentMap());                           
                            mpAtlas->GetCurrentMap()->AddKeyFrame(k, true);
                            
                            for (auto mp : k->GetMapPoints())  {
                                cout << "one mp" << endl;
                                //mp->UpdateMap(mpAtlas->GetCurrentMap());
                                mpAtlas->GetCurrentMap()->AddMapPoint(mp);
                            }

                          
                            //mpLoopCloser->InsertKeyFrame(k);
                            //mpLocalMapper->InsertKeyFrame(k);
                                    

                            cout << "add keyframe to atlas " <<endl;
                        }
                    }
                    cout << "add to atlas done " << vm.size() <<endl;

}





void System::getSmallAtlas(int num){
    cout << "smallMapKF size is: " << smallMapKF.size() << endl;

//just for ate experiment:
    mpLocalMapper->RequestFinish();
    mpLoopCloser->RequestFinish();
    if(mpViewer)
    {
        mpViewer->RequestFinish();
        while(!mpViewer->isFinished())
            usleep(5000);
    }
    

    // Wait until all thread have effectively stopped
    while(!mpLocalMapper->isFinished() || !mpLoopCloser->isFinished() || mpLoopCloser->isRunningGBA())
    {
        if(!mpLocalMapper->isFinished())
            cout << "mpLocalMapper is not finished" << endl;
        if(!mpLoopCloser->isFinished())
            cout << "Shutdown:: mpLoopCloser is not finished" << endl;
        if(mpLoopCloser->isRunningGBA()){
            cout << "mpLoopCloser is running GBA" << endl;
            cout << "break anyway..." << endl;
            break;
        }
        usleep(5000);
    }
    
    if(mpViewer)
        pangolin::BindToContext("ORB-SLAM2: Map Viewer");

////finish



    struct timeval smallstart0, smallend0;
    struct timeval start0, end0, presaveStart0, presaveEnd0;
    gettimeofday(&smallstart0, NULL);
    ofstream file_out;
    file_out.open("timeseris.txt", std::ios_base::app);
    file_out << "Before Loading atlas: start0: " << smallstart0.tv_sec * 1000000 + smallstart0.tv_usec<< endl;


    int allKeyframeSize = mpAtlas->GetAllKeyFrames().size();
    if (allKeyframeSize <= 6)
        {
            SaveAtlas_Yunshu("temp");
        }
    else{
            string resultSava_path = "/home/ucrnet/Desktop/workspace/ORBSLAM3/Yunshu_programs/Shellscommends/testKeyFramesize/";
            string keyframesizeFile = "KFsize.txt";
            ofstream myfile;
            myfile.open(resultSava_path + keyframesizeFile, std::ios_base::app);
            myfile << "keyframe number: " << mpAtlas->GetAllKeyFrames().size() << "\n";

             
             gettimeofday(&start0, NULL);

            string saveFileName;
            saveFileName = "smallmap" + to_string(num) ;
            if(!saveFileName.empty())
            {

                gettimeofday(&presaveStart0, NULL);
                
                gettimeofday(&presaveEnd0, NULL);
                double elapsed = ((presaveEnd0.tv_sec - presaveStart0.tv_sec) * 1000) + (presaveEnd0.tv_sec / 1000 - presaveStart0.tv_sec / 1000);

                cout << "*****************save BINARY_FILE  presave time:  " << elapsed << " ******************* " << endl;

                string pathSaveFileName = "./";
                pathSaveFileName = pathSaveFileName.append(saveFileName);
                pathSaveFileName = pathSaveFileName.append(".osa");




                    vector<Map*> vm = mpAtlas->GetAllMaps();
                    cout << "total maps in mpatlas: " << vm.size() <<endl;
                    //exit(0);
                    for(int i = 0; i < vm.size(); i++){
                        Map* m = vm[i];
                        mpAtlas->GetCurrentMap()->mpKFlowerID = m->mpKFlowerID;
                        cout << "load_second 01" << endl;
                        int count = 0;
                        int smallMapPoints = 0;
                        int totalMapPoints = 0;
                        int keyframeSize = m->GetAllKeyFrames().size();

                        vector<KeyFrame*> vpKFs = m->GetAllKeyFrames();
                        sort(vpKFs.begin(),vpKFs.end(),KeyFrame::lId);
                        vector<KeyFrame*> lastNumKF = {};
                        cout << "smallMapKF.size() " <<smallMapKF.size() <<endl; 
                        for(auto k : vpKFs){
                            //lastNumKF.push_back(k);
                            //Yunshu commands: this following line controls how many keyframes to be inserted into the small map
                            if(std::count(smallMapKF.begin(), smallMapKF.end(), k) == 0){
                            //if (count <= keyframeSize - num - 1){
                                
                                m->EraseKeyFrame(k);
                            }
                            else{
                                ;
                            }

                            

                            totalMapPoints += k->GetMapPoints().size();
                            count++;
                        }


                        cout << "smallMapKF.size() " <<smallMapKF.size() <<endl;    
                        for (auto mp : m->GetAllMapPoints())  {
                            int time = 0;
                            for (auto k : smallMapKF){
                                if(mp->IsInKeyFrame(k)){
                                    time = 1;
                                    cout << "kf mp! " <<endl;
                                    break;
                                }
                            }
                            int time2 = std::count(lastNumKF.begin(), lastNumKF.end(), mp->GetReferenceKeyFrame());
                            
                            //int time = 1;
                            cout << "time: " << time <<";   time2: " << time2 <<endl;
                            if (time == 0) {
                                   m->EraseMapPoint(mp);
                            }
                        }
                    }        


                                        vector<Map*> vpMaps = mpAtlas->GetAllMaps();
                                        Map* pBiggerMap;
                                        int numMaxKFs = 0;
                                        for(Map* pMap :vpMaps)
                                        {
                                            if(pMap->GetAllKeyFrames().size() > numMaxKFs)
                                            {
                                                numMaxKFs = pMap->GetAllKeyFrames().size();
                                                pBiggerMap = pMap;
                                            }
                                        }


                                        // Transform all keyframes so that the first keyframe is at the origin.
                                        // After a loop closure the first keyframe might not be at the origin.
                                        ofstream f;
                                        f.open("kf_smallmap"  + to_string(num) +".txt");
                                        f << fixed;

                                        vector<KeyFrame*> vpKFs = pBiggerMap->GetAllKeyFrames();
                                        sort(vpKFs.begin(),vpKFs.end(),KeyFrame::lId);
                                        for(size_t i=0; i<vpKFs.size(); i++)
                                        {
                                            KeyFrame* pKF = vpKFs[i];

                                        // pKF->SetPose(pKF->GetPose()*Two);

                                            if(pKF->isBad())
                                                continue;
                                            if (mSensor == IMU_MONOCULAR || mSensor == IMU_STEREO)
                                            {
                                                cv::Mat R = pKF->GetImuRotation().t();
                                                vector<float> q = Converter::toQuaternion(R);
                                                cv::Mat twb = pKF->GetImuPosition();
                                                f << setprecision(6) << 1e9*pKF->mTimeStamp  << " " <<  setprecision(9) << twb.at<float>(0) << " " << twb.at<float>(1) << " " << twb.at<float>(2) << " " << q[0] << " " << q[1] << " " << q[2] << " " << q[3] << endl;

                                            }
                                            else
                                            {
                                                cv::Mat R = pKF->GetRotation();
                                                vector<float> q = Converter::toQuaternion(R);
                                                cv::Mat t = pKF->GetCameraCenter();
                                                f << setprecision(6) << 1e9*pKF->mTimeStamp << " " <<  setprecision(9) << t.at<float>(0) << " " << t.at<float>(1) << " " << t.at<float>(2) << " " << q[0] << " " << q[1] << " " << q[2] << " " << q[3] << endl;
                                            }
                                        }
                                        f.close();











    gettimeofday(&start0, NULL);
    file_out << "Before saving atlas_small: PreSave(): " << presaveStart0.tv_sec  * 1000000 + presaveStart0.tv_usec << endl;
        
                std::cout << "Atlas::PreSave() start" << std::endl;
                mpAtlas->PreSave();
                std::cout << "mpKeyFrameDatabase PreSave() start" << std::endl;
                mpKeyFrameDatabase->PreSave();
    gettimeofday(&end0, NULL);          
    elapsed = (end0.tv_sec * 1000000 + end0.tv_usec)  - (start0.tv_sec * 1000000 + start0.tv_usec );
    file_out << "After saving atlas_small: PreSave(): total time: " << elapsed << endl;
    gettimeofday(&start0, NULL);
    file_out << "Before saving atlas_small: serialization time: " << start0.tv_sec  * 1000000 + start0.tv_usec << endl;

 cout << "Starting to write the save binary file" << endl;
                    std::remove(pathSaveFileName.c_str());
                cout << "OK1" << endl;
                    std::ofstream ofs(pathSaveFileName, std::ios::binary);
                cout << "OK2" <<pathSaveFileName <<endl;
                    boost::archive::binary_oarchive oa(ofs);
                cout << "OK3" << endl;
                int test = 5;
                oa << test;
                cout << "OK3.5" << endl;

                oa << mpAtlas;

                cout << "OK5" << endl;
                    cout << "End to write save binary file" << endl;
    gettimeofday(&end0, NULL);
    elapsed = (end0.tv_sec * 1000000 + end0.tv_usec)  - (start0.tv_sec * 1000000 + start0.tv_usec );
    file_out << "after saving atlas_small: serialization time: " << elapsed << endl;

                currentTotalKF = mpAtlas->GetAllKeyFrames().size();
                cout << "currentTotalKF" << currentTotalKF<< endl;
 
                mpAtlas->clearAtlas();

                
            }

    }
    gettimeofday(&smallend0, NULL);
    file_out << "after small save atlas: smallend0: " << smallend0.tv_sec * 1000000 + smallend0.tv_usec<< endl;
    double elapsed = (smallend0.tv_sec * 1000000 + smallend0.tv_usec)  - (smallstart0.tv_sec * 1000000 + smallstart0.tv_usec );
    file_out << "small total time "<< elapsed << endl;

    cout << "smallMapKF size is: " << smallMapKF.size() << endl;


    
}




void System::deleteSmallAtlas(int num){

    struct timeval smallstart0, smallend0;
    struct timeval start0, end0, presaveStart0, presaveEnd0;
    gettimeofday(&smallstart0, NULL);
    ofstream file_out;
    file_out.open("timeseris.txt", std::ios_base::app);
    file_out << "Before Loading atlas: start0: " << smallstart0.tv_sec * 1000000 + smallstart0.tv_usec<< endl;


    int allKeyframeSize = mpAtlas->GetAllKeyFrames().size();
    if (allKeyframeSize <= 6)
        {
            SaveAtlas_Yunshu("temp");
        }
    else{
            string resultSava_path = "/home/ucrnet/Desktop/workspace/ORBSLAM3/Yunshu_programs/Shellscommends/testKeyFramesize/";
            string keyframesizeFile = "KFsize.txt";
            ofstream myfile;
            myfile.open(resultSava_path + keyframesizeFile, std::ios_base::app);
            myfile << "keyframe number: " << mpAtlas->GetAllKeyFrames().size() << "\n";

             
             gettimeofday(&start0, NULL);

            string saveFileName;
            saveFileName = "smallmap" + to_string(num) ;
            if(!saveFileName.empty())
            {

                gettimeofday(&presaveStart0, NULL);
                
                gettimeofday(&presaveEnd0, NULL);
                double elapsed = ((presaveEnd0.tv_sec - presaveStart0.tv_sec) * 1000) + (presaveEnd0.tv_sec / 1000 - presaveStart0.tv_sec / 1000);

                cout << "*****************save BINARY_FILE  presave time:  " << elapsed << " ******************* " << endl;

                string pathSaveFileName = "./";
                pathSaveFileName = pathSaveFileName.append(saveFileName);
                pathSaveFileName = pathSaveFileName.append(".osa");




                    vector<Map*> vm = mpAtlas->GetAllMaps();
                    cout << "total maps in mpatlas: " << vm.size() <<endl;
                    //exit(0);
                    for(int i = 0; i < vm.size(); i++){
                        Map* m = vm[i];
                        mpAtlas->GetCurrentMap()->mpKFlowerID = m->mpKFlowerID;
                        cout << "load_second 01" << endl;
                        int count = 0;
                        int smallMapPoints = 0;
                        int totalMapPoints = 0;
                        int keyframeSize = m->GetAllKeyFrames().size();

                        vector<KeyFrame*> vpKFs = m->GetAllKeyFrames();
                       // sort(vpKFs.begin(),vpKFs.end(),KeyFrame::lId);
                        vector<KeyFrame*> lastNumKF = {};
                        cout << "smallMapKF.size() " <<smallMapKF.size() <<endl; 
                        for(auto k : vpKFs){
                            //lastNumKF.push_back(k);
                            //Yunshu commands: this following line controls how many keyframes to be inserted into the small map
                            if(std::count(smallMapKF.begin(), smallMapKF.end(), k) == 0){
                            //if (count <= keyframeSize - num - 1){
                                
                                m->EraseKeyFrame(k);
                            }
                            else{
                                ;
                            }

                            

                            totalMapPoints += k->GetMapPoints().size();
                            count++;
                        }


                        cout << "smallMapKF.size() " <<smallMapKF.size() <<endl;    
                        for (auto mp : m->GetAllMapPoints())  {
                            int time = 0;
                            for (auto k : smallMapKF){
                                if(mp->IsInKeyFrame(k)){
                                    time = 1;
                                    cout << "kf mp! " <<endl;
                                    break;
                                }
                            }
                            int time2 = std::count(lastNumKF.begin(), lastNumKF.end(), mp->GetReferenceKeyFrame());
                            
                            //int time = 1;
                            cout << "time: " << time <<";   time2: " << time2 <<endl;
                            if (time == 0) {
                                   m->EraseMapPoint(mp);
                            }
                        }
                    }        


                                        vector<Map*> vpMaps = mpAtlas->GetAllMaps();
                                        Map* pBiggerMap;
                                        int numMaxKFs = 0;
                                        for(Map* pMap :vpMaps)
                                        {
                                            if(pMap->GetAllKeyFrames().size() > numMaxKFs)
                                            {
                                                numMaxKFs = pMap->GetAllKeyFrames().size();
                                                pBiggerMap = pMap;
                                            }
                                        }


                                        // Transform all keyframes so that the first keyframe is at the origin.
                                        // After a loop closure the first keyframe might not be at the origin.
                                        ofstream f;
                                        f.open("kf_smallmap"  + to_string(num) +".txt");
                                        f << fixed;

                                        vector<KeyFrame*> vpKFs = pBiggerMap->GetAllKeyFrames();
                                        sort(vpKFs.begin(),vpKFs.end(),KeyFrame::lId);
                                        for(size_t i=0; i<vpKFs.size(); i++)
                                        {
                                            KeyFrame* pKF = vpKFs[i];

                                        // pKF->SetPose(pKF->GetPose()*Two);

                                            if(pKF->isBad())
                                                continue;
                                            if (mSensor == IMU_MONOCULAR || mSensor == IMU_STEREO)
                                            {
                                                cv::Mat R = pKF->GetImuRotation().t();
                                                vector<float> q = Converter::toQuaternion(R);
                                                cv::Mat twb = pKF->GetImuPosition();
                                                f << setprecision(6) << 1e9*pKF->mTimeStamp  << " " <<  setprecision(9) << twb.at<float>(0) << " " << twb.at<float>(1) << " " << twb.at<float>(2) << " " << q[0] << " " << q[1] << " " << q[2] << " " << q[3] << endl;

                                            }
                                            else
                                            {
                                                cv::Mat R = pKF->GetRotation();
                                                vector<float> q = Converter::toQuaternion(R);
                                                cv::Mat t = pKF->GetCameraCenter();
                                                f << setprecision(6) << 1e9*pKF->mTimeStamp << " " <<  setprecision(9) << t.at<float>(0) << " " << t.at<float>(1) << " " << t.at<float>(2) << " " << q[0] << " " << q[1] << " " << q[2] << " " << q[3] << endl;
                                            }
                                        }
                                        f.close();
            }
    }


    
}



cv::Mat System::TrackStereo(const cv::Mat &imLeft, const cv::Mat &imRight, const double &timestamp, const vector<IMU::Point>& vImuMeas, string filename)
{
    if(mSensor!=STEREO && mSensor!=IMU_STEREO)
    {
        cerr << "ERROR: you called TrackStereo but input sensor was not set to Stereo nor Stereo-Inertial." << endl;
        exit(-1);
    }

    // Check mode change
    {
        unique_lock<mutex> lock(mMutexMode);
        if(mbActivateLocalizationMode)
        {
            mpLocalMapper->RequestStop();

            // Wait until Local Mapping has effectively stopped
            while(!mpLocalMapper->isStopped())
            {
                usleep(1000);
            }

            mpTracker->InformOnlyTracking(true);
            mbActivateLocalizationMode = false;
        }
        if(mbDeactivateLocalizationMode)
        {
            mpTracker->InformOnlyTracking(false);
            mpLocalMapper->Release();
            mbDeactivateLocalizationMode = false;
        }
    }

    // Check reset
    {
        unique_lock<mutex> lock(mMutexReset);
        if(mbReset)
        {
            mpTracker->Reset();
            cout << "Reset stereo..." << endl;
            mbReset = false;
            mbResetActiveMap = false;
        }
        else if(mbResetActiveMap)
        {
            mpTracker->ResetActiveMap();
            mbResetActiveMap = false;
        }
    }

    if (mSensor == System::IMU_STEREO)
        for(size_t i_imu = 0; i_imu < vImuMeas.size(); i_imu++)
            mpTracker->GrabImuData(vImuMeas[i_imu]);

    // std::cout << "start GrabImageStereo" << std::endl;
    cv::Mat Tcw = mpTracker->GrabImageStereo(imLeft,imRight,timestamp,filename);

    // std::cout << "out grabber" << std::endl;

    unique_lock<mutex> lock2(mMutexState);
    mTrackingState = mpTracker->mState;
    mTrackedMapPoints = mpTracker->mCurrentFrame.mvpMapPoints;
    mTrackedKeyPointsUn = mpTracker->mCurrentFrame.mvKeysUn;

    return Tcw;
}

cv::Mat System::TrackRGBD(const cv::Mat &im, const cv::Mat &depthmap, const double &timestamp, string filename)
{
    if(mSensor!=RGBD)
    {
        cerr << "ERROR: you called TrackRGBD but input sensor was not set to RGBD." << endl;
        exit(-1);
    }

    // Check mode change
    {
        unique_lock<mutex> lock(mMutexMode);
        if(mbActivateLocalizationMode)
        {
            mpLocalMapper->RequestStop();

            // Wait until Local Mapping has effectively stopped
            while(!mpLocalMapper->isStopped())
            {
                usleep(1000);
            }

            mpTracker->InformOnlyTracking(true);
            mbActivateLocalizationMode = false;
        }
        if(mbDeactivateLocalizationMode)
        {
            mpTracker->InformOnlyTracking(false);
            mpLocalMapper->Release();
            mbDeactivateLocalizationMode = false;
        }
    }

    // Check reset
    {
        unique_lock<mutex> lock(mMutexReset);
        if(mbReset)
        {
            mpTracker->Reset();
            mbReset = false;
            mbResetActiveMap = false;
        }
        else if(mbResetActiveMap)
        {
            mpTracker->ResetActiveMap();
            mbResetActiveMap = false;
        }
    }


    cv::Mat Tcw = mpTracker->GrabImageRGBD(im,depthmap,timestamp,filename);

    unique_lock<mutex> lock2(mMutexState);
    mTrackingState = mpTracker->mState;
    mTrackedMapPoints = mpTracker->mCurrentFrame.mvpMapPoints;
    mTrackedKeyPointsUn = mpTracker->mCurrentFrame.mvKeysUn;
    return Tcw;
}

cv::Mat System::TrackMonocular(const cv::Mat &im, const double &timestamp, const vector<IMU::Point>& vImuMeas, string filename)
{

    //if (mpAtlas->GetAllKeyFrames().size() >49){
   //     std::cout << "mpAtlas->GetAllKeyFrames().size()"  <<mpAtlas->GetAllKeyFrames().size()<< std::endl;
  //  Shutdown();

  // }
    //cout << "in System::TrackMonocular 00" << endl;
    if(mSensor!=MONOCULAR && mSensor!=IMU_MONOCULAR)
    {
        cerr << "ERROR: you called TrackMonocular but input sensor was not set to Monocular nor Monocular-Inertial." << endl;
        exit(-1);
    }
    // Check mode change
    {
        unique_lock<mutex> lock(mMutexMode);
        if(mbActivateLocalizationMode)
        {
            mpLocalMapper->RequestStop();

            // Wait until Local Mapping has effectively stopped
            while(!mpLocalMapper->isStopped())
            {
                usleep(1000);
            }

            mpTracker->InformOnlyTracking(true);
            mbActivateLocalizationMode = false;
        }
        if(mbDeactivateLocalizationMode)
        {
            mpTracker->InformOnlyTracking(false);
            mpLocalMapper->Release();
            mbDeactivateLocalizationMode = false;
        }
    }

    cout << "Here3:   ******************* " << endl;

    //cout << "in System::TrackMonocular 01" << endl;
    // Check reset
    {
        unique_lock<mutex> lock(mMutexReset);
        if(mbReset)
        {
            mpTracker->Reset();
            mbReset = false;
            mbResetActiveMap = false;
        }
        else if(mbResetActiveMap)
        {
            cout << "SYSTEM-> Reseting active map in monocular case" << endl;
            mpTracker->ResetActiveMap();
            mbResetActiveMap = false;
        }
    }
    cout << "Here4: ******************* " << endl;

    //cout << "in System::TrackMonocular 02" << endl;
    if (mSensor == System::IMU_MONOCULAR)
        for(size_t i_imu = 0; i_imu < vImuMeas.size(); i_imu++)
            mpTracker->GrabImuData(vImuMeas[i_imu]);
    cout << "Here2:  "  << " ******************* filename is: " << filename<< endl;

    cv::Mat Tcw = mpTracker->GrabImageMonocular(im,timestamp,filename);

    unique_lock<mutex> lock2(mMutexState);
    mTrackingState = mpTracker->mState;
    mTrackedMapPoints = mpTracker->mCurrentFrame.mvpMapPoints;
    mTrackedKeyPointsUn = mpTracker->mCurrentFrame.mvKeysUn;

    cout << "in System::TrackMonocular end" << endl;
    return Tcw;
}



void System::ActivateLocalizationMode()
{
    unique_lock<mutex> lock(mMutexMode);
    mbActivateLocalizationMode = true;
}

void System::DeactivateLocalizationMode()
{
    unique_lock<mutex> lock(mMutexMode);
    mbDeactivateLocalizationMode = true;
}

bool System::MapChanged()
{
    static int n=0;
    int curn = mpAtlas->GetLastBigChangeIdx();
    if(n<curn)
    {
        n=curn;
        return true;
    }
    else
        return false;
}

void System::Reset()
{
    unique_lock<mutex> lock(mMutexReset);
    mbReset = true;
}

void System::ResetActiveMap()
{
    unique_lock<mutex> lock(mMutexReset);
    mbResetActiveMap = true;
}

void System::Shutdown()
{
    mpLocalMapper->RequestFinish();
    mpLoopCloser->RequestFinish();
    if(mpViewer)
    {
        mpViewer->RequestFinish();
        while(!mpViewer->isFinished())
            usleep(5000);
    }

    // Wait until all thread have effectively stopped
    while(!mpLocalMapper->isFinished() || !mpLoopCloser->isFinished() || mpLoopCloser->isRunningGBA())
    {
        if(!mpLocalMapper->isFinished())
            cout << "mpLocalMapper is not finished" << endl;
        if(!mpLoopCloser->isFinished())
            cout << "Shutdown:: mpLoopCloser is not finished" << endl;
        if(mpLoopCloser->isRunningGBA()){
            cout << "mpLoopCloser is running GBA" << endl;
            cout << "break anyway..." << endl;
            break;
        }
        usleep(5000);
    }
    struct timeval start0, end0;
    if(mpViewer)
        pangolin::BindToContext("ORB-SLAM2: Map Viewer");


//mpTracker->LocalMapStats2File();
    SaveAtlas(BINARY_FILE);
    //SaveAtlas_Yunshu("shutdhown");

}



void System::SaveTrajectoryTUM(const string &filename)
{
    cout << endl << "Saving camera trajectory to " << filename << " ..." << endl;
    if(mSensor==MONOCULAR)
    {
        cerr << "ERROR: SaveTrajectoryTUM cannot be used for monocular." << endl;
        return;
    }

    vector<KeyFrame*> vpKFs = mpAtlas->GetAllKeyFrames();
    sort(vpKFs.begin(),vpKFs.end(),KeyFrame::lId);

    // Transform all keyframes so that the first keyframe is at the origin.
    // After a loop closure the first keyframe might not be at the origin.
    cv::Mat Two = vpKFs[0]->GetPoseInverse();

    ofstream f;
    f.open(filename.c_str());
    f << fixed;

    // Frame pose is stored relative to its reference keyframe (which is optimized by BA and pose graph).
    // We need to get first the keyframe pose and then concatenate the relative transformation.
    // Frames not localized (tracking failure) are not saved.

    // For each frame we have a reference keyframe (lRit), the timestamp (lT) and a flag
    // which is true when tracking failed (lbL).
    list<ORB_SLAM3::KeyFrame*>::iterator lRit = mpTracker->mlpReferences.begin();
    list<double>::iterator lT = mpTracker->mlFrameTimes.begin();
    list<bool>::iterator lbL = mpTracker->mlbLost.begin();
    for(list<cv::Mat>::iterator lit=mpTracker->mlRelativeFramePoses.begin(),
        lend=mpTracker->mlRelativeFramePoses.end();lit!=lend;lit++, lRit++, lT++, lbL++)
    {
        if(*lbL)
            continue;

        KeyFrame* pKF = *lRit;

        cv::Mat Trw = cv::Mat::eye(4,4,CV_32F);

        // If the reference keyframe was culled, traverse the spanning tree to get a suitable keyframe.
        while(pKF->isBad())
        {
            Trw = Trw*pKF->mTcp;
            pKF = pKF->GetParent();
        }

        Trw = Trw*pKF->GetPose()*Two;

        cv::Mat Tcw = (*lit)*Trw;
        cv::Mat Rwc = Tcw.rowRange(0,3).colRange(0,3).t();
        cv::Mat twc = -Rwc*Tcw.rowRange(0,3).col(3);

        vector<float> q = Converter::toQuaternion(Rwc);

        f << setprecision(6) << *lT << " " <<  setprecision(9) << twc.at<float>(0) << " " << twc.at<float>(1) << " " << twc.at<float>(2) << " " << q[0] << " " << q[1] << " " << q[2] << " " << q[3] << endl;
    }
    f.close();
    // cout << endl << "trajectory saved!" << endl;
}

void System::SaveKeyFrameTrajectoryTUM(const string &filename)
{
    cout << endl << "Saving keyframe trajectory to " << filename << " ..." << endl;

    vector<KeyFrame*> vpKFs = mpAtlas->GetAllKeyFrames();
    sort(vpKFs.begin(),vpKFs.end(),KeyFrame::lId);

    // Transform all keyframes so that the first keyframe is at the origin.
    // After a loop closure the first keyframe might not be at the origin.
    ofstream f;
    f.open(filename.c_str());
    f << fixed;

    for(size_t i=0; i<vpKFs.size(); i++)
    {
        KeyFrame* pKF = vpKFs[i];

       // pKF->SetPose(pKF->GetPose()*Two);

        if(pKF->isBad())
            continue;

        cv::Mat R = pKF->GetRotation().t();
        vector<float> q = Converter::toQuaternion(R);
        cv::Mat t = pKF->GetCameraCenter();
        f << setprecision(6) << pKF->mTimeStamp << setprecision(7) << " " << t.at<float>(0) << " " << t.at<float>(1) << " " << t.at<float>(2)
          << " " << q[0] << " " << q[1] << " " << q[2] << " " << q[3] << endl;

    }

    f.close();
}

void System::SaveTrajectoryEuRoC(const string &filename)
{

    cout << endl << "Saving trajectory to " << filename << " ..." << endl;
    /*if(mSensor==MONOCULAR)
    {
        cerr << "ERROR: SaveTrajectoryEuRoC cannot be used for monocular." << endl;
        return;
    }*/

    vector<Map*> vpMaps = mpAtlas->GetAllMaps();
    Map* pBiggerMap;
    int numMaxKFs = 0;
    for(Map* pMap :vpMaps)
    {
        if(pMap->GetAllKeyFrames().size() > numMaxKFs)
        {
            numMaxKFs = pMap->GetAllKeyFrames().size();
            pBiggerMap = pMap;
        }
    }

cout << endl << "Saving trajectory 0" << endl;
    vector<KeyFrame*> vpKFs = pBiggerMap->GetAllKeyFrames();
    sort(vpKFs.begin(),vpKFs.end(),KeyFrame::lId);

cout << endl << "Saving trajectory 1" << endl;
    // Transform all keyframes so that the first keyframe is at the origin.
    // After a loop closure the first keyframe might not be at the origin.
    cv::Mat Twb; // Can be word to cam0 or world to b dependingo on IMU or not.
    if (mSensor==IMU_MONOCULAR || mSensor==IMU_STEREO)
        Twb = vpKFs[0]->GetImuPose();
    else
        Twb = vpKFs[0]->GetPoseInverse();


cout << endl << "Saving trajectory 2" << endl;
    ofstream f;
    f.open(filename.c_str());
    // cout << "file open" << endl;
    f << fixed;

cout << endl << "Saving trajectory 0.5" << endl;
    // Frame pose is stored relative to its reference keyframe (which is optimized by BA and pose graph).
    // We need to get first the keyframe pose and then concatenate the relative transformation.
    // Frames not localized (tracking failure) are not saved.

    // For each frame we have a reference keyframe (lRit), the timestamp (lT) and a flag
    // which is true when tracking failed (lbL).
    list<ORB_SLAM3::KeyFrame*>::iterator lRit = mpTracker->mlpReferences.begin();
    list<double>::iterator lT = mpTracker->mlFrameTimes.begin();
    list<bool>::iterator lbL = mpTracker->mlbLost.begin();

    //cout << "size mlpReferences: " << mpTracker->mlpReferences.size() << endl;
    //cout << "size mlRelativeFramePoses: " << mpTracker->mlRelativeFramePoses.size() << endl;
    //cout << "size mpTracker->mlFrameTimes: " << mpTracker->mlFrameTimes.size() << endl;
    //cout << "size mpTracker->mlbLost: " << mpTracker->mlbLost.size() << endl;

cout << endl << "Saving trajectory 1" << endl;
    for(list<cv::Mat>::iterator lit=mpTracker->mlRelativeFramePoses.begin(),
        lend=mpTracker->mlRelativeFramePoses.end();lit!=lend;lit++, lRit++, lT++, lbL++)
    {
        //cout << "1" << endl;
        if(*lbL)
            continue;


        KeyFrame* pKF = *lRit;
        //cout << "KF: " << pKF->mnId << endl;

        cv::Mat Trw = cv::Mat::eye(4,4,CV_32F);

        /*cout << "2" << endl;
        cout << "KF id: " << pKF->mnId << endl;*/

        // If the reference keyframe was culled, traverse the spanning tree to get a suitable keyframe.
        if (!pKF)
            continue;

        cout << "2.5" << endl;

        while(pKF->isBad())
        {
            //cout << " 2.bad" << endl;
            Trw = Trw*pKF->mTcp;
            pKF = pKF->GetParent();
            //cout << "--Parent KF: " << pKF->mnId << endl;
        }

        if(!pKF || pKF->GetMap() != pBiggerMap)
        {
            //cout << "--Parent KF is from another map" << endl;
            /*if(pKF)
                cout << "--Parent KF " << pKF->mnId << " is from another map " << pKF->GetMap()->GetId() << endl;*/
            continue;
        }

        cout << "3" << endl;

        Trw = Trw*pKF->GetPose()*Twb; // Tcp*Tpw*Twb0=Tcb0 where b0 is the new world reference

         cout << "4" << endl;

        if (mSensor == IMU_MONOCULAR || mSensor == IMU_STEREO)
        {
            cv::Mat Tbw = pKF->mImuCalib.Tbc*(*lit)*Trw;
            cv::Mat Rwb = Tbw.rowRange(0,3).colRange(0,3).t();
            cv::Mat twb = -Rwb*Tbw.rowRange(0,3).col(3);
            vector<float> q = Converter::toQuaternion(Rwb);
            f << setprecision(6) << 1e9*(*lT) << " " <<  setprecision(9) << twb.at<float>(0) << " " << twb.at<float>(1) << " " << twb.at<float>(2) << " " << q[0] << " " << q[1] << " " << q[2] << " " << q[3] << endl;
        }
        else
        {
            cv::Mat Tcw = (*lit)*Trw;
            cv::Mat Rwc = Tcw.rowRange(0,3).colRange(0,3).t();
            cv::Mat twc = -Rwc*Tcw.rowRange(0,3).col(3);
            vector<float> q = Converter::toQuaternion(Rwc);
            f << setprecision(6) << 1e9*(*lT) << " " <<  setprecision(9) << twc.at<float>(0) << " " << twc.at<float>(1) << " " << twc.at<float>(2) << " " << q[0] << " " << q[1] << " " << q[2] << " " << q[3] << endl;
        }

        // cout << "5" << endl;
    }
    //cout << "end saving trajectory" << endl;
    f.close();
    cout << endl << "End of saving trajectory to " << filename << " ..." << endl;
}


void System::SaveKeyFrameTrajectoryEuRoC(const string &filename)
{
    cout << endl << "Saving keyframe trajectory to " << filename << " ..." << endl;

    vector<Map*> vpMaps = mpAtlas->GetAllMaps();
    Map* pBiggerMap;
    int numMaxKFs = 0;
    for(Map* pMap :vpMaps)
    {
        if(pMap->GetAllKeyFrames().size() > numMaxKFs)
        {
            numMaxKFs = pMap->GetAllKeyFrames().size();
            pBiggerMap = pMap;
        }
    }

    vector<KeyFrame*> vpKFs = pBiggerMap->GetAllKeyFrames();
    sort(vpKFs.begin(),vpKFs.end(),KeyFrame::lId);

    // Transform all keyframes so that the first keyframe is at the origin.
    // After a loop closure the first keyframe might not be at the origin.
    ofstream f;
    f.open(filename.c_str());
    f << fixed;

    for(size_t i=0; i<vpKFs.size(); i++)
    {
        KeyFrame* pKF = vpKFs[i];

       // pKF->SetPose(pKF->GetPose()*Two);

        if(pKF->isBad())
            continue;
        if (mSensor == IMU_MONOCULAR || mSensor == IMU_STEREO)
        {
            cv::Mat R = pKF->GetImuRotation().t();
            vector<float> q = Converter::toQuaternion(R);
            cv::Mat twb = pKF->GetImuPosition();
            f << setprecision(6) << 1e9*pKF->mTimeStamp  << " " <<  setprecision(9) << twb.at<float>(0) << " " << twb.at<float>(1) << " " << twb.at<float>(2) << " " << q[0] << " " << q[1] << " " << q[2] << " " << q[3] << endl;

        }
        else
        {
            cv::Mat R = pKF->GetRotation();
            vector<float> q = Converter::toQuaternion(R);
            cv::Mat t = pKF->GetCameraCenter();
            f << setprecision(6) << 1e9*pKF->mTimeStamp << " " <<  setprecision(9) << t.at<float>(0) << " " << t.at<float>(1) << " " << t.at<float>(2) << " " << q[0] << " " << q[1] << " " << q[2] << " " << q[3] << endl;
        }
    }
    f.close();
}

void System::SaveKeyFrameTrajectoryEuRoC(const string &filename, int firstmapKF_size)
{
    cout << endl << "Saving keyframe trajectory to " << filename << " ..." << endl;

    vector<Map*> vpMaps = mpAtlas->GetAllMaps();
    Map* pBiggerMap;
    int numMaxKFs = 0;
    for(Map* pMap :vpMaps)
    {
        if(pMap->GetAllKeyFrames().size() > numMaxKFs)
        {
            numMaxKFs = pMap->GetAllKeyFrames().size();
            pBiggerMap = pMap;
        }
    }

    vector<KeyFrame*> vpKFs = pBiggerMap->GetAllKeyFrames();
    sort(vpKFs.begin(),vpKFs.end(),KeyFrame::lId);

    // Transform all keyframes so that the first keyframe is at the origin.
    // After a loop closure the first keyframe might not be at the origin.
    ofstream f;
    f.open(filename.c_str());
    f << fixed;

    for(size_t i=firstmapKF_size; i<vpKFs.size(); i++)
    {
        KeyFrame* pKF = vpKFs[i];

       // pKF->SetPose(pKF->GetPose()*Two);

        if(pKF->isBad())
            continue;
        if (mSensor == IMU_MONOCULAR || mSensor == IMU_STEREO)
        {
            cv::Mat R = pKF->GetImuRotation().t();
            vector<float> q = Converter::toQuaternion(R);
            cv::Mat twb = pKF->GetImuPosition();
            f << setprecision(6) << 1e9*pKF->mTimeStamp  << " " <<  setprecision(9) << twb.at<float>(0) << " " << twb.at<float>(1) << " " << twb.at<float>(2) << " " << q[0] << " " << q[1] << " " << q[2] << " " << q[3] << endl;

        }
        else
        {
            cv::Mat R = pKF->GetRotation();
            vector<float> q = Converter::toQuaternion(R);
            cv::Mat t = pKF->GetCameraCenter();
            f << setprecision(6) << 1e9*pKF->mTimeStamp << " " <<  setprecision(9) << t.at<float>(0) << " " << t.at<float>(1) << " " << t.at<float>(2) << " " << q[0] << " " << q[1] << " " << q[2] << " " << q[3] << endl;
        }
    }
    f.close();
}

void System::SaveTrajectoryKITTI(const string &filename)
{
    cout << endl << "Saving camera trajectory to " << filename << " ..." << endl;
    if(mSensor==MONOCULAR)
    {
        cerr << "ERROR: SaveTrajectoryKITTI cannot be used for monocular." << endl;
        return;
    }

    vector<KeyFrame*> vpKFs = mpAtlas->GetAllKeyFrames();
    sort(vpKFs.begin(),vpKFs.end(),KeyFrame::lId);

    // Transform all keyframes so that the first keyframe is at the origin.
    // After a loop closure the first keyframe might not be at the origin.
    cv::Mat Two = vpKFs[0]->GetPoseInverse();

    ofstream f;
    f.open(filename.c_str());
    f << fixed;

    // Frame pose is stored relative to its reference keyframe (which is optimized by BA and pose graph).
    // We need to get first the keyframe pose and then concatenate the relative transformation.
    // Frames not localized (tracking failure) are not saved.

    // For each frame we have a reference keyframe (lRit), the timestamp (lT) and a flag
    // which is true when tracking failed (lbL).
    list<ORB_SLAM3::KeyFrame*>::iterator lRit = mpTracker->mlpReferences.begin();
    list<double>::iterator lT = mpTracker->mlFrameTimes.begin();
    for(list<cv::Mat>::iterator lit=mpTracker->mlRelativeFramePoses.begin(), lend=mpTracker->mlRelativeFramePoses.end();lit!=lend;lit++, lRit++, lT++)
    {
        ORB_SLAM3::KeyFrame* pKF = *lRit;

        cv::Mat Trw = cv::Mat::eye(4,4,CV_32F);

        while(pKF->isBad())
        {
            Trw = Trw*pKF->mTcp;
            pKF = pKF->GetParent();
        }

        Trw = Trw*pKF->GetPose()*Two;

        cv::Mat Tcw = (*lit)*Trw;
        cv::Mat Rwc = Tcw.rowRange(0,3).colRange(0,3).t();
        cv::Mat twc = -Rwc*Tcw.rowRange(0,3).col(3);

        f << setprecision(9) << Rwc.at<float>(0,0) << " " << Rwc.at<float>(0,1)  << " " << Rwc.at<float>(0,2) << " "  << twc.at<float>(0) << " " <<
             Rwc.at<float>(1,0) << " " << Rwc.at<float>(1,1)  << " " << Rwc.at<float>(1,2) << " "  << twc.at<float>(1) << " " <<
             Rwc.at<float>(2,0) << " " << Rwc.at<float>(2,1)  << " " << Rwc.at<float>(2,2) << " "  << twc.at<float>(2) << endl;
    }
    f.close();
}


void System::SaveDebugData(const int &initIdx)
{
    // 0. Save initialization trajectory
    SaveTrajectoryEuRoC("init_FrameTrajectoy_" +to_string(mpLocalMapper->mInitSect)+ "_" + to_string(initIdx)+".txt");

    // 1. Save scale
    ofstream f;
    f.open("init_Scale_" + to_string(mpLocalMapper->mInitSect) + ".txt", ios_base::app);
    f << fixed;
    f << mpLocalMapper->mScale << endl;
    f.close();

    // 2. Save gravity direction
    f.open("init_GDir_" +to_string(mpLocalMapper->mInitSect)+ ".txt", ios_base::app);
    f << fixed;
    f << mpLocalMapper->mRwg(0,0) << "," << mpLocalMapper->mRwg(0,1) << "," << mpLocalMapper->mRwg(0,2) << endl;
    f << mpLocalMapper->mRwg(1,0) << "," << mpLocalMapper->mRwg(1,1) << "," << mpLocalMapper->mRwg(1,2) << endl;
    f << mpLocalMapper->mRwg(2,0) << "," << mpLocalMapper->mRwg(2,1) << "," << mpLocalMapper->mRwg(2,2) << endl;
    f.close();

    // 3. Save computational cost
    f.open("init_CompCost_" +to_string(mpLocalMapper->mInitSect)+ ".txt", ios_base::app);
    f << fixed;
    f << mpLocalMapper->mCostTime << endl;
    f.close();

    // 4. Save biases
    f.open("init_Biases_" +to_string(mpLocalMapper->mInitSect)+ ".txt", ios_base::app);
    f << fixed;
    f << mpLocalMapper->mbg(0) << "," << mpLocalMapper->mbg(1) << "," << mpLocalMapper->mbg(2) << endl;
    f << mpLocalMapper->mba(0) << "," << mpLocalMapper->mba(1) << "," << mpLocalMapper->mba(2) << endl;
    f.close();

    // 5. Save covariance matrix
    f.open("init_CovMatrix_" +to_string(mpLocalMapper->mInitSect)+ "_" +to_string(initIdx)+".txt", ios_base::app);
    f << fixed;
    for(int i=0; i<mpLocalMapper->mcovInertial.rows(); i++)
    {
        for(int j=0; j<mpLocalMapper->mcovInertial.cols(); j++)
        {
            if(j!=0)
                f << ",";
            f << setprecision(15) << mpLocalMapper->mcovInertial(i,j);
        }
        f << endl;
    }
    f.close();

    // 6. Save initialization time
    f.open("init_Time_" +to_string(mpLocalMapper->mInitSect)+ ".txt", ios_base::app);
    f << fixed;
    f << mpLocalMapper->mInitTime << endl;
    f.close();
}


int System::GetTrackingState()
{
    unique_lock<mutex> lock(mMutexState);
    return mTrackingState;
}

vector<MapPoint*> System::GetTrackedMapPoints()
{
    unique_lock<mutex> lock(mMutexState);
    return mTrackedMapPoints;
}

vector<cv::KeyPoint> System::GetTrackedKeyPointsUn()
{
    unique_lock<mutex> lock(mMutexState);
    return mTrackedKeyPointsUn;
}

double System::GetTimeFromIMUInit()
{
    double aux = mpLocalMapper->GetCurrKFTime()-mpLocalMapper->mFirstTs;
    if ((aux>0.) && mpAtlas->isImuInitialized())
        return mpLocalMapper->GetCurrKFTime()-mpLocalMapper->mFirstTs;
    else
        return 0.f;
}

bool System::isLost()
{
    if (!mpAtlas->isImuInitialized())
        return false;
    else
    {
        if ((mpTracker->mState==Tracking::LOST)) //||(mpTracker->mState==Tracking::RECENTLY_LOST))
            return true;
        else
            return false;
    }
}


bool System::isFinished()
{
    return (GetTimeFromIMUInit()>0.1);
}

void System::ChangeDataset()
{
    if(mpAtlas->GetCurrentMap()->KeyFramesInMap() < 12)
    {
        mpTracker->ResetActiveMap();
    }
    else
    {
        mpTracker->CreateMapInAtlas();
    }

    mpTracker->NewDataset();
}

void System::SaveAtlas(int type){

    string resultSava_path = "/home/ucrnet/Desktop/workspace/ORBSLAM3/Yunshu_programs/Shellscommends/testKeyFramesize/";
    string keyframesizeFile = "KFsize.txt";
    ofstream myfile;
    myfile.open(resultSava_path + keyframesizeFile, std::ios_base::app);
    myfile << "keyframe number: " << mpAtlas->GetAllKeyFrames().size() << "\n";

    
    cout << endl << "Enter the name of the file if you want to save the current Atlas session. To exit press ENTER: ";

    struct timeval start0, end0, presaveStart0, presaveEnd0;
    gettimeofday(&start0, NULL);
    string saveFileName;
    getline(cin,saveFileName);
    if(!saveFileName.empty())
    {
        //clock_t start = clock();

        // Save the current session
        gettimeofday(&presaveStart0, NULL);
        std::cout << "Atlas::PreSave() start" << std::endl;
        mpAtlas->PreSave();
	std::cout << "mpKeyFrameDatabase PreSave() start" << std::endl;
        mpKeyFrameDatabase->PreSave();
	std::cout << "mpKeyFrameDatabase PreSave() end" << std::endl;
        gettimeofday(&presaveEnd0, NULL);
        double elapsed = ((presaveEnd0.tv_sec - presaveStart0.tv_sec) * 1000) + (presaveEnd0.tv_sec / 1000 - presaveStart0.tv_sec / 1000);

        cout << "*****************save BINARY_FILE  presave time:  " << elapsed << " ******************* " << endl;

        string pathSaveFileName = "./";
        pathSaveFileName = pathSaveFileName.append(saveFileName);
        pathSaveFileName = pathSaveFileName.append(".osa");

        //string strVocabularyChecksum = CalculateCheckSum(mStrVocabularyFilePath,TEXT_FILE);
        //std::size_t found = mStrVocabularyFilePath.find_last_of("/\\");
        //string strVocabularyName = mStrVocabularyFilePath.substr(found+1);

        if(type == TEXT_FILE) // File text
        {
            cout << "Starting to write the save text file " << endl;
            std::remove(pathSaveFileName.c_str());
            std::ofstream ofs(pathSaveFileName, std::ios::binary);
            boost::archive::text_oarchive oa(ofs);

            //oa << strVocabularyName;
            //oa << strVocabularyChecksum;
            oa << mpAtlas;
            //Yunshucommented
            //oa << mpKeyFrameDatabase;
            cout << "End to write the save text file" << endl;
        }
        else if(type == BINARY_FILE) // File binary
        {
            cout << "Starting to write the save binary file" << endl;
            std::remove(pathSaveFileName.c_str());
	    cout << "OK1" << endl;
            std::ofstream ofs(pathSaveFileName, std::ios::binary);
	    cout << "OK2" <<pathSaveFileName <<endl;
            boost::archive::binary_oarchive oa(ofs);
	    cout << "OK3" << endl;
	    int test = 5;
	    oa << test;
	    cout << "OK3.5" << endl;
            //oa << strVocabularyName;
            //oa << strVocabularyChecksum;
            oa << mpAtlas;
	    cout << "OK4" << endl;
        //Yunshucommented
           // oa << mpKeyFrameDatabase;
	    cout << "OK5" << endl;
            cout << "End to write save binary file" << endl;
        }

        gettimeofday(&end0, NULL);
        //elapsed = ((end0.tv_sec - start0.tv_sec) * 1000) + (end0.tv_sec / 1000 - start0.tv_sec / 1000);
        elapsed = (end0.tv_sec * 1000000 + end0.tv_usec)  - (start0.tv_sec * 1000000 + start0.tv_usec);
        double saveTimeSeq = elapsed;
        cout << "*****************save BINARY_FILE  time:  " << saveTimeSeq << " ******************* " << endl;
        //clock_t timeElapsed = clock() - start;
        //unsigned msElapsed = timeElapsed / (CLOCKS_PER_SEC / 1000);
        //cout << "Binary file saved in " << msElapsed << " ms" << endl;
    }
}



void System::SaveAtlas_Yunshu(string s){

    int type = BINARY_FILE;
    struct timeval start0, end0, presaveStart0, presaveEnd0;
    gettimeofday(&start0, NULL);
    string saveFileName;
    saveFileName = s;
    ofstream file_out;
    if(!saveFileName.empty())
    {
        //clock_t start = clock();
        cout << "*****************Ther is no need of input" << " ******************* " << endl;
        // Save the current session
        gettimeofday(&presaveStart0, NULL);
        std::cout << "Atlas::PreSave() start" << std::endl;
        mpAtlas->PreSave();
	std::cout << "mpKeyFrameDatabase PreSave() start" << std::endl;
        mpKeyFrameDatabase->PreSave();
	std::cout << "mpKeyFrameDatabase PreSave() end" << std::endl;
        gettimeofday(&presaveEnd0, NULL);
        double elapsed = (presaveEnd0.tv_sec * 1000000 + presaveEnd0.tv_usec)  - (presaveStart0.tv_sec * 1000000 + presaveStart0.tv_usec );

        cout << "*****************save BINARY_FILE  presave time:  " << elapsed << " ******************* " << endl;

        string pathSaveFileName = "./";
        //pathSaveFileName = pathSaveFileName.append(saveFileName);
        pathSaveFileName = pathSaveFileName.append(s +".osa");

        cout << "pathSaveFileName " << pathSaveFileName << endl;

        //string strVocabularyChecksum = CalculateCheckSum(mStrVocabularyFilePath,TEXT_FILE);
        //std::size_t found = mStrVocabularyFilePath.find_last_of("/\\");
        //string strVocabularyName = mStrVocabularyFilePath.substr(found+1);
file_out.open("timeseris.txt", std::ios_base::app);
        if(type == TEXT_FILE) // File text
        {
            cout << "Starting to write the save text file " << endl;
            cout << "pathSaveFileName " << pathSaveFileName<< endl;

            cout << "pathSaveFileName.c_str " << pathSaveFileName.c_str()<< endl;





            std::remove(pathSaveFileName.c_str());
            cout << "pathSaveFileName: " << pathSaveFileName<< endl;
            std::ofstream ofs(pathSaveFileName, std::ios::binary);
            boost::archive::text_oarchive oa(ofs);

            //oa << strVocabularyName;
            //oa << strVocabularyChecksum;
            oa << mpAtlas;
            oa << mpKeyFrameDatabase;
            cout << "End to write the save text file" << endl;
        }
        else if(type == BINARY_FILE) // File binary
        {

            gettimeofday(&presaveStart0, NULL);
            cout << "Starting to write the save binary file" << endl;
          //  cout << "pathSaveFileName " << pathSaveFileName<< endl;

           // cout << "pathSaveFileName.c_str " << pathSaveFileName.c_str()<< endl;

           // std::remove(pathSaveFileName.c_str());
         //   cout << "pathSaveFileName: " << pathSaveFileName<< endl;
         
    
    file_out << "Before saving atlas: presaveStart0: " << presaveStart0.tv_sec  * 1000000 + presaveStart0.tv_usec << endl;
	    cout << "OK1" << endl;
            std::ofstream ofs(pathSaveFileName, std::ios::binary);
	    cout << "OK2" << endl;
            boost::archive::binary_oarchive oa(ofs);
	    cout << "OK3" << endl;
	    int test = 5;


        //for file transmission
        //int t = client();
	    oa << test;
	    cout << "OK3.5" << endl;
            //oa << strVocabularyName;
            //oa << strVocabularyChecksum;
            oa << mpAtlas;
	    cout << "OK4" << endl;

        //timeer Yunshu todo
            oa << mpKeyFrameDatabase;
	    cout << "OK5" << endl;
            cout << "End to write save binary file" << endl;
        }

        gettimeofday(&end0, NULL);
        elapsed = (end0.tv_sec * 1000000 + end0.tv_usec)  - (presaveStart0.tv_sec * 1000000 + presaveStart0.tv_usec);
        double saveTimeSeq = elapsed;
        cout << "*****************save BINARY_FILE  time:  " << saveTimeSeq << " ******************* " << endl;
      //ofstream file_out;
    //file_out.open("timeseris.txt", std::ios_base::app);
    file_out << "save atlas end0 time at: " << end0.tv_sec * 1000000 + end0.tv_usec << endl;
    file_out << "save atlas serialization time: " << elapsed << endl;
      
        //clock_t timeElapsed = clock() - start;
        //unsigned msElapsed = timeElapsed / (CLOCKS_PER_SEC / 1000);
        //cout << "Binary file saved in " << msElapsed << " ms" << endl;
    }
   //char * s = "client0.osa";
    //SLAM->client(8081, s);
    //SLAM->saveAllFiles();

}


bool System::LoadAtlas(string filename, int type)
{
    string strFileVoc, strVocChecksum;
    bool isRead = false;
    struct timeval start0, end0, presaveStart0, presaveEnd0;

    if(type == TEXT_FILE) // File text
    {
        cout << "Starting to read the save text file " << endl;
        std::ifstream ifs(filename, std::ios::binary);
        if(!ifs.good())
        {
            cout << "Load file not found" << endl;
            return false;
        }
        boost::archive::text_iarchive ia(ifs);
        //ia >> strFileVoc;
        //ia >> strVocChecksum;
        ia >> mpAtlas;
        ia >> mpKeyFrameDatabase;
        cout << "End to load the save text file " << endl;
        isRead = true;
    }
    else if(type == BINARY_FILE) // File binary
    {
        cout << "Starting to read the save binary file"  << endl;
	cout << "loadAtlas, filename: " << filename << endl;
    gettimeofday(&start0, NULL);
    ofstream file_out;
    file_out.open("timeseris.txt", std::ios_base::app);
    file_out << "Before Loading atlas: start0: " << start0.tv_sec * 1000000 + start0.tv_usec<< endl;
        std::ifstream ifs(filename, std::ios::binary);
        if(!ifs.good())
        {
            cout << "Load file not found" << endl;
            return false;
        }
        boost::archive::binary_iarchive ia(ifs);
        //ia >> strFileVoc;
        //ia >> strVocChecksum;
	    int test = 0;//set as 5
	    ia >> test;
        ia >> mpAtlas;
gettimeofday(&end0, NULL);
        file_out << "After Loading atlas deserialization: end0: " << end0.tv_sec * 1000000 + end0.tv_usec << endl;
        double elapsed = (end0.tv_sec * 1000000 + end0.tv_usec)  - (start0.tv_sec * 1000000 + start0.tv_usec);
        file_out << "Load atlas deserialization time: " << elapsed << endl;

                mpAtlas->SetKeyFrameDababase(mpKeyFrameDatabase);
        mpAtlas->SetORBVocabulary(mpVocabulary);

        

        cout << "now fix keyframe database" << endl;
                    //Yunshucommented
        //ia >> mpKeyFrameDatabase;
        cout << "End to load the save binary file" << endl;
        isRead = true;
    }

    if(isRead)
    {
                return true;
    }
    return false;
}


bool System::LoadAtlas_second(string filename, int type)
{
    string strFileVoc, strVocChecksum;
    bool isRead = false;

    if(type == TEXT_FILE) // File text
    {
        cout << "Starting to read the save text file _second" << endl;
        std::ifstream ifs(filename, std::ios::binary);
        // if(!ifs.good())
        // {
        //     cout << "Load file not found _second" << endl;
        //     return false;
        // }
        boost::archive::text_iarchive ia(ifs);
        //ia >> strFileVoc;
        //ia >> strVocChecksum;
        ia >> mpAtlas_second;
                    //Yunshucommented
        //ia >> mpKeyFrameDatabase_second;
        cout << "End to load the save text file " << endl;
        isRead = true;
    }
    else if(type == BINARY_FILE) // File binary
    {
        cout << "Starting to read the save binary file _second"  << endl;
	cout << "loadAtlas, filename: _second" << filename << endl;
        std::ifstream ifs(filename, std::ios::binary);
        // if(!ifs.good())
        // {
        //     cout << "Load file not found" << endl;
        //     return false;
        // }
        boost::archive::binary_iarchive ia(ifs);
        //ia >> strFileVoc;
        //ia >> strVocChecksum;
	int test = 0;//set as 5
	ia >> test;
    //std::cout << "ia" << ia.to_string() <<std::endl;
        ia >> mpAtlas_second;
	cout << "End to load mpAtlas_second" << endl;
	//TODO Uncomment
       //ia >> mpKeyFrameDatabase_second;
        cout << "End to load the save binary file" << endl;
        isRead = true;
    }

    if(isRead)
    {
        return true;
    }

    return false;
}


string System::CalculateCheckSum(string filename, int type)
{
    string checksum = "";

    unsigned char c[MD5_DIGEST_LENGTH];

    std::ios_base::openmode flags = std::ios::in;
    if(type == BINARY_FILE) // Binary file
        flags = std::ios::in | std::ios::binary;

    ifstream f(filename.c_str(), flags);
    if ( !f.is_open() )
    {
        cout << "[E] Unable to open the in file " << filename << " for Md5 hash." << endl;
        return checksum;
    }

    MD5_CTX md5Context;
    char buffer[1024];

    MD5_Init (&md5Context);
    while ( int count = f.readsome(buffer, sizeof(buffer)))
    {
        MD5_Update(&md5Context, buffer, count);
    }

    f.close();

    MD5_Final(c, &md5Context );

    for(int i = 0; i < MD5_DIGEST_LENGTH; i++)
    {
        char aux[10];
        sprintf(aux,"%02x", c[i]);
        checksum = checksum + aux;
    }

    return checksum;
}














































} //namespace ORB_SLAM

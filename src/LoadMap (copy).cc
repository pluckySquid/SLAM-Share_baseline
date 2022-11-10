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



#include "LoadMap.h"
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

namespace ORB_SLAM3
{

//Verbose::eLevel Verbose::th = Verbose::VERBOSITY_NORMAL;

LoadMap::LoadMap(const string &strVocFile, const string &strSettingsFile, const eSensor sensor,
               const bool bUseViewer, const int initFr, const string &strSequence, const string &strLoadingFile, const string &strLoadingFile_second):
    mSensor(sensor), mpViewer(static_cast<Viewer*>(NULL)), mbReset(false), mbResetActiveMap(false),
    mbActivateLocalizationMode(false), mbDeactivateLocalizationMode(false)
{
    // Output welcome message
    cout << endl <<
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
    /*cout << endl << "Loading ORB Vocabulary. This could take a while..." << endl;

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
    mpAtlas = new Atlas(0);*/
    //----

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

        cout << "Load File" << endl;

        // Load the file with an earlier session
	//clock_t start = clock();
	struct timeval start, end;
	gettimeofday(&start, NULL);
	
        //clock_t start = clock();
        bool isRead = LoadAtlas(strLoadingFile,BINARY_FILE);

        if(!isRead)
        {
            cout << "Error to load the file, please try with other session file or vocabulary file" << endl;
            exit(-1);
        }
        mpKeyFrameDatabase = new KeyFrameDatabase(*mpVocabulary);

        mpAtlas->SetKeyFrameDababase(mpKeyFrameDatabase);
        mpAtlas->SetORBVocabulary(mpVocabulary);
        mpAtlas->PostLoad();
        //cout << "KF in DB: " << mpKeyFrameDatabase->mnNumKFs << "; words: " << mpKeyFrameDatabase->mnNumWords << endl;

        loadedAtlas = true;

        mpAtlas->CreateNewMap();

        //clock_t timeElapsed = clock() - start;
        //unsigned msElapsed = timeElapsed / (CLOCKS_PER_SEC / 1000);
        //cout << "Binary file read in " << msElapsed << " ms" << endl;
	gettimeofday(&end, NULL);
	double elapsed = ((end.tv_sec - start.tv_sec) * 1000) 
        	+ (end.tv_usec / 1000 - start.tv_usec / 1000);
	cout << "elapsed time in loading .bin file: " << elapsed << endl;

        //usleep(10*1000*1000);
	cout << "------press enter to continue------" << endl;
	string tmp;
    	getline(cin,tmp);

        if(!strLoadingFile.empty()){
	    bool isRead_second = LoadAtlas_second(strLoadingFile_second,BINARY_FILE);
	    //indexing etc?....
	}
    }


    if (mSensor==IMU_STEREO || mSensor==IMU_MONOCULAR)
        mpAtlas->SetInertialSensor();

    //Create Drawers. These are used by the Viewer
    mpFrameDrawer = new FrameDrawer(mpAtlas);
    mpMapDrawer = new MapDrawer(mpAtlas, strSettingsFile);

    //Initialize the Tracking thread
    //(it will live in the main thread of execution, the one that called this constructor)
    //cout << "Seq. Name: " << strSequence << endl;
    //mpTracker = new Tracking(this, mpVocabulary, mpFrameDrawer, mpMapDrawer,
    //                         mpAtlas, mpKeyFrameDatabase, strSettingsFile, mSensor, strSequence);

    //Initialize the Local Mapping thread and launch
    //mpLocalMapper = new LocalMapping(this, mpAtlas, mSensor==MONOCULAR || mSensor==IMU_MONOCULAR, mSensor==IMU_MONOCULAR || mSensor==IMU_STEREO, strSequence);
    //mptLocalMapping = new thread(&ORB_SLAM3::LocalMapping::Run,mpLocalMapper);
    //mpLocalMapper->mInitFr = initFr;
    //mpLocalMapper->mThFarPoints = fsSettings["thFarPoints"];
/*
    if(mpLocalMapper->mThFarPoints!=0)
    {
        cout << "Discard points further than " << mpLocalMapper->mThFarPoints << " m from current camera" << endl;
        mpLocalMapper->mbFarPoints = true;
    }
    else
        mpLocalMapper->mbFarPoints = false;
*/

    //Initialize the Loop Closing thread and launch
    // mSensor!=MONOCULAR && mSensor!=IMU_MONOCULAR
    mpLoopCloser = new LoopClosing(mpAtlas, mpKeyFrameDatabase, mpVocabulary, mSensor!=MONOCULAR); // mSensor!=MONOCULAR);
    mptLoopClosing = new thread(&ORB_SLAM3::LoopClosing::Run, mpLoopCloser);

    //Initialize the Viewer thread and launch
    /*if(bUseViewer)
    {
        mpViewer = new Viewer(this, mpFrameDrawer,mpMapDrawer,mpTracker,strSettingsFile);
        mptViewer = new thread(&Viewer::Run, mpViewer);
        mpTracker->SetViewer(mpViewer);
        mpLoopCloser->mpViewer = mpViewer;
        mpViewer->both = mpFrameDrawer->both;
    }*/

    //Set pointers between threads
    /*mpTracker->SetLocalMapper(mpLocalMapper);
    mpTracker->SetLoopClosing(mpLoopCloser);

    mpLocalMapper->SetTracker(mpTracker);
    mpLocalMapper->SetLoopCloser(mpLoopCloser);

    mpLoopCloser->SetTracker(mpTracker);
    mpLoopCloser->SetLocalMapper(mpLocalMapper);*/

    // Fix verbosity
    Verbose::SetTh(Verbose::VERBOSITY_QUIET);
}



void LoadMap::Shutdown()
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
            cout << "mpLoopCloser is not finished" << endl;
        if(mpLoopCloser->isRunningGBA()){
            cout << "mpLoopCloser is running GBA" << endl;
            cout << "break anyway..." << endl;
            break;
        }
        usleep(5000);
    }

    if(mpViewer)
        pangolin::BindToContext("ORB-SLAM2: Map Viewer");
    SaveAtlas(BINARY_FILE);
}




void LoadMap::SaveAtlas(int type){
    cout << endl << "Enter the name of the file if you want to save the current Atlas session. To exit press ENTER: ";
    string saveFileName;
    getline(cin,saveFileName);
    if(!saveFileName.empty())
    {
        //clock_t start = clock();

        // Save the current session
        std::cout << "Atlas::PreSave() start" << std::endl;
        mpAtlas->PreSave();
	std::cout << "mpKeyFrameDatabase PreSave() start" << std::endl;
        mpKeyFrameDatabase->PreSave();
	std::cout << "mpKeyFrameDatabase PreSave() end" << std::endl;

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
            oa << mpKeyFrameDatabase;
            cout << "End to write the save text file" << endl;
        }
        else if(type == BINARY_FILE) // File binary
        {
            cout << "Starting to write the save binary file" << endl;
            std::remove(pathSaveFileName.c_str());
	    cout << "OK1" << endl;
            std::ofstream ofs(pathSaveFileName, std::ios::binary);
	    cout << "OK2" << endl;
            boost::archive::binary_oarchive oa(ofs);
	    cout << "OK3" << endl;
	    int test = 5;
	    oa << test;
	    cout << "OK3.5" << endl;
            //oa << strVocabularyName;
            //oa << strVocabularyChecksum;
            oa << mpAtlas;
	    cout << "OK4" << endl;
            oa << mpKeyFrameDatabase;
	    cout << "OK5" << endl;
            cout << "End to write save binary file" << endl;
        }

        //clock_t timeElapsed = clock() - start;
        //unsigned msElapsed = timeElapsed / (CLOCKS_PER_SEC / 1000);
        //cout << "Binary file saved in " << msElapsed << " ms" << endl;
    }
}


bool LoadMap::LoadAtlas(string filename, int type)
{
    string strFileVoc, strVocChecksum;
    bool isRead = false;

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
        ia >> mpKeyFrameDatabase;
        cout << "End to load the save binary file" << endl;
        isRead = true;
    }

    if(isRead)
    {
        //Check if the vocabulary is the same
        /*string strInputVocabularyChecksum = CalculateCheckSum(mStrVocabularyFilePath,TEXT_FILE);

        if(strInputVocabularyChecksum.compare(strVocChecksum) != 0)
        {
            cout << "The vocabulary load isn't the same which the load session was created " << endl;
            cout << "-Vocabulary name: " << strFileVoc << endl;
            return false; // Both are differents
        }*/

        return true;
    }
    return false;
}

bool LoadMap::LoadAtlas_second(string filename, int type)
{
    string strFileVoc, strVocChecksum;
    bool isRead = false;

    if(type == TEXT_FILE) // File text
    {
        cout << "Starting to read the save text file _second" << endl;
        std::ifstream ifs(filename, std::ios::binary);
        if(!ifs.good())
        {
            cout << "Load file not found _second" << endl;
            return false;
        }
        boost::archive::text_iarchive ia(ifs);
        //ia >> strFileVoc;
        //ia >> strVocChecksum;
        ia >> mpAtlas_second;
        ia >> mpKeyFrameDatabase_second;
        cout << "End to load the save text file " << endl;
        isRead = true;
    }
    else if(type == BINARY_FILE) // File binary
    {
        cout << "Starting to read the save binary file _second"  << endl;
	cout << "loadAtlas, filename: _second" << filename << endl;
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
        ia >> mpAtlas_second;
        ia >> mpKeyFrameDatabase_second;
        cout << "End to load the save binary file" << endl;
        isRead = true;
    }

    if(isRead)
    {
        return true;
    }
    return false;
}

} //namespace ORB_SLAM



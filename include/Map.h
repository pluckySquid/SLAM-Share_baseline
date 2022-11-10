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


#ifndef MAP_H
#define MAP_H

#include "MapPoint.h"
#include "KeyFrame.h"
#include "iostream"

#include <set>
#include <pangolin/pangolin.h>
#include <mutex>

#include <boost/serialization/base_object.hpp>


namespace ORB_SLAM3
{

class MapPoint;
class KeyFrame;
class Atlas;
class KeyFrameDatabase;

class Map
{
    friend class boost::serialization::access;

    template<class Archive>
    void serialize(Archive &ar, const unsigned int version)
    {
	std::cout << "Map OK1 GetKeyFrameSize() map size is: " << GetKeyFrameSize() << std::endl;
	std::vector<KeyFrame*> vmspKeyFrames;
	std::vector<MapPoint*> vmspMapPoints;
        ar & mnId;
        ar & mnInitKFid;
        ar & mnMaxKFid;
        ar & mnBigChangeIdx;
        // Set of KeyFrames and MapPoints, in this version the set serializator is not working
	//xukan uncommented the following 2
	if (Archive::is_saving::value){
	    //save
	    vmspKeyFrames.resize(mspKeyFrames.size());
	    vmspMapPoints.resize(mspMapPoints.size());
	    std::cout << "Map OK2, mspKeyFrames size is " << mspKeyFrames.size() << std::endl;
	    std::copy(mspKeyFrames.begin(), mspKeyFrames.end(), vmspKeyFrames.begin());
	    std::cout << "Map OK3, mspMapPoints size is " << mspMapPoints.size() << std::endl;
	    std::copy(mspMapPoints.begin(), mspMapPoints.end(), vmspMapPoints.begin());
	    std::cout << "Map OK4" << std::endl;
	    ar & vmspMapPoints;
	    std::cout << "Map OK5" << std::endl;
	    ar & vmspKeyFrames;
	    std::cout << "Map OK6" << std::endl;
	}else{//load

    	    std::cout << "Map load 1 " << mspKeyFrames.size() << std::endl;

	    ar & vmspMapPoints;
	    ar & vmspKeyFrames;
            	    std::cout << "Map load 2.2 " << mspKeyFrames.size() << std::endl;
        std::cout << "Map load 3 " << mspKeyFrames.size() << std::endl;

	    mspKeyFrames.clear();
	    mspMapPoints.clear();
      std::cout << "Map load 2.3 " << mspKeyFrames.size() << std::endl;

            if ( vmspKeyFrames.size() > 0 )

            	    std::cout << "Map load 3 " << mspKeyFrames.size() << std::endl;
            if ( vmspKeyFrames.size() > 0 )
	    for(auto k : vmspKeyFrames) Map::AddKeyFrame(k);
            	    std::cout << "Map load 4 " << mspKeyFrames.size() << std::endl;
            if ( vmspKeyFrames.size() > 0 )
	    for(auto m : vmspMapPoints) Map::AddMapPoint(m);
            	    std::cout << "Map load 5 " << mspKeyFrames.size() << std::endl;

	}
        //ar & mspKeyFrames;
        //ar & mspMapPoints;
           if ( vmspKeyFrames.size() > 0 )
                {
                        ar & mvpBackupKeyFrames;
                        ar & mvpBackupMapPoints;
                std::cout << "Map load 6 " << mspKeyFrames.size() << std::endl;
                        ar & mvBackupKeyFrameOriginsId;
                std::cout << "Map load 7 " << mspKeyFrames.size() << std::endl;
                        ar & mnBackupKFinitialID;
                        ar & mnBackupKFlowerID;
                std::cout << "Map load 8 " << mspKeyFrames.size() << std::endl;
                        ar & mbImuInitialized;
                        ar & mbIsInertial;
                        ar & mbIMU_BA1;
                        ar & mbIMU_BA2;
                std::cout << "Map load 9 " << mspKeyFrames.size() << std::endl;
                        ar & mnInitKFid;
                        ar & mnMaxKFid;
                        ar & mnLastLoopKFid;
                                }
                        //ar & mpKFinitial;
                        //ar & mpKFlowerID;
         std::cout << "Map OK2" << std::endl;
    }

public:
    Map();
    Map(int initKFid);
    ~Map();

    int GetKeyFrameSize();
    void AddKeyFrame(KeyFrame* pKF, bool skip = false);
    void AddMapPoint(MapPoint* pMP);
    void EraseMapPoint(MapPoint* pMP);
    void EraseKeyFrame(KeyFrame* pKF);
    void SetReferenceMapPoints(const std::vector<MapPoint*> &vpMPs);
    void InformNewBigChange();
    int GetLastBigChangeIdx();

    std::vector<KeyFrame*> GetAllKeyFrames();
    std::vector<MapPoint*> GetAllMapPoints();
    std::vector<MapPoint*> GetReferenceMapPoints();

    long unsigned int MapPointsInMap();
    long unsigned  KeyFramesInMap();

    long unsigned int GetId();

    long unsigned int GetInitKFid();
    void SetInitKFid(long unsigned int initKFif);
    long unsigned int GetMaxKFid();

    KeyFrame* GetOriginKF();

    void SetCurrentMap();
    void SetStoredMap();

    bool HasThumbnail();
    bool IsInUse();

    void SetBad();
    bool IsBad();

    void clear();

    int GetMapChangeIndex();
    void IncreaseChangeIndex();
    int GetLastMapChange();
    void SetLastMapChange(int currentChangeId);

    void SetImuInitialized();
    bool isImuInitialized();

    void RotateMap(const cv::Mat &R);
    void ApplyScaledRotation(const cv::Mat &R, const float s, const bool bScaledVel=false, const cv::Mat t=cv::Mat::zeros(cv::Size(1,3),CV_32F));

    void SetInertialSensor();
    bool IsInertial();
    void SetIniertialBA1();
    void SetIniertialBA2();
    bool GetIniertialBA1();
    bool GetIniertialBA2();

    void PrintEssentialGraph();
    bool CheckEssentialGraph();
    void ChangeId(long unsigned int nId);

    unsigned int GetLowerKFID();

    void PreSave(std::set<GeometricCamera*> &spCams);
    void PostLoad(KeyFrameDatabase* pKFDB, ORBVocabulary* pORBVoc, map<long unsigned int, KeyFrame*>& mpKeyFrameId, map<unsigned int, GeometricCamera*> &mpCams);
    void PostLoad_second(KeyFrameDatabase* pKFDB, ORBVocabulary* pORBVoc, map<long unsigned int, KeyFrame*>& mpKeyFrameId, map<unsigned int, GeometricCamera*> &mpCams);


    void printReprojectionError(list<KeyFrame*> &lpLocalWindowKFs, KeyFrame* mpCurrentKF, string &name, string &name_folder);

    vector<KeyFrame*> mvpKeyFrameOrigins;
    vector<unsigned long int> mvBackupKeyFrameOriginsId;
    KeyFrame* mpFirstRegionKF;
    std::mutex mMutexMapUpdate;

    // This avoid that two points are created simultaneously in separate threads (id conflict)
    std::mutex mMutexPointCreation;

    bool mbFail;

    // Size of the thumbnail (always in power of 2)
    static const int THUMB_WIDTH = 512;
    static const int THUMB_HEIGHT = 512;

    static long unsigned int nNextId;
    static bool needIndexProcess;

//protected:

    long unsigned int mnId;

    std::set<MapPoint*> mspMapPoints;
    std::set<KeyFrame*> mspKeyFrames;

    std::vector<MapPoint*> mvpBackupMapPoints;
    std::vector<KeyFrame*> mvpBackupKeyFrames;

    KeyFrame* mpKFinitial;
    KeyFrame* mpKFlowerID;

    unsigned long int mnBackupKFinitialID;
    unsigned long int mnBackupKFlowerID;

    std::vector<MapPoint*> mvpReferenceMapPoints;

    bool mbImuInitialized;

    int mnMapChange;
    int mnMapChangeNotified;

    long unsigned int mnInitKFid;
    long unsigned int mnMaxKFid;
    long unsigned int mnLastLoopKFid;

    // Index related to a big change in the map (loop closure, global BA)
    int mnBigChangeIdx;


    // View of the map in aerial sight (for the AtlasViewer)
    GLubyte* mThumbnail;

    bool mIsInUse;
    bool mHasTumbnail;
    bool mbBad = false;

    bool mbIsInertial;
    bool mbIMU_BA1;
    bool mbIMU_BA2;

    std::mutex mMutexMap;
};

} //namespace ORB_SLAM3

#endif // MAP_H

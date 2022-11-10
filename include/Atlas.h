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

#ifndef ATLAS_H
#define ATLAS_H

#include "Map.h"
#include "MapPoint.h"
#include "KeyFrame.h"
#include "GeometricCamera.h"
#include "Pinhole.h"
#include "KannalaBrandt8.h"
//BOOST_CLASS_EXPORT(ORB_SLAM3::KannalaBrandt8)
//BOOST_CLASS_EXPORT(ORB_SLAM3::Pinhole)

#include <set>
#include <mutex>
#include <boost/serialization/vector.hpp>
#include <boost/serialization/export.hpp>
#include "iostream"
#include <assert.h>
#include <time.h>
#include <sys/time.h>

namespace ORB_SLAM3
{
class Viewer;
class Map;
class MapPoint;
class KeyFrame;
class KeyFrameDatabase;
class Frame;
class KannalaBrandt8;
class Pinhole;

//BOOST_CLASS_EXPORT_GUID(Pinhole, "Pinhole")
//BOOST_CLASS_EXPORT_GUID(KannalaBrandt8, "KannalaBrandt8")

struct Pinsave{
    unsigned int mnId;
    unsigned int mnType;
    float fx, fy, cx, cy;
    Pinsave(){}
    Pinsave(GeometricCamera *gc){
	mnId = gc->GetId();
	mnType = gc->GetType();
	checkGeo(gc);
	fx = gc->mvParameters[0];
	fy = gc->mvParameters[1];
	cx = gc->mvParameters[2];
	cy = gc->mvParameters[3];
    }

    static Pinsave Geo2Pins(GeometricCamera* gc){
	checkGeo(gc);
	Pinsave res;
	res.fx = gc->mvParameters[0];
	res.fy = gc->mvParameters[1];
	res.cx = gc->mvParameters[2];
	res.cy = gc->mvParameters[3];
	res.mnId = gc->mnId;
	res.mnType = gc->mnType;
	return res;
    }
    static GeometricCamera* Pins2Geo(Pinsave ps){
	vector<float> vCamCalib{ps.fx,ps.fy,ps.cx,ps.cy};
	//bastract can new.
	//GeometricCamera* res = new GeometricCamera(vCamCalib);
	GeometricCamera* res = NULL;
	res->mnId = ps.mnId;
	res->mnType = ps.mnType;
	return res;
    }

/*    static Pinhole* Pins2Pin(Pinsave ps){
	vector<float> vCamCalib{ps.fx,ps.fy,ps.cx,ps.cy};
	Pinhole* res =  new Pinhole(vCamCalib);
	res->mnId = ps.mnId;
	res->mnType = ps.mnType;
	return res;
    }
    static Pinsave Pin2Pins(Pinhole* p){
	Pinsave res;
	res.fx = p->mvParameters[0];
	res.fy = p->mvParameters[1];
	res.cx = p->mvParameters[2];
	res.cy = p->mvParameters[3];
	res.mnId = p->mnId;
	res.mnType = p->mnType;
	return res;
    }*/

    static void checkGeo(GeometricCamera* gc){
	if(gc->GetType() != gc->CAM_PINHOLE){
	    std::cout << "ERROR!!!! ERROR!!!! We current only support Pinhole camera! Happened in struct Pinsave at Atlas.h gc->GetType() != gc->CAM_PINHOLE" << std::endl;
	    assert(false);
	}
	if(gc->mvParameters.size() != 4){
		std::cout << "ERROR!!!! ERROR!!!! We current only support Pinhole camera! Happened in struct Pinsave at Atlas.h gc.mvParameters.size() != 4" << std::endl;
	    assert(false);
	}
    }

private:
    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive &ar, const unsigned int version){
	ar & mnId;
	ar & mnType;
	ar & fx;
	ar & fy;
	ar & cx;
	ar & cy;
    }

};


class Atlas
{
    friend class boost::serialization::access;

    template<class Archive>
    void serialize(Archive &ar, const unsigned int version)
    {
        ar.template register_type<Pinhole>();
    	ar.template register_type<KannalaBrandt8>();

        // Save/load the set of maps, the set is broken in libboost 1.58 for ubuntu 16.04
        //ar & mspMaps;
	//definition: std::set<Map*> mspMaps;
	//***Danger*** assumer the loader's mspMaps is empty.
	/*std::vector<Map*> mvpMaps(mspMaps.begin(), mspMaps.end());
	ar & mvpMaps;
	if(Archive::is_loading::value){
	    for(auto m : mvpMaps){
		mspMaps.insert(m);
	    }
	}*/
	//clock_t start = clock();
	struct timeval start, end;
	gettimeofday(&start, NULL);
	std::cout << "Atlas save OK1" << std::endl;
        ar & mvpBackupMaps;
	std::cout << "Atlas save OK2, mvpBackupMaps size: " << mvpBackupMaps.size() << std::endl;
	std::cout << "mvpCameras size: " << mvpCameras.size() << std::endl;
	if(mvpCameras.size() == 0){
	    std::cout << "mvpCameras size is zero" << std::endl;
	}else{
	    bool flag = false;
	    for(auto t : mvpCameras){
		if(t == NULL){
		    flag = true;
		    break;
		}
	    }
	    if(flag){
	    	std::cout << "mvpCameras has NULL pointer, size: " << mvpCameras.size() << std::endl;
	    }else{
		std::cout << "mvpCameras does not have NULL pointer, size: " << mvpCameras.size()  << std::endl;
	    }
	}

	    std::cout << "we are close to find the error atlas.h 1" << std::endl;

	//xukan commented 03/12/2021
        ar & mvpCameras;

		    std::cout << "we are close to find the error atlas.h 1 " << std::endl;

	int mvpCameras_size = mvpCameras.size();
	int mvpBackupCamPin_size =  mvpBackupCamPin.size();
	int mvpBackupCamKan_size = mvpBackupCamKan.size();

	if(mvpBackupCamKan_size != 0){
	    std::cout << "ERROR!!!! We current only support Pinhole camera!, size: " << mvpBackupCamKan_size << std::endl;
	    assert(false);
	}
	std::cout << "Atlas save OK3" << std::endl;

	ar & mvpCameras_size;
	ar & mvpBackupCamPin_size;
	ar & mvpBackupCamKan_size;
	
	if(Archive::is_saving::value){
	    std::cout << "--------------is saving;--------------" << std::endl;
	    vector<Pinhole*> tmp;
	    for(auto c : mvpCameras){
		tmp.push_back((Pinhole*)c);
	    }
	    ar & tmp;
	}else{
	    std::cout << "-----------------is loading;---------------" << std::endl;
	    vector<Pinhole*> tmp;
		std::cout << "Yunshu -- atlas is loading 1" << std::endl;
	    ar & tmp;
				std::cout << "Yunshu -- atlas is loading 2" << std::endl;

	    for(auto p : tmp){
					std::cout << "Yunshu -- atlas is loading for loop" << std::endl;

		mvpCameras.push_back((GeometricCamera*) p);
	    }
	    std::cout << "loading mvpCameras size: " << mvpCameras.size() << std::endl;
	}
        ar & mvpBackupCamPin;
        ar & mvpBackupCamKan;
        // Need to save/load the static Id from Frame, KeyFrame, MapPoint and Map
        
	if(KeyFrame::nNextId_backup == 0){//only change these static variables when backup is 0; this is static value
	    ar & Map::nNextId;
            ar & Frame::nNextId;
            ar & KeyFrame::nNextId;
            ar & MapPoint::nNextId;
            ar & GeometricCamera::nNextId;
	    //updated then update reloaded keyframe index
	    KeyFrame::nNextId_backup = KeyFrame::nNextId;
	    if(KeyFrame::nNextId_backup != 0){
		//update keyframe, Frame, MapPoint, GeometricCamera mnId
		//or update in other files
		//needIndexProcess = true;
		Map::needIndexProcess = true;
		//Frame::needIndexProcess = true;
		KeyFrame::needIndexProcess = true;
		MapPoint::needIndexProcess = true;
		//GeometricCamera::needIndexProcess = true;
	    }
	}
	
        ar & mnLastInitKFidMap;
	//clock_t timeElapsed = clock() - start;
	//unsigned msElapsed = timeElapsed / (CLOCKS_PER_SEC / 1000);
	//cout << "Binary file created in " << msElapsed << " ms" << endl;
	gettimeofday(&end, NULL);
	double elapsed = ((end.tv_sec - start.tv_sec) * 1000) 
        	+ (end.tv_usec / 1000 - start.tv_usec / 1000);
	cout << "elapsed time in creating .bin file: " << elapsed << endl;
    }

public:
    Atlas();
    Atlas(int initKFid); // When its initialization the first map is created
    ~Atlas();

    void CreateNewMap();
    void ChangeMap(Map* pMap);

    unsigned long int GetLastInitKFid();

    void SetViewer(Viewer* pViewer);

    // Method for change components in the current map
    void AddKeyFrame(KeyFrame* pKF, bool skip = false);
    void AddMapPoint(MapPoint* pMP);
    //void EraseMapPoint(MapPoint* pMP);
    //void EraseKeyFrame(KeyFrame* pKF);

    void AddCamera(GeometricCamera* pCam);

    /* All methods without Map pointer work on current map */
    void SetReferenceMapPoints(const std::vector<MapPoint*> &vpMPs);
    void InformNewBigChange();
    int GetLastBigChangeIdx();

    long unsigned int MapPointsInMap();
    long unsigned KeyFramesInMap();

    // Method for get data in current map
    std::vector<KeyFrame*> GetAllKeyFrames();
    std::vector<MapPoint*> GetAllMapPoints();
    std::vector<MapPoint*> GetReferenceMapPoints();

    vector<Map*> GetAllMaps();

    int CountMaps();

    void clearMap();

    void clearAtlas();

    Map* GetCurrentMap();

    void SetMapBad(Map* pMap);
    void RemoveBadMaps();

    bool isInertial();
    void SetInertialSensor();
    void SetImuInitialized();
    bool isImuInitialized();

    // Function for garantee the correction of serialization of this object
    void PreSave();
    void PostLoad();
    void PostLoad_second();

    void SetKeyFrameDababase(KeyFrameDatabase* pKFDB);
    KeyFrameDatabase* GetKeyFrameDatabase();

    void SetORBVocabulary(ORBVocabulary* pORBVoc);
    ORBVocabulary* GetORBVocabulary();

    long unsigned int GetNumLivedKF();

    long unsigned int GetNumLivedMP();

protected:

    std::set<Map*> mspMaps;
    std::set<Map*> mspBadMaps;
    // Its necessary change the container from set to vector because libboost 1.58 and Ubuntu 16.04 have an error with this cointainer
    std::vector<Map*> mvpBackupMaps;
    Map* mpCurrentMap;

    std::vector<GeometricCamera*> mvpCameras;
    std::vector<KannalaBrandt8*> mvpBackupCamKan;
    std::vector<Pinhole*> mvpBackupCamPin;

    //Pinhole testCam;
    std::mutex mMutexAtlas;

    unsigned long int mnLastInitKFidMap;

    Viewer* mpViewer;
    bool mHasViewer;

    // Class references for the map reconstruction from the save file
    KeyFrameDatabase* mpKeyFrameDB;
    ORBVocabulary* mpORBVocabulary;
    


}; // class Atlas

} // namespace ORB_SLAM3

#endif // ATLAS_H

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

#include <pthread.h>
#include <string>

using namespace std;
int atlasReady = 1;



void LoadImages(const string &strImagePath, const string &strPathTimes,
                vector<string> &vstrImages, vector<double> &vTimeStamps);


int server(ORB_SLAM3::System *SLAM);

void *forClient(void *ptr);
void invokeSLAM(ORB_SLAM3::System *SLAM);

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


    

    // 

    // Load all sequences:
    int seq;
    vector< vector<string> > vstrImageFilenames;
    vector< vector<double> > vTimestampsCam;
    vector<int> nImages;

    vstrImageFilenames.resize(num_seq);
    vTimestampsCam.resize(num_seq);
    nImages.resize(num_seq);



    struct timeval start0, end0, loadTempStart, loadTempEnd, overallstart;

gettimeofday(&overallstart, NULL);
    int tot_images = 0;


    std::vector<std::thread> threads;
    threads.reserve(20);
    for (seq = 0; seq<num_seq; seq++)
    {
        cout << "Loading images for sequence " << seq << "...";
        gettimeofday(&start0, NULL);
        LoadImages(string(argv[(2*seq)+3]) + "/mav0/cam0/data", string(argv[(2*seq)+4]), vstrImageFilenames[seq], vTimestampsCam[seq]);
        gettimeofday(&end0, NULL);
        double elapsed = ((end0.tv_sec - start0.tv_sec) * 1000) + (end0.tv_sec / 1000 - start0.tv_sec / 1000);
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
cout << "starting server" << " ******************* " << endl;

std::thread t(&server, &SLAM);   // t starts running
//t.join();
    cout << "loaded both" << " ******************* " << endl;

  //  ORB_SLAM3::System SLAM(argv[1],argv[2],ORB_SLAM3::System::MONOCULAR, true, 0, "", "./testmap.osa");


    gettimeofday(&start0, NULL);
// //std::string strMicroSec = lexical_cast<std::string>(end0.tv_sec);
    ofstream file_out;
    file_out.open("timeseris.txt", std::ios_base::app);
    file_out << "After initiate SLAM, the first image starts at: " << start0.tv_sec * 1000000 + start0.tv_usec<< endl;

        // Main loop
    cv::Mat im;
    int proccIm = 0;
    seq = 0;
    for(int ni=0; ni<nImages[0]; ni++, proccIm++)
    {
            // *********************** Yunshu ************************************//
                        // load the binary file is the same as the buffer, so all we need is to load the binary file but not need to update the buffer because they are the same

                        cout << "ni:  " << ni << " ******************* " << endl;


   


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

            if(atlasReady == 1)
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



            //if(ni % 200 == 199 && ni > 198)
            if(ni % 150 == 149 && ni > 148)
            {


                cout << "sending the dataset" << endl;

                       // SLAM.ChangeDataset();
                // Read image from file ********** Do B

                    threads.emplace_back(&invokeSLAM, &SLAM);
                    //std::thread clientThread(&invokeSLAM, &SLAM); 
                    //clientThread.join();
                   //SLAM.client();

                   cout << "ni % 100: " << ni  % 100<< endl;


             //      SLAM.SaveAtlas_Yunshu("B" + std::to_string(ni / 100));


            }





   //     }

    }
    for (auto& t : threads)
        t.join();
    //    clientThread.join();
    // Stop all threads
    SLAM.Shutdown();

    gettimeofday(&end0, NULL);
    double elapsed = ((end0.tv_sec - start0.tv_sec) * 1000) + (end0.tv_sec / 1000 - start0.tv_sec / 1000);
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
    
    elapsed = ((end0.tv_sec - start0.tv_sec) * 1000) + (end0.tv_sec / 1000 - start0.tv_sec / 1000);
    saveTimeSeq = elapsed;
    cout << "*****************loading  time for seq1:  " << loadTimeSeq[0]  <<" ******************* " << endl;
    cout << "*****************loading  time for seq2:  " << loadTimeSeq[1]  <<" ******************* " << endl;
    cout << "*****************save  time:  " << saveTimeSeq << " ******************* " << endl;


    elapsed = ((end0.tv_sec - overallstart.tv_sec) * 1000) + (end0.tv_sec / 1000 - overallstart.tv_sec / 1000);

    return 0;
    //save ends



}


void invokeSLAM(ORB_SLAM3::System *SLAM){
    //atlasReady = 0;
    //SLAM->SaveAtlas_Yunshu("client0");
   SLAM->saveSmallAtlas(0);
   //usleep(1000000);
    //atlasReady = 1;
    // while(1){
    //     usleep(1000);
    // }
    char * s = "client0.osa";
    SLAM->client(8081, s);
    //SLAM->saveAllFiles();


    std::cout << "SLAM->client done" << std::endl;
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





















struct client {
    socklen_t client_len;
    struct sockaddr_in client_address;
    int client_sockfd;
    pthread_t thread;
    ORB_SLAM3::System *SLAM;
};




enum { PORTSIZE = 6 };




int server(ORB_SLAM3::System *SLAM)
{
    struct addrinfo hints,
    *res;
    int enable = 1;
    //int filefd;  // NOTE: this is never initialized/used
    int server_sockfd;
    //unsigned short server_port = 8080u;
    long int server_port = 8080;
    char portNum[PORTSIZE];

    // NOTE: now all client related data is malloc'ed
#if 0
    int socket_index = 0;
#else
    struct client *ctl;
#endif

    
   // server_port = strtol(server_port, NULL, 10);


    memset(&hints, 0, sizeof hints);
    hints.ai_family = AF_INET;          // ipv4
    hints.ai_socktype = SOCK_STREAM;    // tcp
    hints.ai_flags = AI_PASSIVE;        // fill in my IP for me
    
    printf(" hints.ai_flags", hints.ai_flags);

    sprintf(portNum, "%d", server_port);
    getaddrinfo(NULL, portNum, &hints, &res);

    server_sockfd = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
    if (server_sockfd == -1) {
        perror("socket");
        exit(EXIT_FAILURE);
    }

    if (setsockopt(server_sockfd, SOL_SOCKET, (SO_REUSEPORT | SO_REUSEADDR), &enable, sizeof(enable)) < 0) {
        perror("setsockopt(SO_REUSEADDR) failed");
        exit(EXIT_FAILURE);
    }

    if (bind(server_sockfd, res->ai_addr, res->ai_addrlen) == -1) {
        perror("bind");
        exit(EXIT_FAILURE);
    }

    if (listen(server_sockfd, 5) == -1) {
        perror("listen");
        exit(EXIT_FAILURE);
    }
    fprintf(stderr, "listening on port %d\n", server_port);

    // NOTE: we want the threads to run detached so we don't have to wait
    // for them to do cleanup -- the thread now does its own close/cleanup
    pthread_attr_t attr;
    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr,1);

    while (1) {
        // NOTE/BUG: using a fixed list, if you actually let threads detach,
        // you don't know which thread completes allowing its control struct
        // to be reused
        // the solution is to allocate a fresh one, fill it, pass it to the
        // thread and let the _thread_ do all the closes and cleanup
#if 0
        ctl = &control_list[socket_index];
#else
        ctl = (struct client *)malloc(sizeof(struct client));
        if (ctl == NULL) {
            perror("malloc");
            exit(EXIT_FAILURE);
        }
#endif

        ctl->client_len = sizeof(ctl->client_address);
        puts("waiting for client");

        ctl->client_sockfd = accept(server_sockfd,
            (struct sockaddr *) &ctl->client_address, &ctl->client_len);

        if (ctl->client_sockfd < 0) {
            perror("Cannot accept connection\n");
            close(server_sockfd);
            exit(EXIT_FAILURE);
        }

        ctl->SLAM = SLAM;

        // NOTE: we're running the threads detached now and we're passing down
        // extra information just in case the client loop needs it
#if 0
        pthread_create(&ctl->thread, NULL, forClient, ctl);
#else
        pthread_create(&ctl->thread, &attr, forClient, ctl);
        
#endif

#if 0
        if (BUFSIZ == socket_index) {
            socket_index = 0;
        }
        else {
            ++socket_index;
        }
#endif

        // NOTE/BUG: this is why you couldn't do multiple clients at the same
        // time -- you are doing a thread join
        // but you _had_ to because the main thread didn't know when a thread
        // was done with the control struct without the join
#if 0
        pthread_join(threads[socket_index], NULL);
        close(filefd);
        close(client_sockfd[socket_index]);
#endif
    }

    return EXIT_SUCCESS;
}

void *
forClient(void *ptr)
{

    struct client *ctl = (struct client *)ptr;
    int connect_socket = ctl->client_sockfd;

    int filefd;
    ssize_t read_return;
    char buffer[BUFSIZ];
    char *file_path;
    long long file_length;
    char receiveFileName[BUFSIZ];

    //int ret = 1;

    // Thread number means client's id
    printf("Thread number %ld\n", pthread_self());
    struct timeval start0;
    gettimeofday(&start0, NULL);
// //std::string strMicroSec = lexical_cast<std::string>(end0.tv_sec);
    ofstream file_out;
    file_out.open("timeseris.txt", std::ios_base::app);
    file_out << "client start receiving time at: " << start0.tv_sec * 1000000 + start0.tv_usec<< endl;

    // NOTE: to run parallel threads, this prevents that
#if 0
    pthread_mutex_lock(&mutex1);
#endif

    // until stop receiving go on taking information
    while (recv(connect_socket, receiveFileName, sizeof(receiveFileName), 0)) {
        // NOTE/FIX2: now we have the client send us the file length so we
        // know when to stop the read loop below
        file_length = strtoll(receiveFileName,&file_path,10);

        if (*file_path != ',') {
            fprintf(stderr,"syntax error in request -- '%s'\n",
                receiveFileName);
            exit(EXIT_FAILURE);
        }
        file_path += 1;


//char str1[] = "client";
 //          strcat (str1, file_path);
  //          file_path = str1;
        fprintf(stderr, "is the file name received? ?   =>  %s [%lld bytes]\n",
            file_path,file_length);

        // NOTE: if you want to see _why_ sending the length is necessary,
        // uncomment this line and the "unable to send two files" bug will
        // reappear
        //file_length = 1LL << 62;

cout << "file path is  " << file_path<<endl;

char str1[7 + std::strlen( file_path )] = "client";
           strcat (str1, file_path);
cout << "str1 is  " << str1 <<endl;
            //file_path = str1;
        filefd = open(str1,
            O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
        if (filefd == -1) {
            perror("open");
            exit(EXIT_FAILURE);
        }


   
        for (;  file_length > 0;  file_length -= read_return) {
            read_return = BUFSIZ;
            if (read_return > file_length)
                read_return = file_length;

            read_return = read(connect_socket, buffer, read_return);
            if (read_return == -1) {
                perror("read");
                exit(EXIT_FAILURE);
            }
            if (read_return == 0)
                break;

            if (write(filefd, buffer, read_return) == -1) {
                perror("write");
                exit(EXIT_FAILURE);
            }
            printf("read_return : %d \n", read_return);
        }

        fprintf(stderr,"file complete\n");
        gettimeofday(&start0, NULL);  
    file_out << "client finish receiving time at: " << start0.tv_sec * 1000000 + start0.tv_usec<< endl;


        atlasReady = 0;
        ctl->SLAM->setLoadMap_Yunshu(true, str1);

        atlasReady = 1;
        // NOTE/BUG: filefd was never closed
#if 1
        close(filefd);
#endif
    }

#if 0
    pthread_mutex_unlock(&mutex1);
#endif

    fprintf(stderr, "Client dropped connection\n");

    // NOTE: do all client related cleanup here
    // previously, the main thread was doing the close, which is why it had
    // to do the pthread_join
    close(connect_socket);

    
    free(ctl);




    // NOTE: this needs a void * value like below
#if 0
    pthread_exit(&ret);
#endif
    
    return (void *) 0;
}
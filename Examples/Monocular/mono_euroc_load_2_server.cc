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
int atlasReady = 0;
#define MAXFILES        1000000


void LoadImages(const string &strImagePath, const string &strPathTimes,
                vector<string> &vstrImages, vector<double> &vTimeStamps);


int server();
int toClient(int port, char * clientFileName);
void *forClient(void *ptr);
void invokeSLAM(char *  filenametosend);

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


std::thread t(&server);   // t starts running


    

    // 

    // Load all sequences:
    int seq;
    vector< vector<string> > vstrImageFilenames;
    vector< vector<double> > vTimestampsCam;
    vector<int> nImages;

    vstrImageFilenames.resize(num_seq);
    vTimestampsCam.resize(num_seq);
    nImages.resize(num_seq);



    struct timeval start0, end0, loadTempStart, loadTempEnd;


    

    // Vector for tracking time statistics
    

    cout << endl << "-------" << endl;
    cout.precision(17);


    gettimeofday(&start0, NULL);
    // Create SLAM system. It initializes all system threads and gets ready to process frames.
    ORB_SLAM3::System SLAM(argv[1],argv[2],ORB_SLAM3::System::MONOCULAR, true);
    //return 0;
    //ORB_SLAM3::System SLAM(argv[1],argv[2],ORB_SLAM3::System::MONOCULAR, true, 0, "", "./04262021_2maps.osa", "./04262021_2maps.osa");
   //ORB_SLAM3::System SLAM(argv[1],argv[2],ORB_SLAM3::System::MONOCULAR, true, 0, "", "./MH04_0909.osa", "./MH05_0909.osa" );

  // ORB_SLAM3::System SLAM(argv[1],argv[2],ORB_SLAM3::System::MONOCULAR, true, 0, "", "./tempB0.osa", "./MH05_0909.osa" );
    int counter = -1;
    while (true){
        std::cout << atlasReady << std::endl;
        if(atlasReady == 1){
            counter = counter + 2;
            string tempstring;
            std::cout << "ready to merge" << std::endl;
            //SLAM.ChangeTempMap_Yunshu("shellCommands_008.osa");

            switch(counter) {
                case 1:
                    usleep(1784704);
                    //tempstring = "MH0405-" + std::to_string(counter) + ".osa"
                    break;
                case 3:
                    usleep(1946110);
                    
                    break;
                case 5:
                    usleep(1881269);
                case 7:
                    usleep(5194529);
                case 9:
                    usleep(8241418);
                case 11:
                    usleep(11061805);
                case 13:
                    usleep(14941815);
                case 15:
                    usleep(14619219);
                case 17:
                    usleep(17080999);
                case 19:
                    usleep(16295643);
                
                default:
                usleep(1);
                    // code block
            }
            //unsigned int microsecond = 1000000;
            //usleep(3 * microsecond);//sleeps for 3 second
            atlasReady = 0;
            tempstring = "MH0405-" + std::to_string(counter) + ".osa";
            //string tempstring = "MH0405-" + std::to_string(counter + 5) + ".osa";
            char *  filenametosend = strdup(tempstring.c_str());
            
            std::thread client(&invokeSLAM, filenametosend); 
            client.join();
            
            //return 0;
        }
        //std::cout << "waiting for the client to send file" << std::endl;
    }
   /// ORB_SLAM3::System SLAM_2(argv[1],argv[2],ORB_SLAM3::System::MONOCULAR, true);
cout << "starting server" << " ******************* " << endl;

//t.join();
    cout << "loaded both" << " ******************* " << endl;

  //  ORB_SLAM3::System SLAM(argv[1],argv[2],ORB_SLAM3::System::MONOCULAR, true, 0, "", "./testmap.osa");
    SLAM.Shutdown();

    gettimeofday(&end0, NULL);
    double elapsed = ((end0.tv_sec - start0.tv_sec) * 1000) + (end0.tv_sec / 1000 - start0.tv_sec / 1000);
    cout << "*****************Second elapsed time:  " << elapsed << " ******************* " << endl;


    cout << "*****************Total elapsed time:  " << firstTime + elapsed << " ******************* " << endl;
    // Save camera trajectory

    

    return 0;
    //save ends



}


void invokeSLAM(char *  filenametosend){
    std::cout << "toClient" << std::endl;
    toClient(8080, filenametosend);

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
    
};




enum { PORTSIZE = 6 };




int server()
{
    struct addrinfo hints,
    *res;
    int enable = 1;
    //int filefd;  // NOTE: this is never initialized/used
    int server_sockfd;
    //unsigned short server_port = 8080u;
    long int server_port = 8081;
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
#if 0
    int connect_socket = (int) ptr;
#else
    struct client *ctl = (struct client *)ptr;
    int connect_socket = ctl->client_sockfd;
#endif
    int filefd;
    ssize_t read_return;
    char buffer[BUFSIZ];
    char *file_path;
    long long file_length;
    char receiveFileName[BUFSIZ];

    //int ret = 1;

    // Thread number means client's id
    printf("Thread number %ld\n", pthread_self());

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

        fprintf(stderr, "is the file name received? ?   =>  %s [%lld bytes]\n",
            file_path,file_length);

        // NOTE: if you want to see _why_ sending the length is necessary,
        // uncomment this line and the "unable to send two files" bug will
        // reappear
        //file_length = 1LL << 62;

        filefd = open(file_path,
            O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
        if (filefd == -1) {
            perror("open");
            exit(EXIT_FAILURE);
        }


   //     char *data = new char[BUFSIZ];

//	int received = recv(connect_socket, data, BUFSIZ, 0);
    //received = recv(connect_socket, data, BUFSIZ, 0);



 //   	printf("received : %d \n", received);
//printf("\n  client sent : %s \n", std::string(data));






// std::string pathSaveFileName = "./temp.osa";
//     std::remove(pathSaveFileName.c_str());






//  std::ofstream ofs(pathSaveFileName, std::ios::binary);
//              boost::archive::binary_oarchive oa(ofs);

//             oa << data;




        // NOTE/BUG2/FIX: now we only read up to what we're told to read
        // previously, we would keep trying to read, so on the _second_
        // send, our read call here would get the data that _should_ have
        // gone into the recv above
        // in other words, we'd lose synchronization with what the client
        // was sending us [and we'd put the second filename into the first
        // file as data at the bottom]
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
            //printf("read_return : %d \n", read_return);
        }

        fprintf(stderr,"file complete\n");

struct timeval start0;
gettimeofday(&start0, NULL);
    ofstream file_out;
    file_out.open("timeseris.txt", std::ios_base::app);
    file_out << "file complete\n"<<"server finish receiving time at: " << start0.tv_sec * 1000000 + start0.tv_usec<< "\n" <<endl;

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









int toClient(int port, char * clientFileName) {
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
    file_out << "server start sending time at: " << start0.tv_sec * 1000000 + start0.tv_usec<< endl;

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
                
                strcpy(file_path, clientFileName);
				

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



                 struct timeval start0;
                 gettimeofday(&start0, NULL);
                // //std::string strMicroSec = lexical_cast<std::string>(end0.tv_sec);
                 ofstream file_out;
                 file_out.open("timeseris.txt", std::ios_base::app);
                 file_out << "server finish sending time at: " << start0.tv_sec * 1000000 + start0.tv_usec << endl;
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
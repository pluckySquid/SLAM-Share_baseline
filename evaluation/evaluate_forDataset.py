# Modified by Raul Mur-Artal
# Automatically compute the optimal scale factor for monocular VO/SLAM.

# Software License Agreement (BSD License)
#
# Copyright (c) 2013, Juergen Sturm, TUM
# All rights reserved.
#
# Redistribution and use in source and binary forms, with or without
# modification, are permitted provided that the following conditions
# are met:
#
#  * Redistributions of source code must retain the above copyright
#    notice, this list of conditions and the following disclaimer.
#  * Redistributions in binary form must reproduce the above
#    copyright notice, this list of conditions and the following
#    disclaimer in the documentation and/or other materials provided
#    with the distribution.
#  * Neither the name of TUM nor the names of its
#    contributors may be used to endorse or promote products derived
#    from this software without specific prior written permission.
#
# THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
# "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
# LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
# FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
# COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
# INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
# BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
# LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
# CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
# LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
# ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
# POSSIBILITY OF SUCH DAMAGE.
#
# Requirements:
# sudo apt-get install python-argparse

"""
This script computes the absolute trajectory error from the ground truth
trajectory and the estimated trajectory.
"""

import sys
import numpy
import argparse
import associate
import os

def align(model,data):
    """Align two trajectories using the method of Horn (closed-form).
    Input:
    model -- first trajectory (3xn)
    data -- second trajectory (3xn)
    Output:
    rot -- rotation matrix (3x3)
    trans -- translation vector (3x1)
    trans_error -- translational error per point (1xn)
    """


    numpy.set_printoptions(precision=3,suppress=True)
    model_zerocentered = model - model.mean(1)
    data_zerocentered = data - data.mean(1)

    W = numpy.zeros( (3,3) )
    for column in range(model.shape[1]):
        W += numpy.outer(model_zerocentered[:,column],data_zerocentered[:,column])
    U,d,Vh = numpy.linalg.linalg.svd(W.transpose())
    S = numpy.matrix(numpy.identity( 3 ))
    if(numpy.linalg.det(U) * numpy.linalg.det(Vh)<0):
        S[2,2] = -1
    rot = U*S*Vh

    rotmodel = rot*model_zerocentered
    dots = 0.0
    norms = 0.0

    for column in range(data_zerocentered.shape[1]):
        dots += numpy.dot(data_zerocentered[:,column].transpose(),rotmodel[:,column])
        normi = numpy.linalg.norm(model_zerocentered[:,column])
        norms += normi*normi

    s = float(dots/norms)
    print('scale is ' + str(s))
    transGT = data.mean(1) - s*rot * model.mean(1)
    trans = data.mean(1) - rot * model.mean(1)

    model_alignedGT = s*rot * model + transGT
    model_aligned = rot * model + trans

    alignment_errorGT = model_alignedGT - data
    alignment_error = model_aligned - data

    trans_errorGT = numpy.sqrt(numpy.sum(numpy.multiply(alignment_errorGT,alignment_errorGT),0)).A[0]
    trans_error = numpy.sqrt(numpy.sum(numpy.multiply(alignment_error,alignment_error),0)).A[0]

    return rot,transGT,trans_errorGT,transGT,trans_errorGT, s

def plot_trajGroundTruth(left, right, ax,stamps,traj,style,color,label, markersize=12, colorchoice=False):
    """
    Plot a trajectory using matplotlib.
    Input:
    ax -- the plot
    stamps -- time stamps (1xn)
    traj -- trajectory (3xn)
    style -- line style
    color -- line color
    label -- plot legend
    """
    #MHstamps: 1403636762713555456    1403637009451666432    1403637264388318976    1403638227695097088    1403638630527829504
    #V1 stamps  1403715417812143104      1403715608412143104    1403715993034057984
    #V2 stamps: 1413393325455760384    1413394002655760384    1413394997605760512
    labelinfo = {}
    labelinfo["MH_01"] = 0
    labelinfo["MH_02"] = 0
    labelinfo["MH_03"] = 0
    labelinfo["MH_04"] = 0
    labelinfo["MH_05"] = 0
    labelinfo["ground truth"] = 0
    labelinfo[""] = 0

    labelinfo["V1_01"] = 0
    labelinfo["V1_02"] = 0
    labelinfo["V1_03"] = 0
    labelinfo["V2_01"] = 0
    labelinfo["V2_02"] = 0
    labelinfo["V2_03"] = 0

    stamps.sort()
    interval = numpy.median([s-t for s,t in zip(stamps[1:],stamps[:-1])])
    print([s-t for s,t in zip(stamps[1:],stamps[:-1])])
    print(stamps)
    print("s is : %d\n", s)
    print("t is : %d\n", t)
    print("interval is : %d\n", interval)
    x = []
    y = []
    #timestampGroundTruth = []
   # left = 0
    leftFlag = True
    #right = 0
    rightFlag = True
    last = stamps[0]
    print("statemp length is: %d\n",len(stamps))

    open_path = '/home/ucrnet/Desktop/workspace/ORBSLAM3/Yunshu_Results/' + "0920" + '/'
    file_name = "keyframes3.txt"

    if not os.path.exists(open_path):
        os.makedirs('open_path')

    file1 = open(open_path + file_name, "a")
    #left = 20
   # right = 40
    for i in range(len(stamps)):

        if True:



            x.append(traj[i][0])
            y.append(traj[i][1])


        if stamps[i]-last > 2*interval:
            print("this is the amazing timestap: %d\n", stamps[i], last)
            if colorchoice:


                    ax.plot(x,y,style,color=color,label=label if labelinfo[label] == 0 else "", markersize=markersize)




            #if label != 'ground truth' and label != "keyframe":
            ax.plot(x,y,style,color=color,label=label if label == 'ground truth' else "", markersize=markersize)
            label=""

            x=[]
            y=[]
        else:
            print("This is an exception", len(x))
        last= stamps[i]


    file1.close()
    if len(x)>0:
        ax.plot(x,y,style,color=color,label=label, markersize=markersize)
        print(len(x))

        if len(stamps)> 280:
            print(len(x))
            print(left, right)
            ax.plot(x[left:right],y[left:right],style,color="g",label=label, linewidth=3)
        print("left",left)
        print("rigth",right)



def plot_traj(ax,stamps,traj,style,color,label, markersize=12, colorchoice=False):
    """
    Plot a trajectory using matplotlib.
    Input:
    ax -- the plot
    stamps -- time stamps (1xn)
    traj -- trajectory (3xn)
    style -- line style
    color -- line color
    label -- plot legend
    """
    #MHstamps: 1403636762713555456    1403637009451666432    1403637264388318976    1403638227695097088    1403638630527829504
    #V1 stamps  1403715417812143104      1403715608412143104    1403715993034057984
    #V2 stamps: 1413393325455760384    1413394002655760384    1413394997605760512
    labelinfo = {}
    labelinfo["MH_01"] = 0
    labelinfo["MH_02"] = 0
    labelinfo["MH_03"] = 0
    labelinfo["MH_04"] = 0
    labelinfo["MH_05"] = 0
    labelinfo["ground truth"] = 0
    labelinfo[""] = 0

    labelinfo["V1_01"] = 0
    labelinfo["V1_02"] = 0
    labelinfo["V1_03"] = 0
    labelinfo["V2_01"] = 0
    labelinfo["V2_02"] = 0
    labelinfo["V2_03"] = 0

    stamps.sort()
    interval = numpy.median([s-t for s,t in zip(stamps[1:],stamps[:-1])])
    print([s-t for s,t in zip(stamps[1:],stamps[:-1])])
    print(stamps)
    print("s is : %d\n", s)
    print("t is : %d\n", t)
    print("interval is : %d\n", interval)
    x = []
    y = []
    last = stamps[0]
    print("statemp length is: %d\n",len(stamps))
    for i in range(len(stamps)):
        print("i : %d", i)
        if stamps[i]-last < 2*interval:
            x.append(traj[i][0])
            y.append(traj[i][1])
        elif len(x)>0:
            print("this is the amazing timestap: %d\n", stamps[i])
            if colorchoice:


                if last > 1403638519777829376:
                    color = 'r'
                    label = "V1_03"
                    ax.plot(x,y,style,color=color,label=label if labelinfo[label] == 0 else "", markersize=markersize)
                    labelinfo["V1_03"] = 1;


                elif last <= 1413393325455760384:
                    print("MH04")
                    color = 'blue'
                    label = "V1_01"
                    ax.plot(x,y,style,color=color,label=label if labelinfo[label] == 0 else "", markersize=markersize)
                    labelinfo["V1_01"] = 1;
                elif last <= 1413394002655760384:
                    color = 'g'
                    label = "V1_02"
                    ax.plot(x,y,style,color=color,label=label if labelinfo[label] == 0 else "", markersize=markersize)
                    labelinfo["V1_02"] = 1;
                elif last <= 1413394997605760512:
                    color = 'r'
                    label = "V1_03"
                    ax.plot(x,y,style,color=color,label=label if labelinfo[label] == 0 else "", markersize=markersize)
                    labelinfo["V1_03"] = 1;




            ax.plot(x,y,style,color=color,label=label if label == 'ground truth' else "", markersize=markersize)
            label=""
            x=[]
            y=[]
        last= stamps[i]


#    start = int(str(sys.argv[-1]).split(".pdf")[0][-1])
#    print(start)
#    end = start+20
 #   if len(stamps) <= 270:

 #       for j in range(start,end):
#            color = 'r'
 #           print("there it is")
 #           print(j)
  #          ax.plot(x[j],y[j],style,color=color,label=label if labelinfo[label] == 0 else "", markersize=20)
  #          label = "V1_03"
  #          labelinfo["V1_03"] = 3;
  #      x = []
 #       y = []

    #print("left start time stamp: ", '{:.0f}'.format(stamps[start]))
   # print("right end time stamp: ", '{:.0f}'.format(stamps[end]))


    if len(x)>0:
        ax.plot(x,y,style,color=color,label=label, markersize=markersize)

if __name__=="__main__":
    # parse command line
    parser = argparse.ArgumentParser(description='''
    This script computes the absolute trajectory error from the ground truth trajectory and the estimated trajectory.
    ''')

    parser.add_argument('first_file', help='ground truth trajectory (format: timestamp tx ty tz qx qy qz qw)')
    parser.add_argument('second_file', help='estimated trajectory (format: timestamp tx ty tz qx qy qz qw)')
    parser.add_argument('--offset', help='time offset added to the timestamps of the second file (default: 0.0)',default=0.0)
    parser.add_argument('--scale', help='scaling factor for the second trajectory (default: 1.0)',default=1.0)
    parser.add_argument('--max_difference', help='maximally allowed time difference for matching entries (default: 10000000 ns)',default=20000000)
    parser.add_argument('--save', help='save aligned second trajectory to disk (format: stamp2 x2 y2 z2)')
    parser.add_argument('--save_associations', help='save associated first and aligned second trajectory to disk (format: stamp1 x1 y1 z1 stamp2 x2 y2 z2)')
    parser.add_argument('--plot', help='plot the first and the aligned second trajectory to an image (format: png)')
    parser.add_argument('--verbose', help='print all evaluation data (otherwise, only the RMSE absolute translational error in meters after alignment will be printed)', action='store_true')
    parser.add_argument('--verbose2', help='print scale eror and RMSE absolute translational error in meters after alignment with and without scale correction', action='store_true')
    parser.add_argument('missing_range', help='missing range is a integer')
    parser.add_argument('missing_File', help='missing range file')

    args = parser.parse_args()

    first_list = associate.read_file_list(args.first_file, False)
    second_list = associate.read_file_list(args.second_file, False)

    matches = associate.associate(first_list, second_list,float(args.offset),float(args.max_difference))
    if len(matches)<2:
        sys.exit("Couldn't find matching timestamp pairs between groundtruth and estimated trajectory! Did you choose the correct sequence?")
    first_xyz = numpy.matrix([[float(value) for value in first_list[a][0:3]] for a,b in matches]).transpose()
    second_xyz = numpy.matrix([[float(value)*float(args.scale) for value in second_list[b][0:3]] for a,b in matches]).transpose()
    dictionary_items = second_list.items()
    sorted_second_list = sorted(dictionary_items)

    second_xyz_full = numpy.matrix([[float(value)*float(args.scale) for value in sorted_second_list[i][1][0:3]] for i in range(len(sorted_second_list))]).transpose() # sorted_second_list.keys()]).transpose()
    rot,transGT,trans_errorGT,trans,trans_error, scale = align(second_xyz,first_xyz)

    second_xyz_aligned = scale * rot * second_xyz + trans
    second_xyz_notscaled = rot * second_xyz + trans
    second_xyz_notscaled_full = rot * second_xyz_full + trans
    first_stamps = first_list.keys()
    first_stamps.sort()
    first_xyz_full = numpy.matrix([[float(value) for value in first_list[b][0:3]] for b in first_stamps]).transpose()

    second_stamps = second_list.keys()
    second_stamps.sort()
    #print(second_stamps[0:100])
    second_xyz_full = numpy.matrix([[float(value)*float(args.scale) for value in second_list[b][0:3]] for b in second_stamps]).transpose()
    second_xyz_full_aligned = scale * rot * second_xyz_full + trans


    missingFile = open(args.missing_File, "r")
    missingRangeString = missingFile.read()
    missingRangeLines = missingRangeString.split("\n")

    if args.verbose:
        print "compared_pose_pairs %d pairs"%(len(trans_error))

        print "absolute_translational_error.rmse %f m"%numpy.sqrt(numpy.dot(trans_error,trans_error) / len(trans_error))
        print "absolute_translational_error.mean %f m"%numpy.mean(trans_error)
        print "absolute_translational_error.median %f m"%numpy.median(trans_error)
        print "absolute_translational_error.std %f m"%numpy.std(trans_error)
        print "absolute_translational_error.min %f m"%numpy.min(trans_error)
        print "absolute_translational_error.max %f m"%numpy.max(trans_error)
        print "max idx: %i" %numpy.argmax(trans_error)
    else:
        # print "%f, %f " % (numpy.sqrt(numpy.dot(trans_error,trans_error) / len(trans_error)),  scale)
        # print "%f,%f" % (numpy.sqrt(numpy.dot(trans_error,trans_error) / len(trans_error)),  scale)
        print "%f,%f,%f" % (numpy.sqrt(numpy.dot(trans_error,trans_error) / len(trans_error)), scale, numpy.sqrt(numpy.dot(trans_errorGT,trans_errorGT) / len(trans_errorGT)))
        # print "%f" % len(trans_error)
    if args.verbose2:
        print "compared_pose_pairs %d pairs"%(len(trans_error))
        print "absolute_translational_error.rmse %f m"%numpy.sqrt(numpy.dot(trans_error,trans_error) / len(trans_error))
        print "absolute_translational_errorGT.rmse %f m"%numpy.sqrt(numpy.dot(trans_errorGT,trans_errorGT) / len(trans_errorGT))

    if args.save_associations:
        file = open(args.save_associations,"w")
        file.write("\n".join(["%f %f %f %f %f %f %f %f"%(a,x1,y1,z1,b,x2,y2,z2) for (a,b),(x1,y1,z1),(x2,y2,z2) in zip(matches,first_xyz.transpose().A,second_xyz_aligned.transpose().A)]))
        file.close()

    if args.save:
        file = open(args.save,"w")
        file.write("\n".join(["%f "%stamp+" ".join(["%f"%d for d in line]) for stamp,line in zip(second_stamps,second_xyz_notscaled_full.transpose().A)]))
        file.close()

    if args.plot:
        import matplotlib
        matplotlib.use('Agg')
        import matplotlib.pyplot as plt
        import matplotlib.pylab as pylab
        from matplotlib.patches import Ellipse
        fig = plt.figure()
        ax = fig.add_subplot(111)
        deletingRange = int(args.missing_range)


        plot_trajGroundTruth(missingRangeLines[deletingRange].split(', ')[0], missingRangeLines[deletingRange].split(', ')[1], ax,first_stamps,first_xyz_full.transpose().A,'-',"black","ground truth", 1, colorchoice = False)
        plot_traj(ax,second_stamps,second_xyz_full_aligned.transpose().A,'.',"blue","keyframe", 3, colorchoice=True)

        print "absolute_translational_error.rmse %f m"%numpy.sqrt(numpy.dot(trans_error,trans_error) / len(trans_error))
        label="difference"
        #for (a,b),(x1,y1,z1),(x2,y2,z2) in zip(matches,first_xyz.transpose().A,second_xyz_aligned.transpose().A):
            #ax.plot([x1,x2],[y1,y2],'-',color="red",label=label)
            #label=""

        ax.legend()

        ax.set_xlabel('x [m]')
        ax.set_ylabel('y [m]')
        plt.axis('equal')
        plt.savefig(args.plot,format="pdf")
        plt.show()
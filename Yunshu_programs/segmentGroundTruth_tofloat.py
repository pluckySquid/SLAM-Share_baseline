import os
import sys
import numpy


if __name__=="__main__":

    #interval = int(sys.argv[2])
    #print(sys.argv[sys.argc-1])


    timeStampFile_path = '/home/ucrnet/Desktop/workspace/ORBSLAM3/evaluation/Ground_truth/dataset/poses/'


    resultSava_path = '/home/ucrnet/Desktop/workspace/ORBSLAM3/Ground_truth/dataset/xyzGroundTruth_tofloat/'
    if not os.path.exists(resultSava_path):
        os.makedirs(resultSava_path)
    #resultSava_fileName = "00.txt"

    files = sorted(os.listdir(timeStampFile_path))

    #interval = 50

    #write the resulting files
    for file in files:

        resultSava_file = open(resultSava_path + file, "w+")
        timeStampFile = open(timeStampFile_path+file, "r")
        timeStampFileString = timeStampFile.read()
        timeStampFileLines = timeStampFileString.split("\n")
        timeStampFileLines = filter(None, timeStampFileLines)
        #stamp are the starting and ending stamp in the sourceFile [stamp[0], stamp[1]]
        for i in range(0, len(timeStampFileLines)):
            R = numpy.array([[float('{:.9f}'.format(float(timeStampFileLines[i].split(" ")[0]))), float('{:.9f}'.format(float(timeStampFileLines[i].split(" ")[1]))), float('{:.9f}'.format(float(timeStampFileLines[i].split(" ")[2])))],
            [float('{:.9f}'.format(float(timeStampFileLines[i].split(" ")[4]))), float('{:.9f}'.format(float(timeStampFileLines[i].split(" ")[5]))), float('{:.9f}'.format(float(timeStampFileLines[i].split(" ")[6])))],
            [float('{:.9f}'.format(float(timeStampFileLines[i].split(" ")[8]))), float('{:.9f}'.format(float(timeStampFileLines[i].split(" ")[9]))), float('{:.9f}'.format(float(timeStampFileLines[i].split(" ")[10])))]])

            Tx = float('{:.9f}'.format(float(timeStampFileLines[i].split(" ")[3])))
            Ty = float('{:.9f}'.format(float(timeStampFileLines[i].split(" ")[7])))
            Tz = float('{:.9f}'.format(float(timeStampFileLines[i].split(" ")[11])))
            T = numpy.array([Tx, Ty, Tz])

            print(type(Tz))
            print(R)
            print(str('{:.9f}'.format((float(Tx)))) + " " + str('{:.9f}'.format((float(Ty)))) + " " + str('{:.9f}'.format((float(Tz)))))
            print(numpy.matmul(R.transpose(), T))
            x, y, z = numpy.negative(numpy.matmul(R.transpose(), T) )
            print(x , y , z)
            resultSava_file.write(str(i).zfill(6) + " " + str(Tx) + " " + str(Ty) + " " + str(Tz) + "\n")





        resultSava_file.close()
        timeStampFile.close()

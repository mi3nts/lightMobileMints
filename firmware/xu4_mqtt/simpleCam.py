from datetime import timezone
import time
import os
import datetime
import numpy as np
import pickle
from skimage import io, color
import matplotlib.pyplot as plt
import matplotlib.image as mpimg
import matplotlib.colors as mpclr
from collections import OrderedDict

#from mintsXU4 import mintsSkyCamReader as mSCR
from mintsXU4 import mintsSensorReader as mSR
from mintsXU4 import mintsDefinitions as mD


dataFolder = mD.dataFolder


def main():

    sensorName = "MCAM"
    dateTimeNow = datetime.datetime.now()
    path   = mSR.getWritePathSnaps(sensorName,dateTimeNow)
    mSR.directoryCheck(path)
    print(path)
    onboardCapture = True

#    try:
    os.system("fswebcam -r 1280x720 --no-banner " + path)
    img = mpimg.imread(path,0)
    MCAMWrite(img,path,dateTimeNow)   
 #   except:
 #       print("TRY AGAIN")

def MCAMWrite(inputImage,imagePath,dateTime):
    inputImage_RGB = inputImage
    inputImage_HSV = mpclr.rgb_to_hsv(inputImage)
    RGB_for_LAB = io.imread(imagePath)
    inputImage_LAB = color.rgb2lab(RGB_for_LAB)

    Image_Array_RGB = np.array(inputImage_RGB)
    Image_Array_HSV = np.array(inputImage_HSV)
    Image_Array_LAB = np.array(inputImage_LAB)

    # Record the original shape
    Image_Shape = Image_Array_RGB.shape

    # Make a 1-dimensional view of arrays

    One_D_Image_Red   = np.transpose(np.matrix(Image_Array_RGB[:, :, 0].ravel()))
    One_D_Image_Green = np.transpose(np.matrix(Image_Array_RGB[:, :, 1].ravel()))
    One_D_Image_Blue  = np.transpose(np.matrix(Image_Array_RGB[:, :, 2].ravel()))

    # Recasting to support negative integers

    One_D_Image_Red   = One_D_Image_Red.astype(np.int16)
    One_D_Image_Green = One_D_Image_Green.astype(np.int16)
    One_D_Image_Blue  = One_D_Image_Blue.astype(np.int16)

    One_D_Image_H = np.transpose(np.matrix(Image_Array_HSV[:, :, 0].ravel()))
    One_D_Image_S = np.transpose(np.matrix(Image_Array_HSV[:, :, 1].ravel()))
    One_D_Image_V = np.transpose(np.matrix(Image_Array_HSV[:, :, 2].ravel()))

    One_D_Image_L = np.transpose(np.matrix(Image_Array_LAB[:, :, 0].ravel()))
    One_D_Image_A = np.transpose(np.matrix(Image_Array_LAB[:, :, 1].ravel()))
    One_D_Image_B = np.transpose(np.matrix(Image_Array_LAB[:, :, 2].ravel()))

    sensorDictionary = OrderedDict([
                ("dateTime"        ,str(dateTime)),
                ("redAvg"          ,np.sum(One_D_Image_Red)/len(One_D_Image_Red)),
                ("greenAvg"        ,np.sum(One_D_Image_Green)/len(One_D_Image_Red)),
                ("blueAvg"         ,np.sum(One_D_Image_Blue)/len(One_D_Image_Red)),
      			("hueAvg"          ,np.sum(One_D_Image_H)/len(One_D_Image_Red)),
                ("saturationAvg"   ,np.sum(One_D_Image_S)/len(One_D_Image_Red)),
                ("valueAvg"        ,np.sum(One_D_Image_V)/len(One_D_Image_Red)),
      			("l_Avg"           ,np.sum(One_D_Image_L)/len(One_D_Image_Red)),
                ("a_Avg"           ,np.sum(One_D_Image_A)/len(One_D_Image_Red)),
                ("b_Avg"           ,np.sum(One_D_Image_B)/len(One_D_Image_Red)),
        	     ])
    mSR.sensorFinisher(dateTime,"MCAM",sensorDictionary)
    

if __name__ == "__main__":
   main()
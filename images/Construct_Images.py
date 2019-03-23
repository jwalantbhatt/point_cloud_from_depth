# jjjdk - brokflow - Jwalant Bhatt
# Script to create images, from text file, with depth information, in string with scientific notation


# imports
import numpy as np 
import cv2
import os


# set path
img_path = os.getcwd()  								  # change this 


# load text image files to numpy array
for tifiles in os.listdir(img_path):
	if tifiles[-3:] == 'txt':
		string = img_path + "/" + tifiles  
		img_array = np.loadtxt(string)
		img_array[img_array < 2] = 5                      # assuming there are no obstacles before 2m
		img_array[img_array > 5] = 5                      # thresholding max distance at 5  
		small_array = img_array                   
		#small_array = img_array[32:102]				  # only considering the human in the view
		small_array *= float(51) 						  # scale to 255
		print(small_array.shape[0])
		cv2.imwrite( tifiles[:-4] + '.jpg', small_array)  # save images
						
        


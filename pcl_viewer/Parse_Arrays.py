# jjjdk - brokflow - Jwalant Bhatt
# Script to create images, from text file, with depth information, in string with scientific notation


# imports
import numpy as np 
import os

img_array = np.loadtxt('human_corridor_0.txt')
img_array *= float(51)
img_array[img_array > 255] = 255
np.savetxt('wsn0.txt', img_array, fmt='%.4f')







# Jwalant Bhatt.
# Script to find the clearance distance between the person(obstacle) and the corridor.


#######################################################################################


# imports
import numpy as np 
from math import cos, sin, tan, radians
import sys


# load file in numpy array
filename = sys.argv[1]
img_array = np.loadtxt(filename)


# find per pixel angle (not considering lense distortion)
hfov = float(70)/176
vfov = float(50)/132
                                

# considering the human in the view and creating a copy                   
obs_array = img_array[32:102]					  
d_array = obs_array
obs_array = img_array[32:102]
dist_x = float(1.6)*cos(radians(55))                                     # approximating distnce of the corridor


# list of clearance at each height 
verti_clearance = []


# compute lateral distances between 2 points and get the cordinates
for i in range(70):

	hori_array = d_array[i]
	hori_xpos = []
	hori_fdis = []

	for j in range(176):

		depth = hori_array[j]
		if depth < 4:
			ang_x = float(j)*hfov
			ang_y = float(i + 32)*vfov
			trig_v = sin(radians(65 + ang_y))                                  # for vertical angle
			if (j < 88):													   # for horizontal angle
				dist = max(dist_x - depth*cos(radians(55 + ang_x))*trig_v, 0)  
			else:
				dist = min(dist_x + depth*cos(radians(125 - ang_x))*trig_v, 2*dist_x)
			hori_fdis.append(dist)
			hori_xpos.append(j)
			
	clearance_array = [q-p for p, q in zip(hori_fdis[:-1], hori_fdis[1:])]     # difference of lateral distances
	max_clearance = np.amax(clearance_array)                                   # find the maximum clearance on either side
	index = clearance_array.index(max_clearance)                               
	pos1 = hori_xpos[index]
	pos2 = hori_xpos[index + 1]
	verti_clearance.append([max_clearance, pos1, pos2])

# get the index of the min value of the clearance at each height
pos_x_1 = verti_clearance[np.argmin(verti_clearance,axis =0)[0]][1]
pos_x_2 = verti_clearance[np.argmin(verti_clearance,axis =0)[0]][2]
f_dist = verti_clearance[np.argmin(verti_clearance,axis =0)[0]][0]


# determine heading and distance from corridor
if((pos_x_1 + pos_x_2)/2 < 88):                          
	head = "left"
else:
	head = "right"


# print the final result
print(head +" "+ "%0.2f" %f_dist)


# Several assumptions for solving this system:
# 	1. the camera on the robot is exactly at the center from top/botton and right/left 
#   2. the vanishing point of the view is assumed at the center of the image
#   3. there is no obstacle except human which is at 2m approx always 
#   4. the camera is mounted and aligned perfectly on the bot
#   5. the orientation of the cam or the bot doesnt change in different images


######################################################################################
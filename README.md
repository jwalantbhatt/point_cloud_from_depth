# point_cloud_from_depth
Creates point cloud (pcl) from depth image stored in a text file

For point cloud go to directory pcl

![Alt text](/img.png?raw=true "Title")


For finding clearance

Goal: Avoid human present in the corridor.

Assumptions:
1. The only obstacle is human which is at 2m approximately always.
2. The camera is mounted and aligned perfectly on the bot.
3. The orientation of the cam or the bot does not change.
4. The camera on the robot is exactly at the center from all sides.
5. The vanishing point of image is assumed at the center. (3+4)
6. The height of the robot covers entire length of the human.
7. This allows me to check for distance only in specific area.

Approach:
1. Load the file in array.
2. Threshold at 4 meters.
3. Only consider the area where human is present.
4. Iterate through array and find lateral distances between all points.
5. Get maximum clearance (lateral distance) for each height.
6. Find minimum clearance amongst different heights.
7. This way one can stay safe assuming worst case.
8. Get the positions of pixels corresponding the final clearance we got in step 6 and return distance and the heading.


Modules used numpy, sys and math

python3 find_clearance.py ./human_corridor_0.txt
Output: left 0.94

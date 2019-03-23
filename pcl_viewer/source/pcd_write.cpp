// Jwalant Bhatt
// Percpetion System Brain Test
// Modified from PCL tutorials

#include <iostream>
#include <pcl/io/pcd_io.h>
#include <pcl/point_types.h>
#include <boost/thread/thread.hpp>
#include <pcl/common/common_headers.h>
#include <pcl/features/normal_3d.h>
#include <pcl/io/pcd_io.h>
#include <pcl/visualization/pcl_visualizer.h>
#include <pcl/console/parse.h>
#include <fstream>
#include <sstream>
#include <string>
using namespace std;

// Stream file
ifstream input("wsn0.txt");


// String vector
vector<string> split(string str, char delimiter) {
  vector<string> internal;
  stringstream ss(str); // Turn the string into a stream.
  string tok;

  while (getline(ss, tok, delimiter)) {
    internal.push_back(tok);
  }

  return internal;
}

// Keyboard event
unsigned int text_id = 0;
void keyboardEventOccurred (const pcl::visualization::KeyboardEvent &event,
                            void* viewer_void)
{
  pcl::visualization::PCLVisualizer *viewer = static_cast<pcl::visualization::PCLVisualizer *> (viewer_void);
  if (event.getKeySym () == "r" && event.keyDown ())
  {
    std::cout << "r was pressed => removing all text" << std::endl;

    char str[512];
    for (unsigned int i = 0; i < text_id; ++i)
    {
      sprintf (str, "text#%03d", i);
      viewer->removeShape (str);
    }
    text_id = 0;
  }
}

// Mouse event
void mouseEventOccurred (const pcl::visualization::MouseEvent &event,
                         void* viewer_void)
{
  pcl::visualization::PCLVisualizer *viewer = static_cast<pcl::visualization::PCLVisualizer *> (viewer_void);
  if (event.getButton () == pcl::visualization::MouseEvent::LeftButton &&
      event.getType () == pcl::visualization::MouseEvent::MouseButtonRelease)
  {
    std::cout << "Left mouse button released at position (" << event.getX () << ", " << event.getY () << ")" << std::endl;

    char str[512];
    sprintf (str, "text#%03d", text_id ++);
    viewer->addText ("clicked here", event.getX (), event.getY (), str);
  }
}


int main (int argc, char** argv)
{
  int i = 0;
  int j = 0;
  string line;
  float dtpa[132][176];
  for (string line; getline(input, line); )
  {
    istringstream iss(line);

      vector<string> sep = split(line, ' ');
      for (int i = 0; i < sep.size(); ++i)
      {   
        dtpa[j][i] = stof(sep[i]);
        printf("%f\n", dtpa[j][i]);
      }
    
      ++j;
  }

  pcl::PointCloud<pcl::PointXYZ>::Ptr basic_cloud_ptr (new pcl::PointCloud<pcl::PointXYZ>);
  
  for (int xi = 0; xi < 176; xi++)
  {
    for (int yj = 132; yj > 0; yj--)
    {
      pcl::PointXYZ basic_point;
      basic_point.x = (float)xi/10;
      basic_point.y = (float)yj/10;
      basic_point.z = dtpa[yj][xi]/10;
      basic_cloud_ptr->points.push_back(basic_point);
    }
  }

      
  
  basic_cloud_ptr->width = (int) basic_cloud_ptr->points.size ();
  basic_cloud_ptr->height = 1;

  pcl::PointCloud<pcl::PointXYZ> cloud;
  cloud = *basic_cloud_ptr;


  pcl::io::savePCDFileASCII ("human_corr0.pcd", cloud);

  pcl::visualization::PCLVisualizer::Ptr viewer (new pcl::visualization::PCLVisualizer ("3D Viewer"));
  viewer->setBackgroundColor (0, 0, 0);
  viewer->addPointCloud<pcl::PointXYZ> (basic_cloud_ptr, "3d point cloud");
  viewer->setPointCloudRenderingProperties (pcl::visualization::PCL_VISUALIZER_POINT_SIZE, 1, "3d point cloud");
  viewer->addCoordinateSystem (1.0);
  viewer->initCameraParameters ();

  // Viewer loop
  while (!viewer->wasStopped ())
  {
    viewer->spinOnce (100);
    boost::this_thread::sleep (boost::posix_time::microseconds (100000));
  }

}
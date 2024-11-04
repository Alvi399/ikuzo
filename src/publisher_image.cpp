#include <ros/ros.h>
#include "cv_bridge/cv_bridge.h"
#include "image_transport/image_transport.h"
#include "std_msgs/Header.h"
#include "sensor_msgs/image_encodings.h"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"

static const std::string IMAGE_PATH = "../img/images.jpeg";
using namespace std;
int publishImage (string filepath) {
    cv::Mat image;
    image = cv::imread(filepath, CV_LOAD_IMAGE_COLOR);
    cout << "Path:  " << filepath << endl;
    if(!image.data) {
        cout << "invalid image, could not open the image" << endl;
    }
    ros::NodeHandle nh_;
    image_transport::ImageTransport it_(nh_);
    image_transport::Publisher pub = it_.advertise("camera/rgb/image",1);
    sensor_msgs::ImagePtr msg = cv_bridge::CvImage(std_msgs::Header(), "bgr8", image).toImageMsg();
    ros::Rate loop_rate(5);

    while (nh_.ok())
    {
        pub.publish(msg);
        ros::spinOnce();
        loop_rate.sleep();
    }
    
}

int main (int argc, char ** argv) {
    ros::init(argc,argv,"publisher_image");
    publishImage(IMAGE_PATH);
    return 0;
}

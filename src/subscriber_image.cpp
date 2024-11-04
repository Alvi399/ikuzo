#include <ros/ros.h>
#include <image_transport/image_transport.h>
#include <highgui/highgui.hpp>
#include <cv_bridge/cv_bridge.h>

using namespace std;
void imageCallback(const sensor_msgs::ImageConstPtr& msg) {
    try
    {
        cv_bridge::CvImagePtr cv_ptr = cv_bridge::toCvCopy(msg,"bgr8");
        cv::imwrite("rgb.bmp",cv_ptr->image);
        cv::imshow("view", cv_bridge::toCvShare(msg, "bgr8")->image);
        cv::waitKey(30);
    } catch(cv_bridge::Exception &e) {
        ROS_ERROR("could not convert %s to  'bgr8'.", msg->encoding.c_str());
    }
    
}
int main(int argc, char **argv)
{
    ros::init(argc, argv,"subscriber_image");
    ros::NodeHandle nh_;
    cv::namedWindow("view");
    cv::startWindowThread();
    image_transport::ImageTransport it_(nh_);
    image_transport::Subscriber sub = it_.subscribe("camera/rgb/image",1,imageCallback);
    ros::spin();
    cv::destroyWindow("view");
    ros::shutdown();
    return 0;
}

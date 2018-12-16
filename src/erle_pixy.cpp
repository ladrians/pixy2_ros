#include "ros/ros.h"

#include <sensor_msgs/fill_image.h>
#include <image_transport/image_transport.h>

#include <sstream>

#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

#include <boost/thread.hpp>

#include "pixycam.h"


int main(int argc, char **argv)
{

    int frame_rate = 10; // default value

    ros::init(argc, argv, "~");
    ros::NodeHandle n;

    n.param("/pixy_cam/frame_rate", frame_rate, frame_rate);

    ROS_INFO("Read Parameters");
    ROS_INFO(" frame_rate: %d", frame_rate);

    image_transport::Publisher image_pub;

    image_transport::ImageTransport it(n);
    image_pub = it.advertise("image_raw", 1);

    sensor_msgs::Image img_;

    ros::Rate loop_rate(frame_rate);

    PixyCam cam;
    boost::thread workerThread(&PixyCam::run, &cam);
//    cam.run();

    int count = 0;
    while (ros::ok()){

        cv::Mat frame = cam.getImage();
        fillImage(img_, "bgr8", frame.rows, frame.cols, frame.channels() * frame.cols, frame.data);

        image_pub.publish(img_);
        ros::spinOnce();

        loop_rate.sleep();
        ++count;
    }

    return 0;
}


#include <ros/ros.h>
#include <image_transport/image_transport.h>
#include <opencv2/highgui/highgui.hpp>
#include <cv_bridge/cv_bridge.h>
#include <sstream>

#include <iostream>

int main( int argc, char** argv )
{

    ros::init( argc, argv, "image_publisher" );
    ros::NodeHandle _nh;

    image_transport::ImageTransport _it( _nh );
    image_transport::Publisher _pub = _it.advertise( "camera/image_raw", 1 );

    cv::VideoCapture _capture( 1 );

    if ( !_capture.isOpened() )
    {
        std::cout << "error opening camera" << std::endl;
        return -1;
    }

    ros::Rate _loopRate( 30 );

    while ( _nh.ok() )
    {
        cv::Mat _frame;
        sensor_msgs::ImagePtr _imgMsg;

        _capture.read( _frame );

        // std::cout << "????" << std::endl;

        if ( !_frame.empty() )
        {
            // std::cout << "sent image" << std::endl;
            _imgMsg = cv_bridge::CvImage( std_msgs::Header(), "bgr8", _frame ).toImageMsg();
            _pub.publish( _imgMsg );
            cv::waitKey( 1 );
        }

        ros::spinOnce();
        _loopRate.sleep();
    }


    return 0;

}
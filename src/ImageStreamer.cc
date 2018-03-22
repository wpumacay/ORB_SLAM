
#include <ros/ros.h>
#include <image_transport/image_transport.h>
#include <opencv2/highgui/highgui.hpp>
#include <cv_bridge/cv_bridge.h>

#include <DataSetTUM.h>

using namespace std;

int main( int argc, char** argv )
{

    ros::init( argc, argv, "image_publisher" );
    ros::NodeHandle _nh;

    image_transport::ImageTransport _it( _nh );
    image_transport::Publisher _pub = _it.advertise( "camera/image_raw", 1 );

    vector< cv::Mat > _frames;

    string _datasetPath;
    _datasetPath += RESOURCES_PATH;
    // _datasetPath += "TUM/rgbd_dataset_freiburg3_walking_halfsphere/";
    _datasetPath += "TUM/rgbd_dataset_freiburg2_desk/";

    if( !orbslam::dataset::TUM::loadImages( _datasetPath, 
                                            _frames, 
                                            false ) )
    {
        cout << "Couldn't load dataset" << endl;
        return 0;
    }

    ros::Rate _loopRate( 30 );
    int _index = 0;

    while ( _nh.ok() )
    {
        sensor_msgs::ImagePtr _imgMsg;

        cv::Mat _frame = _frames[_index];

        _index = ( _index + 1 ) % _frames.size();

        if ( !_frame.empty() )
        {
            _imgMsg = cv_bridge::CvImage( std_msgs::Header(), "bgr8", _frame ).toImageMsg();
            //_imgMsg = cv_bridge::CvImage( std_msgs::Header(), "mono8", _frame ).toImageMsg();
            _pub.publish( _imgMsg );
        }

        ros::spinOnce();
        _loopRate.sleep();
    }


    return 0;

}

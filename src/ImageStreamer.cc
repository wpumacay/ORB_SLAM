
#include <ros/ros.h>
#include <image_transport/image_transport.h>
#include <opencv2/highgui/highgui.hpp>
#include <cv_bridge/cv_bridge.h>

#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <fstream>

#define RES_PATH "../res/kitti_data/image_0"
#define TXT_TUM_PATH "../res/TUM/rgbd_dataset_freiburg3_walking_halsfshpere"
#define RES_TUM_PATH "../res/TUM/"
//#define NUM_IMAGES 114
#define NUM_IMAGES 631


bool initializeTUMdataset( std::vector< std::string >& imagePaths, std::string txtImagesList )
{
    std::ifstream _fHandle( txtImagesList.c_str() );
    std::string _line, _path;

    if( !myfile.is_open() )
    {
        cout << "File " << txtImagesList << " cannot be opened\n";

        return false;
    }
    while( getline( _fHandle, _line ) )
    {
        if( _linene.substr( 0, _line.find(' ') == "#" ) )
        {
            continue;
        }

        _path = _line.substr( 1, _line.find(' ') );
        imagePaths.push_back( RES_TUM_PATH + _path );
    }

    _fHandle.close();

    return true;
}

std::string getImageName( int indx, int sz )
{
    std::stringstream _ss;
    std::string _stringVal;

    _ss << std::setfill( '0' ) << std::setw( sz ) << indx;
    _ss >> _stringVal;

    _stringVal = _stringVal + ".png";

    return _stringVal;
}

bool kittiDatasetLoader( std::vector< std::string >& imagePaths, int numImages )
{
    for( int i = 0; i < numImages; i++ )
    {
        imagePaths.push_back( RES_PATH + getImageName( i, 6 ) );
    }
    return true;
}


int main( int argc, char** argv )
{

    ros::init( argc, argv, "image_publisher" );
    ros::NodeHandle _nh;

    image_transport::ImageTransport _it( _nh );
    image_transport::Publisher _pub = _it.advertise( "camera/image_raw", 1 );
    cv::Mat _frame;

    std::vector< std::string > _imagePaths;
    /*if( !initializeTUMdataset( _imagePaths, TXT_TUM_PATH ) )
    {
        return 0;
    }*/

    if( !kittiDatasetLoader( _imagePaths, NUM_IMAGES  ) )
    {
        return 0;
    }

    ros::Rate _loopRate( 15 );
    int _index = 0;
    int _numImages = int( _imagePaths.size() );


    while ( _nh.ok() )
    {
        //std::string _imgName = getImageName( _index );
        std::string _imgName = _imagePaths[ _index ];

        _index = ( _index + 1 ) % _numImages;

        sensor_msgs::ImagePtr _imgMsg;

        _frame = cv::imread( _imgName );

        if ( !_frame.empty() )
        {
            _imgMsg = cv_bridge::CvImage( std_msgs::Header(), "bgr8", _frame ).toImageMsg();
            _pub.publish( _imgMsg );
            cv::waitKey( 1 );
        }

        ros::spinOnce();
        _loopRate.sleep();
    }


    return 0;

}

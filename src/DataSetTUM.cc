
#include <DataSetTUM.h>

using namespace std;

namespace orbslam { namespace dataset { namespace TUM {

	bool loadGroundTruthPoses( string sequenceResourcesPath, 
	                           vector< Pose >& poses )
	{
	    // Just in case
	    poses.clear();

        string _groundtruth_txt_path = sequenceResourcesPath + TUM_DATASET_GROUND_TRUTH_TXT_FILE;

	    std::ifstream _fHandle( _groundtruth_txt_path.c_str() );

        if ( !_fHandle.is_open() )
        {
            cout << "Error reading the groundTruthFile: " << _groundtruth_txt_path << endl;
            return false;
        }

        string _line;
        vector< string > _splits;

        while ( getline( _fHandle, _line ) )
        {
            if ( _line[0] == '#' )
            {
                continue;
            }

            splitString( _line, _splits, ' ' );

            Pose _pose;

            _pose.position[0] = atof( _splits[1].c_str() );
            _pose.position[1] = atof( _splits[2].c_str() );
            _pose.position[2] = atof( _splits[3].c_str() );

            _pose.orientation[0] = atof( _splits[4].c_str() );
            _pose.orientation[1] = atof( _splits[5].c_str() );
            _pose.orientation[2] = atof( _splits[6].c_str() );
            _pose.orientation[3] = atof( _splits[7].c_str() );

            poses.push_back( _pose );
        }

	    _fHandle.close();

        return true;
	}

    bool loadImages( string sequenceResourcesPath,
                     vector< cv::Mat >& cvImages,
                     bool isGrayscale )
    {
        // Just in case
        cvImages.clear();

        string _rgb_txt_path = sequenceResourcesPath + TUM_DATASET_IMAGES_TXT_FILE;

        std::ifstream _fHandle( _rgb_txt_path.c_str() );

        if ( !_fHandle.is_open() )
        {
            cout << "Error reading the rgbResFile: " << _rgb_txt_path << endl;
            return false;
        }

        string _line;
        vector< string > _splits;

        while ( getline( _fHandle, _line ) )
        {

            if ( _line[0] == '#' )
            {
                continue;
            }

            splitString( _line, _splits, ' ' );

            string _imagePath = sequenceResourcesPath + _splits[1];

            if ( isGrayscale )
            {
                cvImages.push_back( cv::imread( _imagePath, CV_LOAD_IMAGE_GRAYSCALE ) );
            }
            else
            {
                cvImages.push_back( cv::imread( _imagePath ) );
            }
        }

        _fHandle.close();

        return true;
    }

}}}
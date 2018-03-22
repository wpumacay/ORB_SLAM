
#pragma once

#include <Common.h>

using namespace std;

#define TUM_DATASET_IMAGES_TXT_FILE "rgb.txt"
#define TUM_DATASET_GROUND_TRUTH_TXT_FILE "groundtruth.txt"

namespace orbslam { namespace dataset { namespace TUM {


	bool loadGroundTruthPoses( string sequenceResourcesPath,
	                           vector< Pose >& poses );

    bool loadImages( string sequenceResourcesPath,
                     vector< cv::Mat >& cvImages,
                     bool isGrayscale );

}}}

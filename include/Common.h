
#pragma once

#include <vector>
#include <string>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <opencv2/opencv.hpp>

#ifndef RESOURCES_PATH
	#define RESOURCES_PATH "../res"
#endif

using namespace std;

namespace orbslam
{

	struct Pose
	{
	    float position[3];
	    float orientation[4];
	};


    void splitString( const string& txt, 
                      vector<string>& strSplits, 
                      char separator = ' ' );

}
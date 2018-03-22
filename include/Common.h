
#pragma once

#include <vector>
#include <string>
#include <fstream>
#include <iostream>

#ifndef RESOURCES_PATH
	#define RESOURCES_PATH "../res"
#endif

namespace orbslam
{

	struct Pose
	{
	    float position[3];
	    float orientation[4];
	};


    vector<string> splitString( const string& txt, char separator = ' ' );

}
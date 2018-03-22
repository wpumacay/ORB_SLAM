
#include <DataSetTUM.h>

using namespace std;

namespace orbslam { namespace dataset { namespace TUM {

	void loadGroundTruthPoses( string grounTruthFile, 
	                           vector< Pose >& poses )
	{
	    // Just in case
	    poses.clear();

	    std::ifstream _fHandle( grounTruthFile.c_str() );




	    _fHandle.close();

	}

}}}
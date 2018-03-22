
#include <Common.h>

using namespace std;

namespace orbslam
{

    void splitString( const string& txt, 
                      vector<string>& strSplits, 
                      char separator )
    {
        // Just in case
        strSplits.clear();
                    
        int pos = txt.find( separator );
        if ( pos == std::string::npos )
        {
            strSplits.push_back( txt );
        }

        int initpos = 0;

        while ( pos != std::string::npos )
        {
            strSplits.push_back( txt.substr( initpos, pos - initpos ) );
            initpos = pos + 1;

            pos = txt.find( separator, initpos );
        }

        strSplits.push_back( txt.substr( initpos, std::min( pos, (int) txt.size() ) - initpos ) );
	}

}
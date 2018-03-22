
#include <Common.h>

using namespace std;

namespace orbslam
{




    vector<string> splitString( const string& txt, char separator )
    {
        vector<string> _res;
                    
        int pos = txt.find( separator );
        if ( pos == std::string::npos )
        {
            _res.push_back( txt );
            return _res;
        }

        int initpos = 0;

        while ( pos != std::string::npos )
        {
            _res.push_back( txt.substr( initpos, pos - initpos ) );
            initpos = pos + 1;

            pos = txt.find( separator, initpos );
        }

        _res.push_back( txt.substr( initpos, std::min( pos, (int) txt.size() ) - initpos ) );
                    
        return _res;
	}

}
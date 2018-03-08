// range.cpp: implementation of the range class.
//
//////////////////////////////////////////////////////////////////////

#include <cassert>
#include <iterator>
#include "range.h"

#ifndef min
#define min(a,b) (((a)<(b))?(a):(b))
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

//FIXME:use 64 bit instead.
unsigned __int64 range::nlength = 0XFFFFFFFF;//FFFFFFFF;

bool range::intersection( const range & r1, const range & r2,range & result)
{
    if ( r2.end() <= r1.pos() || r2.pos() >= r1.end() )
    {
        // ≤ªœ‡Ωª
        return false;
    }    

    if ( r1.pos() < r2.pos() )
    {
        result.set_pos( r2.pos() );
        result.set_length( min((r1.length()-(r2.pos()-r1.pos())), r2.length()));    
    }
    else
    {
        result.set_pos( r1.pos() );
        result.set_length( min((r2.length()-(r1.pos()-r2.pos())), r1.length()) );    
    }    

    return true;
}

range range::intersection( const range & r1, const range & r2 )
{
    range ret(0,0);
    intersection(r1,r2,ret);
    return ret;
}

void range_minus_range(const range& l, const range& r, std::vector<range>& result)
{
	result.clear();

	if( r.pos() <= l.pos() && r.end() >= l.end() ){
		return;
	}
	else if(l.pos() >= r.end() || l.end() <= r.pos()){
		result.push_back(l);
		return;
	}
	else{
		if( l.pos() < r.pos() ){
			result.push_back(range(l.pos(), r.pos()-l.pos()));

			if(r.end() < l.end()){
				result.push_back(range(r.end(), l.end()-r.end()));
			}
		}
		else{
			assert(r.end() < l.end());
			result.push_back(range(r.end(), l.end()-r.end()));
		}
	}
}

void range_vector_minus_range(const std::vector<range>& l, const range& r, std::vector<range>& result)
{
	result.clear();
	std::vector<range> tmp;
	std::vector<range>::const_iterator iter_left = l.begin();
	for( ;iter_left != l.end(); ++iter_left){
		range_minus_range(*iter_left, r, tmp);
		std::copy(tmp.begin(),tmp.end(),std::back_inserter(result));
	}
}
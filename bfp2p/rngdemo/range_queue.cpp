// range_queue.cpp: implementation of the range_queue class.
//
//////////////////////////////////////////////////////////////////////
#include <algorithm>
#include <assert.h>
#include "range_queue.h"

//#define range_queue_test

//////////////////////////////////////////////////////////////////////
range_queue::range_queue()
{
}

range_queue::range_queue( const range& r)
{
	_range_q.push_back(r);
}

void range_queue::init( const std::vector<range>& v_r )
{
	_range_q = v_r;
	std::sort(_range_q.begin(), _range_q.end());
	std::vector<range>::iterator it = _range_q.begin();
	//std::vector<range>::iterator it = _range_q.begin();
	while( it != _range_q.end() )
	{
		std::vector<range>::iterator next_it = it;
		++next_it;
		if( next_it == _range_q.end() )
			break;
		else
		{
			if( it->end() >= next_it->pos() )
			{
				if( it->end() < next_it->end() )
					it->set_length( next_it->end() - it->pos() );
				_range_q.erase( next_it );//删除以后next_it 被重新赋值了，是安全的
			}
			else
				++it;
		}
	}
}

range_queue::range_queue( const std::vector<range>& v_r)
{
	init( v_r );
}

range_queue::~range_queue()
{
}

const std::vector<range>& range_queue::operator = (const range_queue& r)
{
	if (this != &r)
	{
		const std::vector<range>& r_q = r.ranges();
		_range_q = r_q;
	}
	return _range_q;
}

const std::vector<range>& range_queue::operator = (const range& r)
{
/*	std::vector<range> v_r;
	v_r.push_back(r);
	_range_q = v_r;
	*/
	_range_q.clear();
	_range_q.push_back( r );
	return _range_q;
}

const std::vector<range>& range_queue::operator = ( const std::vector<range>& r_q)
{
	init( r_q );
	return _range_q;
}

std::vector<range>& range_queue::ranges()
{
	return _range_q;
}

const std::vector<range>& range_queue::ranges() const
{
	return _range_q;
}

const std::vector<range>& range_queue::operator -= (const range& r)
{
    assert( r.length() );

	if( 0 != r.length() )
	{
		std::vector<range>::iterator it_find = std::lower_bound(_range_q.begin(), _range_q.end(), r);

		//excise pre-range
		if(it_find != _range_q.begin())
		{
			if(r.pos() < (it_find - 1)->end())
			{//can be excised
				unsigned __int64 old_end = (it_find - 1)->end();
				(it_find - 1)->set_length(r.pos() - (it_find - 1)->pos());
				
				if((it_find - 1)->length() == 0)
				{
					it_find = _range_q.erase(it_find - 1);//it_find 的前一个元素被删除了，it_find的位置需要前移一位
					//it_find --;
				}
			
				if(r.end() < old_end)
				{//split two ranges
					_range_q.insert(it_find, range(r.end(), old_end - r.end()));
					return _range_q;
				}
			}
		}

		while(it_find != _range_q.end() && it_find->pos() < r.end())
		{
			if(it_find->end() <= r.end())
			{//removed
				//pointer ++
				it_find = _range_q.erase(it_find);
			}
			else
			{
				it_find->set_length(it_find->end() - r.end());
				it_find->set_pos(r.end());
				it_find ++;
			}
		}
	}
	return _range_q;
}

const std::vector<range>& range_queue::operator += (const range& r)
{
    assert( r.length() );

	if( 0 != r.length() )
	{
		std::vector<range>::iterator it_find = std::lower_bound(_range_q.begin(), _range_q.end(), r);
		unsigned __int64 new_pos, new_end;
		new_pos = r.pos();
		new_end = r.end();

		//decide new pos
		if(it_find != _range_q.begin())
		{
			if(r.pos() <= (it_find - 1)->end())
			{//can be merge
				if(r.end() <= (it_find - 1)->end())
				{//no change to do
					return _range_q;
				}
				else
				{
					it_find --;
					new_pos = it_find->pos();
					it_find = _range_q.erase(it_find);
				}
			}
		}

		//decide new end;
		//std::vector<range>::iterator it_xxx = _range_q.end();
		while(it_find !=  _range_q.end() && it_find->pos() <= r.end())
		{
			if(it_find->end() <= r.end())
			{//removed
				//pointer ++
				it_find = _range_q.erase(it_find);
			}
			else
			{
				new_end = it_find->end();
				it_find = _range_q.erase(it_find);
			}
		}

		_range_q.insert(it_find, range(new_pos, new_end - new_pos));
	}
	return _range_q;
}

const std::vector<range>& range_queue::operator += ( const std::vector<range>& v_r)
{
	for( std::vector<range>::const_iterator it = v_r.begin(); it != v_r.end(); it++)
	{
		(*this) += (*it);
	}
	return _range_q;
}

const std::vector<range>& range_queue::operator -= ( const std::vector<range>& v_r)
{
	for( std::vector<range>::const_iterator it = v_r.begin(); it != v_r.end(); it++)
	{
		(*this) -= (*it);
	}
	return _range_q;
}


void range_queue::swap( range_queue& other )
{
	_range_q.swap( other.ranges() );
}

const std::vector<range>& range_queue::add_to( const range_queue& r_q, std::vector<range>& result ) const
{
	std::vector<range>::const_iterator src_it = _range_q.begin();
	std::vector<range>::const_iterator src_end = _range_q.end();
	std::vector<range>::const_iterator obj_it = r_q.ranges().begin();
	std::vector<range>::const_iterator obj_end = r_q.ranges().end();
	bool has_merged = false;
	unsigned __int64 merged_begin_pos;
	
	while( (src_it != src_end) && (obj_it != obj_end) )
	{
		if( src_it->end() < obj_it->pos() )
		{
			if( has_merged )
			{
				result.push_back( range(merged_begin_pos, src_it->end()-merged_begin_pos) );
				has_merged = false;
			}
			else
				result.push_back( *src_it );
			++src_it;
		}
		else if( obj_it->end() < src_it->pos() )
		{
			if( has_merged )
			{
				result.push_back( range(merged_begin_pos, obj_it->end()-merged_begin_pos) );
				has_merged = false;
			}
			else
				result.push_back( *obj_it );
			++obj_it;
		}
		else 
		{
			if( has_merged == false )
			{
				if( src_it->pos() < obj_it->pos() )
					merged_begin_pos = src_it->pos();
				else
					merged_begin_pos = obj_it->pos();
				has_merged = true;
			}
			if( src_it->end() < obj_it->end() )
				++src_it;
			else
				++obj_it;
		}
	}
	while( src_it != src_end )
	{
		if( has_merged )
		{
			result.push_back( range(merged_begin_pos, src_it->end()-merged_begin_pos) );
			has_merged = false;
		}
		else
			result.push_back( *src_it );
		++src_it;
	}
	while( obj_it != obj_end )
	{
		if( has_merged )
		{
			result.push_back( range(merged_begin_pos, obj_it->end()-merged_begin_pos) );
			has_merged = false;
		}
		else
			result.push_back( *obj_it );
		++obj_it;
	}
	return _range_q;
}

const std::vector<range>& range_queue::add_to( const range_queue& r_q, range_queue& result ) const
{
	add_to( r_q, result.ranges() );
	return _range_q;
}

const std::vector<range>& range_queue::operator += ( const range_queue& r_q)
{

	range_queue temp_queue;
	add_to( r_q, temp_queue );
#ifndef range_queue_test
	swap( temp_queue );
#else
	#pragma message( "在测试range_queue+=的新实现，如果没有问题，在产品代码中最终要删除测试代码" )
	std::vector<range> temp;
	std::vector<range> obj_ranges( r_q.ranges() );
	std::vector<range>::iterator src_it = _range_q.begin();
	std::vector<range>::iterator src_end = _range_q.end();
	std::vector<range>::iterator obj_it = obj_ranges.begin();
	std::vector<range>::iterator obj_end =obj_ranges.end();
	while( (src_it != src_end) && (obj_it != obj_end) )
	{
		if( src_it->end() < obj_it->pos() )
		{
			temp.push_back( *src_it );
			++src_it;
		}
		else if( obj_it->end() < src_it->pos() )
		{
			temp.push_back( *obj_it );
			++obj_it;
		}
		else if( src_it->end() < obj_it->end() )
		{
			if( src_it->pos() < obj_it->pos() )
			{
				obj_it->set_length( obj_it->end() - src_it->pos() );
				obj_it->set_pos( src_it->pos() );
			}
			++src_it;
		}
		else
		{
			if( obj_it->pos() < src_it->pos() )
			{
				src_it->set_length( src_it->end() - obj_it->pos() );
				src_it->set_pos( obj_it->pos() );
			}
			++obj_it;
		}
	}
	while( src_it != src_end )
	{
		temp.push_back( *src_it );
		++src_it;
	}
	while( obj_it != obj_end )
	{
		temp.push_back( *obj_it );
		++obj_it;
	}
	_range_q.swap( temp );
	tornado_assert( this->is_equal( temp_queue ) );
#endif
	return _range_q;
}

const std::vector<range>& range_queue::sub_to( const range_queue& r_q, std::vector<range>& result ) const
{
	std::vector<range>::const_iterator src_it = _range_q.begin();
	std::vector<range>::const_iterator src_end = _range_q.end();
	std::vector<range>::const_iterator obj_it = r_q.ranges().begin();
	std::vector<range>::const_iterator obj_end = r_q.ranges().end();
	bool src_been_trunced = false;
	unsigned __int64 trunced_pos;
	while( (src_it != src_end) && (obj_it != obj_end) )
	{
		if( src_it->end() <= obj_it->pos() )
		{
			if( src_been_trunced )
			{
				result.push_back( range(trunced_pos, src_it->end()-trunced_pos) );
				src_been_trunced = false;
			}
			else
				result.push_back( *src_it );
			++src_it;
		}
		else if( obj_it->end() <= src_it->pos() )
		{
			++obj_it;
		}
		else 
		{	
			if( src_been_trunced )
			{
				if( trunced_pos < obj_it->pos() )
					result.push_back( range(trunced_pos, obj_it->pos()-trunced_pos) );
			}
			else
			{
				if( src_it->pos() < obj_it->pos() )
					result.push_back( range(src_it->pos(), obj_it->pos()-src_it->pos()) );
			}
			
			if( src_it->end() <= obj_it->end() )
			{
				src_been_trunced = false;
				++src_it;
			}
			else
			{
				src_been_trunced = true;
				trunced_pos = obj_it->end();
				++obj_it;
			}
		}
	}
	while( src_it != src_end )
	{
		if( src_been_trunced )
		{
			result.push_back( range(trunced_pos, src_it->end()-trunced_pos) );
			src_been_trunced = false;
		}
		else
			result.push_back( *src_it );
		++src_it;
	}
	return _range_q;
}

const std::vector<range>& range_queue::sub_to( const range_queue& r_q, range_queue& result ) const
{
	sub_to( r_q, result.ranges() );
	

	return _range_q;
}

const std::vector<range>& range_queue::operator -= ( const range_queue& r_q)
{
	range_queue temp_queue;
	sub_to( r_q, temp_queue );
#ifndef range_queue_test
	swap( temp_queue );
#else
	#pragma message( "在测试range_queue-=的新实现，如果没有问题，在产品代码中最终要删除测试代码" )
	std::vector<range> temp;
	std::vector<range>::iterator src_it = _range_q.begin();
	std::vector<range>::iterator src_end = _range_q.end();
	std::vector<range>::const_iterator obj_it = r_q.ranges().begin();
	std::vector<range>::const_iterator obj_end = r_q.ranges().end();
	while( (src_it != src_end) && (obj_it != obj_end) )
	{
		if( src_it->end() <= obj_it->pos() )
		{
			temp.push_back( *src_it );
			++src_it;
		}
		else if( obj_it->end() <= src_it->pos() )
		{
			++obj_it;
		}
		else 
		{	
			if( src_it->pos() < obj_it->pos() )
				temp.push_back( range(src_it->pos(), obj_it->pos()-src_it->pos()) );
			if( src_it->end() <= obj_it->end() )
			{
				++src_it;
			}
			else
			{
				src_it->set_length( src_it->end() - obj_it->end() );
				src_it->set_pos( obj_it->end() );
				++obj_it;
			}
		}
	}
	while( src_it != src_end )
	{
		temp.push_back( *src_it );
		++src_it;
	}
	_range_q.swap( temp );
	tornado_assert( this->is_equal(temp_queue) );
#endif
	return _range_q;

}

range range_queue::bound(void) const
{
	if( 0 != _range_q.size() )
	{
		return range(_range_q.front().pos(), _range_q.back().end() - _range_q.front().pos());
	}
	else
	{
		return range(0, 0);
	}
}

range range_queue::max_size(void) const
{
	range rd(0, 0);

	for(std::vector<range>::const_iterator me = _range_q.begin(); 
		me != _range_q.end(); me ++)
	{
		if( rd.length() < (*me).length() )
		{
			rd = (*me);
		}
	}
	return rd;
}

range range_queue::min_size(void) const
{
	range rd(0, range::nlength);
	
	for(std::vector<range>::const_iterator me = _range_q.begin(); 
	me != _range_q.end(); me ++)
	{
		if( rd.length() > (*me).length() )
		{
			rd = (*me);
		}
	}
	return rd;
}

const std::vector<range> &range_queue::same_to(const range_queue &q , range_queue &result ) const
{
	same_to( q, result.ranges() );
	return _range_q;
}

const std::vector<range> &range_queue::same_to(const range_queue &q , std::vector<range> &result ) const
{
	result.clear();
	range temp_r(0,0);
	std::vector<range>::const_iterator me = _range_q.begin();
	std::vector<range>::const_iterator me_end = _range_q.end();
	std::vector<range>::const_iterator other = q.ranges().begin();
	std::vector<range>::const_iterator other_end = q.ranges().end();
	while( (me!=me_end) && (other!=other_end) )
	{
		if( me->pos() >= other->end() )
		{
			++other;
			continue;
		}
		if( other->pos() >= me->end() )
		{
			++me;
			continue;
		}
		if( me->pos() > other->pos() )
			temp_r.set_pos( me->pos() );
		else
			temp_r.set_pos( other->pos() );
		if( me->end() > other->end() )
		{
			temp_r.set_length( other->end() - temp_r.pos() );
			++other;
		}
		else
		{
			temp_r.set_length( me->end() - temp_r.pos() );
			++me;
		}
		result.push_back( temp_r );
	}
	return _range_q;
}

const std::vector<range> &range_queue::same_to(const range_queue &q , 
			unsigned min_len, range_queue &result ) const
{
	same_to( q, min_len, result.ranges() );
	return _range_q;
}

const std::vector<range> &range_queue::same_to(const range_queue &q , 
						unsigned min_len, std::vector<range> &result ) const
{
	result.clear();
	range temp_r(0,0);
	std::vector<range>::const_iterator me = _range_q.begin();
	std::vector<range>::const_iterator me_end = _range_q.end();
	std::vector<range>::const_iterator other = q.ranges().begin();
	std::vector<range>::const_iterator other_end = q.ranges().end();
	while( (me!=me_end) && (other!=other_end) )
	{
		if( other->length() < min_len )
		{
			++other;
			continue;
		}
		if( me->pos() >= other->end() )
		{
			++other;
			continue;
		}
		if( other->pos() >= me->end() )
		{
			++me;
			continue;
		}
		if( me->pos() > other->pos() )
			temp_r.set_pos( me->pos() );
		else
			temp_r.set_pos( other->pos() );
		if( me->end() > other->end() )
		{
			temp_r.set_length( other->end() - temp_r.pos() );
			++other;
		}
		else
		{
			temp_r.set_length( me->end() - temp_r.pos() );
			++me;
		}
		result.push_back( temp_r );
	}
	return _range_q;
}

const std::vector<range> &range_queue::same(const range_queue &q)
{

	std::vector<range> temp;
	same_to( q, temp );
	_range_q.swap(temp);
	return _range_q;
}

const std::vector<range> &range_queue::same_to(const range &r, std::vector<range>& result) const
{
	//std::vector<range>& temp = result.ranges();
	result.clear();
	range temp_r(0,0);
	std::vector<range>::const_iterator me = std::lower_bound(_range_q.begin(), _range_q.end(), r);
	if( me != _range_q.begin() )
		--me;
	std::vector<range>::const_iterator me_end = _range_q.end();
	while( me != me_end  )
	{
		if( me->pos() >= r.end() )
		{
			break;
		}
		if( r.pos() >= me->end() )
		{
			++me;
			continue;
		}
		if( me->pos() > r.pos() )
			temp_r.set_pos( me->pos() );
		else
			temp_r.set_pos( r.pos() );
		if( me->end() > r.end() )
		{
			temp_r.set_length( r.end() - temp_r.pos() );
			result.push_back( temp_r );
			break;
		}
		else
		{
			temp_r.set_length( me->end() - temp_r.pos() );
			result.push_back( temp_r );
			++me;
		}
	}
	return _range_q;
}


const std::vector<range> &range_queue::same(const range &r)
{
	std::vector<range> temp;
	same_to( r, temp );

	_range_q.swap( temp );
	return _range_q;
}

const std::vector<range> &range_queue::same_to(const range &r, range_queue& result) const
{
	same_to( r, result.ranges() );
	return _range_q;
}

bool range_queue::first_same_to( const range &r, range &result ) const
{
	std::vector<range>::const_iterator me = std::lower_bound(_range_q.begin(), _range_q.end(), r);
	if ( me != _range_q.begin() )
	{
		--me;
	}
	std::vector<range>::const_iterator me_end = _range_q.end();
	while ( me != me_end )
	{
		if ( me->pos() >= r.end() )
		{
			return false;
		}
		if ( r.pos() >= me->end() )
		{
			++me;
			continue;
		}
		if ( me->pos() > r.pos() )
		{
			result.set_pos( me->pos() );
		}
		else
		{
			result.set_pos( r.pos() );
		}
		if ( me->end() > r.end() )
		{
			result.set_length( r.end() - result.pos() );
		}
		else
		{
			result.set_length( me->end() - result.pos() );
		}
		return true;
	}
	return false;
}

void range_queue::sub_same_to(const range_queue &r_q, range_queue &sub_q, range_queue &same_q)
{
	range same_temp(0,0);
	unsigned __int64 trunced_pos;
	bool src_been_trunced = false;
	std::vector<range> &sub_ranges = sub_q.ranges();
	std::vector<range> &same_ranges = same_q.ranges();
	sub_ranges.clear(); same_ranges.clear();

	std::vector<range>::const_iterator src_it = _range_q.begin();
	std::vector<range>::const_iterator src_end = _range_q.end();
	std::vector<range>::const_iterator obj_it = r_q.ranges().begin();
	std::vector<range>::const_iterator obj_end = r_q.ranges().end();	
	while ( (src_it != src_end) && (obj_it != obj_end) )
	{
		if ( src_it->end() <= obj_it->pos() )
		{
			if ( src_been_trunced )
			{
				sub_ranges.push_back( range(trunced_pos, src_it->end() - trunced_pos) );
				src_been_trunced = false;
			}
			else
			{
				sub_ranges.push_back( *src_it );
			}
			++src_it;
		}
		else if ( obj_it->end() <= src_it->pos() )
		{
			++obj_it;
		}
		else 
		{	
			if ( src_been_trunced )
			{
				if ( trunced_pos < obj_it->pos() )
				{
					sub_ranges.push_back( range(trunced_pos, obj_it->pos() - trunced_pos) );
				}
				if ( src_it->pos() < obj_it->pos() )
				{
					same_temp.set_pos( obj_it->pos() );
				}
				else
				{
					same_temp.set_pos( src_it->pos() );
				}
			}
			else
			{
				if ( src_it->pos() < obj_it->pos() )
				{
					sub_ranges.push_back( range(src_it->pos(), obj_it->pos() - src_it->pos()) );
					same_temp.set_pos( obj_it->pos() );
				}
				else
				{
					same_temp.set_pos( src_it->pos() );
				}
			}
			
			if ( src_it->end() <= obj_it->end() )
			{
				src_been_trunced = false;
				same_temp.set_length( src_it->end() - same_temp.pos() );
				++src_it;
			}
			else
			{
				src_been_trunced = true;
				trunced_pos = obj_it->end();
				same_temp.set_length( obj_it->end() - same_temp.pos() );
				++obj_it;
			}
			same_ranges.push_back( same_temp );
		}
	}	
	while ( src_it != src_end )
	{
		if ( src_been_trunced )
		{
			sub_ranges.push_back( range(trunced_pos, src_it->end() - trunced_pos) );
			src_been_trunced = false;
		}
		else
		{
			sub_ranges.push_back( *src_it );
		}
		++src_it;
	}
}

void range_queue::add_new_to(const range_queue &r_q, range_queue &add_q, range_queue &new_q)
{
	bool has_merged = false;
	bool src_been_trunced = false;
	unsigned __int64 merged_begin_pos, trunced_pos;
	std::vector<range> &add_ranges = add_q.ranges();
	std::vector<range> &new_ranges = new_q.ranges();
	add_ranges.clear(); new_ranges.clear();

	std::vector<range>::const_iterator src_it = _range_q.begin();
	std::vector<range>::const_iterator src_end = _range_q.end();
	std::vector<range>::const_iterator obj_it = r_q.ranges().begin();
	std::vector<range>::const_iterator obj_end = r_q.ranges().end();	
	while ( (src_it != src_end) && (obj_it != obj_end) )
	{
		if ( src_it->end() < obj_it->pos() )
		{
			if ( has_merged )
			{
				add_ranges.push_back( range(merged_begin_pos, src_it->end() - merged_begin_pos) );
				has_merged = false;
			}
			else
			{
				add_ranges.push_back( *src_it );
			}
			++src_it;
		}
		else if ( obj_it->end() < src_it->pos() )
		{
			if ( has_merged )
			{
				add_ranges.push_back( range(merged_begin_pos, obj_it->end() - merged_begin_pos) );
				has_merged = false;
			}
			else
			{
				add_ranges.push_back( *obj_it );
			}
			
			if( src_been_trunced )
			{
				new_ranges.push_back( range(trunced_pos, obj_it->end() - trunced_pos) );
				src_been_trunced = false;
			}
			else
			{
				new_ranges.push_back( *obj_it );
			}
			++obj_it;
		}
		else 
		{
			if ( has_merged == false )
			{
				if ( src_it->pos() < obj_it->pos() )
				{
					merged_begin_pos = src_it->pos();
				}
				else
				{
					merged_begin_pos = obj_it->pos();
				}
				has_merged = true;
			}

			if( src_been_trunced )
			{
				if( trunced_pos < src_it->pos() )
				{
					new_ranges.push_back( range(trunced_pos, src_it->pos() - trunced_pos) );
				}
			}
			else
			{
				if( obj_it->pos() < src_it->pos() )
				{
					new_ranges.push_back( range(obj_it->pos(), src_it->pos() - obj_it->pos()) );
				}
			}

			if ( src_it->end() < obj_it->end() )
			{
				src_been_trunced = true;
				trunced_pos = src_it->end();
				++src_it;
			}
			else
			{
				src_been_trunced = false;
				++obj_it;
			}
		}
	}
	while ( src_it != src_end )
	{
		if ( has_merged )
		{
			add_ranges.push_back( range(merged_begin_pos, src_it->end() - merged_begin_pos) );
			has_merged = false;
		}
		else
		{
			add_ranges.push_back( *src_it );
		}
		++src_it;
	}
	while ( obj_it != obj_end )
	{
		if ( has_merged )
		{
			add_ranges.push_back( range(merged_begin_pos, obj_it->end() - merged_begin_pos) );
			has_merged = false;
		}
		else
		{
			add_ranges.push_back( *obj_it );
		}

		if( src_been_trunced )
		{
			new_ranges.push_back( range(trunced_pos, obj_it->end() - trunced_pos) );
			src_been_trunced = false;
		}
		else
		{
			new_ranges.push_back( *obj_it );
		}
		++obj_it;
	}
}

unsigned __int64 range_queue::all_range_length(void) const
{
	unsigned __int64 ret_val = 0;

	for(std::vector<range>::const_iterator it = _range_q.begin(); it != _range_q.end(); it++)
	{
		ret_val += it->length();
	}
	return ret_val;
}

bool range_queue::is_range_relevant(const range& r) const
{
	std::vector<range>::const_iterator it_find = std::lower_bound(_range_q.begin(), _range_q.end(), r);
	return ( it_find != _range_q.begin() && (it_find - 1)->end() > r.pos() 
			|| it_find != _range_q.end() && it_find->pos() < r.end() );
}

bool range_queue::is_inner_range(const range& r) const
{
	std::vector<range>::const_iterator it_find = std::lower_bound(_range_q.begin(), _range_q.end(), r);
	return ( it_find != _range_q.begin() && (it_find - 1)->end() >= r.end() 
		|| it_find != _range_q.end() && it_find->pos() == r.pos() && it_find->length() >= r.length());
}

bool range_queue::is_complete_range(const range& r, unsigned __int64 file_size) const
{
	std::vector<range>::const_iterator it_find = std::lower_bound(_range_q.begin(), _range_q.end(), r);
	return ( it_find != _range_q.begin() && ((it_find - 1)->end() >= r.end() || (it_find - 1)->end() == file_size)
		|| it_find != _range_q.end() && it_find->pos() == r.pos() && it_find->length() >= r.length());
}

void range_queue::clear()
{
	_range_q.clear();
}

bool range_queue::is_equal( const range_queue& q ) const
{
    const std::vector<range>& v = q.ranges();
    
    if ( v.size() ==0 && _range_q.size() ==0 )
        return true;

    if ( v.size() != _range_q.size() )
        return false;

    unsigned i = 0;
    for ( ; i < v.size(); i++ )
    {
        if ( v[i] == _range_q[i] )
            continue;
        else
            return false;
    }
    
    return true;
}

void range_queue::to_string( std::string & result ) const
{
	char buf[64];
	result = "";
	for ( unsigned int i=0; i<_range_q.size(); i++ )
	{
		sprintf( buf,"(%u)[%I64u, %I64u, %I64u)%s", i+1, _range_q[i].pos(), _range_q[i].length(), _range_q[i].end(), 
			i<(_range_q.size()-1)?"\r\n":"" );
		result += buf;
	}
}

std::string range_queue::to_string( ) const
{
	char buf[64];
    std::string result = "";
	for ( unsigned int i=0; i<_range_q.size(); i++ )
	{
		sprintf( buf, "[%llu,%llu]%s", _range_q[i].pos(), _range_q[i].length(), 
			i<(_range_q.size()-1)?",":"" );
		result += buf;
	}
    return result;
}

std::string range_queue::to_string_line( ) const
{
	char buf[64];
    std::string result = "";
	for ( unsigned int i=0; i<_range_q.size(); i++ )
	{
		sprintf( buf, "(%u)[%llu, %llu, %llu) ", i+1, _range_q[i].pos(), _range_q[i].length(), _range_q[i].end());
		result += buf;
	}
    return result;
}

bool range_queue::is_contain(const range_queue& obj) const
{
	std::vector<range>::const_iterator src_it = _range_q.begin();
	std::vector<range>::const_iterator src_end = _range_q.end();
	std::vector<range>::const_iterator obj_it = obj.ranges().begin();
	std::vector<range>::const_iterator obj_end =obj.ranges().end();
	while( (src_it != src_end) && (obj_it != obj_end) )
	{
		if( src_it->end() <= obj_it->pos() )
		{
			++src_it;
		}
		else if( obj_it->end() <= src_it->pos() )
		{
			return false;
		}
		else
		{
			if( src_it->is_contain( *obj_it ) )
				++obj_it;
			else
				return false;
		}
	}
	if( obj_it == obj_end )
		return true;
	else
		return false;
}


bool range_queue::is_contain( const range_queue& obj, range& r ) const
{
	std::vector<range>::const_iterator src_it = _range_q.begin();
	std::vector<range>::const_iterator src_end = _range_q.end();
	std::vector<range>::const_iterator obj_it = obj.ranges().begin();
	std::vector<range>::const_iterator obj_end =obj.ranges().end();
	r.set(0,0);
	while( (src_it != src_end) && (obj_it != obj_end) )
	{
		if( src_it->end() <= obj_it->pos() )
		{
			++src_it;
		}
		else if( obj_it->end() <= src_it->pos() )
		{
			return false;
		}
		else
		{
			if( src_it->is_contain( *obj_it ) )
			{
				if( obj_it->length() > r.length() )
					r = *obj_it;
				++obj_it;
			}
			else
				return false;
		}
	}
	if( obj_it == obj_end )
		return true;
	else
		return false;
}

bool range_queue::is_relevant(const range_queue& obj) const
{
	std::vector<range>::const_iterator src_it = _range_q.begin();
	std::vector<range>::const_iterator src_end = _range_q.end();
	std::vector<range>::const_iterator obj_it = obj.ranges().begin();
	std::vector<range>::const_iterator obj_end =obj.ranges().end();
	while( (src_it != src_end) && (obj_it != obj_end) )
	{
		if( src_it->end() <= obj_it->pos() )
		{
			++src_it;
		}
		else if( obj_it->end() <= src_it->pos() )
		{
			++obj_it;
		}
		else
		{
			return true;
		}
	}
	return false;
}

void range_queue::inc_offset( unsigned __int64 offset_value )
{
    if ( false == _range_q.empty() && offset_value )
    {
        std::vector<range>::iterator it = _range_q.begin();
        std::vector<range>::iterator it_end = _range_q.end();
        for ( ; it!=it_end; it++ )
        {
            //assert( _UI64_MAX-offset_value >= it->pos() );
            it->set_pos( it->pos() + offset_value );
        }
    }
}

void range_queue::dec_offset( unsigned __int64 offset_value )
{
    if ( false == _range_q.empty() && offset_value )
    {
        std::vector<range>::iterator it = _range_q.begin();
        std::vector<range>::iterator it_end = _range_q.end();
        for ( ; it!=it_end; it++ )
        {
            assert( it->pos() >= offset_value );
            it->set_pos( it->pos() - offset_value );
        }
    }
}

void range_sub_range_queue( const range& r, const range_queue& minuend, range_queue& result )
{
	assert( r.length() );

	result.clear();
	if( 0 != r.length() )
	{
		const std::vector<range> & m_vector = minuend.ranges();
		unsigned __int64 cur_pos = r.pos();
		unsigned __int64 cur_length = r.length();
		
		std::vector<range>::const_iterator it_find = std::lower_bound(m_vector.begin(), m_vector.end(), r);

		if(it_find != m_vector.begin())
		{
			if(r.pos() < (it_find - 1)->end())
			{
				cur_pos = (it_find - 1)->end();			
			}
		}

        bool b_find = it_find != m_vector.end(), b_pos_end = it_find->pos() < r.end();
		while (b_find && b_pos_end)
		{
			cur_length = it_find->pos() - cur_pos;
			if (cur_length > 0)
			{
				result.ranges().push_back(range(cur_pos, cur_length));
			}
			cur_pos = it_find->end();
			++it_find;

            if (b_find = (it_find != m_vector.end()))
            {
                b_pos_end = it_find->pos() < r.end();
            }
		}

		if (cur_pos < r.end())
		{
			cur_length = r.end() - cur_pos;
			result.ranges().push_back(range(cur_pos, cur_length));
		}
	}
}

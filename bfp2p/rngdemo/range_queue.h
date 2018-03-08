// range_queue.h: interface for the range_queue class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_RANGE_QUEUE_H__61DFEF04_76EA_4DE4_8168_BDDAB5B33C5C__INCLUDED_)
#define AFX_RANGE_QUEUE_H__61DFEF04_76EA_4DE4_8168_BDDAB5B33C5C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <vector>
#include <string>
#include "range.h"

class range_queue
{
	std::vector<range> _range_q;

public:
	range_queue();
	range_queue( const range&);
	range_queue(const std::vector<range>&);
	virtual ~range_queue();

	std::vector<range>& ranges();
	const std::vector<range>& ranges() const;
	void clear();

	const std::vector<range> &operator = (const range_queue&);
	const std::vector<range> &operator = (const std::vector<range>&);
	const std::vector<range> &operator = ( const range&);
	const std::vector<range> &operator+= ( const range&);
	const std::vector<range> &operator-= ( const range&);
	
	const std::vector<range> &operator+= ( const range_queue&);
	const std::vector<range> &add_to( const range_queue& r_q, range_queue& result ) const;
	const std::vector<range> &add_to( const range_queue& r_q, std::vector<range>& result ) const;

	const std::vector<range> &operator-= ( const range_queue&);
	const std::vector<range> &sub_to( const range_queue& r_q, range_queue& result ) const;
	const std::vector<range> &sub_to( const range_queue& r_q, std::vector<range>& result ) const;

	void swap( range_queue& other );


	const std::vector<range> &operator+= ( const std::vector<range>&);
	const std::vector<range> &operator-= (const std::vector<range>&);
	range bound(void) const; 
	range max_size(void) const;
	range min_size(void) const;
	
	const std::vector<range> &same(const range_queue &q);
	const std::vector<range> &same_to(const range_queue &q , range_queue &result ) const ;
	const std::vector<range> &same_to(const range_queue &q , std::vector<range> &result ) const ;

	//参数q中大小小于min_len的range不参与same运算
	const std::vector<range> &same_to(const range_queue &q , unsigned min_len, range_queue &result ) const;
	//参数q中大小小于min_len的range不参与same运算
	const std::vector<range> &same_to(const range_queue &q , unsigned min_len, std::vector<range> &result ) const;

	const std::vector<range> &same(const range &r );
	const std::vector<range> &same_to( const range &r, range_queue& result ) const;
	const std::vector<range> &same_to( const range &r, std::vector<range>& result ) const;

	//result返回相交部分第一个range
	bool first_same_to( const range &r, range &result ) const;
	void sub_same_to(const range_queue &r_q, range_queue &sub_q, range_queue &same_q);
	void add_new_to(const range_queue &r_q, range_queue &add_q, range_queue &new_q);

	unsigned __int64 all_range_length(void) const;
	bool is_range_relevant(const range&) const;
	bool is_inner_range(const range&) const;

	bool is_complete_range(const range& r, unsigned __int64 file_size) const;

	bool is_contain(const range_queue&) const;
	//当返回true时，r存放两个queue交集的最大块，本来可以先调用is_contain，再调max_size
	//但为了效率，把这两个功能放在一个函数里
	bool is_contain(const range_queue&, range& r ) const;
	bool is_relevant(const range_queue&) const;
    bool is_equal( const range_queue& q ) const;

	void to_string(std::string &result) const;
	std::string to_string() const;
	std::string to_string_line( ) const;

    // range_queue 整体移位，inc_offset是整体位置增加，dec_offset是整体位置减少
    void inc_offset( unsigned __int64 offset_value );
    void dec_offset( unsigned __int64 offset_value );

protected:
	void init( const std::vector<range>& );
};

void range_sub_range_queue( const range& r, const range_queue&, range_queue& result );

#endif // !defined(AFX_RANGE_QUEUE_H__61DFEF04_76EA_4DE4_8168_BDDAB5B33C5C__INCLUDED_)

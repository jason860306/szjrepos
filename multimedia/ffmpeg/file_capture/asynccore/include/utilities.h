///////////////////////////////////////////////////////////////////////////////
// utilities.h
///////////////////////////////////////////////////////////////////////////////

#pragma once

#include "global_defs.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <ctype.h>
#include <time.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <iostream>
#include <windows.h>

///////////////////////////////////////////////////////////////////////////////
// misc routines

/// Determines whether a string is an integer value.
bool is_int_str(const string& str);

/// Determines whether a string is a 64-bits integer value.
bool is_int64_str(const string& str);

/// Determines whether a string is a floating-point value.
bool is_float_str(const string& str);

/// Determines whether a string is a bool value.
bool is_bool_str(const string& str);

/// Converts a string to a number.
/// If the string @a str does not represent a valid number, this function return the @a default_val.
int str_to_int(const string& str, int default_val = 0);

/// Converts a string to a 64-bits number.
/// If the string @a str does not represent a valid number, this function return the @a default_val.
INT64 str_to_int64(const string& str, INT64 default_val = 0);

/// Converts an integer to a string.
string int_to_str(int value);

/// Converts an integer to a string.
string int_to_str(INT64 value);

/// Converts a string to a floating-point value.
/// If the string @a str does not represent a valid floating-point value, this function return the @a default_val.
double str_to_float(const string& str, double default_val = 0);

/// Converts a floating-point value to a string using a specified format.
string float_to_str(double value, const char *format = "%f");

/// Converts a string to a bool value.
/// If the string @a str does not represent a valid bool value, this function return the @a default_val.
///
/// For example:
/** @verbatim
	The valid string        The converted result
	----------------        --------------------
	"true"             ->   true
	"false"            ->   false
	"True"             ->   true
	"FALSE"            ->   false
	"123.456"          ->   true
	"123"              ->   true
	"0"                ->   false
@endverbatim */
bool str_to_bool(const string& str, bool default_val = false);

/// Converts a bool value to a string.
///
/// For example:
/** @verbatim
	value         use_bool_strs   The converted result
	-----------   ------------    --------------------
	true          false           "1"
	false         false           "0"
	true          true            "true"
	false         true            "false"
@endverbatim */
string bool_to_str(bool value, bool use_bool_strs = false);

/// Converts the integer (host byte order) value to a IP string.
string ip_to_string(UINT32 ip);

///  Converts the IP string to an integer value (host byte order).
UINT32 string_to_ip(const string& str);

/// Format a string.
void format_string_v(string& result, const char *format, va_list arg_list);

/// Formats the string as sprintf does.
string format_string(const char *format, ...);

/// Compares two strings without case sensitivity.
/// Returns true if the two strings have the same value; false otherwise.
bool same_text(const string& str1, const string& str2);

/// Compares two strings without case sensitivity.
/// Returns an integer less than, equal to, or greater than zero if str1 to be
/// less than, to match, or be greater than str2.
int compare_text(const char* str1, const char* str2);

/// Trims all whitespaces from the string.
string trim_string(const string& str);

/// Returns a string that has been converted to uppercase.
string upper_case(const string& str);

/// Returns a string that has been converted to lowercase.
string lower_case(const string& str);

/// Replaces string.
string replace_string(const string& source_str, const string& old_pattern,
	const string& new_pattern, bool replace_all = false, bool case_sensitive = true);

/// Splits a string with a splitter character into a string list.
///
/// @param[in] source_str
///   The string to be splited.
/// @param[in] splitter
///   The splitter character.
/// @param[in] str_list
///   Stores the separated strings.
/// @param[in] trim_result
///   Indicates whether to trim the result list or not.
///
/// For example (Suppose the splitter is the comma <tt>","</tt>.) :
/** @verbatim
	""          -> []
	" "         -> [" "]
	","         -> ["", ""]
	"a,b,c"     -> ["a", "b", "c"]
	",a,,b,c,"  -> ["", "a", "", "b", "c", ""]
@endverbatim */
void split_string(const string& source_str, char splitter, string_array& str_list,
	bool trim_result = false);

/// Fetchs a string from the input string.
///
/// @param[in] input_str
///   The source string to be fetched from.
/// @param[in] delimiter
///   The delimiter character.
/// @param[in] del
///   Determines whether to delete the fetched string from the input string or not.
/// @return
///   Returns the fetched string.
///
/// For example:
/** @verbatim
	input_str(before)  delimiter    del           input_str(after)  result(after)
	----------------   -----------  ----------    ---------------   -------------
	"abc def"           ' '         false         "abc def"         "abc"
	"abc def"           ' '         true          "def"             "abc"
	" abc"              ' '         false         " abc"            ""
	" abc"              ' '         true          "abc"             ""
	""                  ' '         true/false    ""                ""
@endverbatim */
string fetch_str(string& input_str, char delimiter = ' ', bool del = true);

//-----------------------------------------------------------------------------

/// Retrieves the size in bytes of the specified file.
/// @return
///   - The size in bytes of the file, or
///   - (-1), if an error occurs.
INT64 get_file_size(const string& file_name);

/// Tests if a specified file exists.
/// @return
///   Returns true if the file exists; false otherwise.
bool file_exists(const string& file_name);

/// Returns the drive and directory portions of a file name.
/// For example:
/** @verbatim
	extract_file_path("/etc/abc/test.txt");    ->   "/etc/abc/"
	extract_file_path("test.txt");             ->   ""
@endverbatim */
string extract_file_path(const string& file_name);

/// Extracts the name and extension parts of a file name.
/// For example:
/** @verbatim
	extract_file_name("/etc/test.txt");        ->   "test.txt"
@endverbatim */
string extract_file_name(const string& file_name);

/// Returns a path with a path delimiter (\) at the end.
string path_with_slash(const string& path);

/// Returns a path without a path delimiter (\) at the end.
string path_without_slash(const string& path);

/// Return the executable file name of this application.
string get_app_exe_name(bool include_path = true);

/// Returns the path of this application.
string get_app_path();

//-----------------------------------------------------------------------------

/// Returns the last system error code.
int get_last_sys_error();

/// Returns the id of the current thread.
THREAD_ID get_cur_thread_id();

/// Translates the error code.
string sys_error_message(int error_code);

/// Returns the current ticks in milliseconds.
UINT64 get_cur_ticks();

/// Calculates the elapsed tick count using the @a old_ticks and new_ticks.
///
/// @a old_ticks and @a new_ticks are the starting and ending tick counts as returned by the
/// get_cur_ticks.
UINT64 get_tick_diff(UINT64 old_ticks, UINT64 new_ticks);

//-----------------------------------------------------------------------------

/// Returns a value that is guaranteed to be within a specified range.
template <typename T>
const T& ensure_range(const T& value, const T& min_val, const T& max_val)
	{ return (value > max_val) ? max_val : (value < min_val ? min_val : value); }

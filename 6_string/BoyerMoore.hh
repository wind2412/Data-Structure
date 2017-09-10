#ifndef __BM_HH__
#define __BM_HH__

#include <iostream>
#include <locale>

// 【中文】字符串的 Boyer-Moore 算法。
//  http://www.ruanyifeng.com/blog/2013/05/boyer-moore_string_search_algorithm.html
//  http://blog.jobbole.com/52830/

int get_index(const wchar_t & c, const std::wstring & pattern);

int match(const std::wstring & origin, const std::wstring & pattern);


#endif
#include "BoyerMoore.hh"

// #define DEBUG

int get_index(const wchar_t & c, const std::wstring & pattern)			// 得到一个 string 中 某一个 char 的下标位
{
	int last_index = pattern.size() - 1;
	for(int i = last_index; i >= 0; i --) {
		if (c == pattern[i]) {
			return last_index;
		}
	}
	return -1;
}

int find_last_index_of (const wchar_t & c, const std::wstring & pattern, int pos)
{
	if (pos >= pattern.size() || pos < 0)	return -1;
	while(pos >= 0) {
		if (pattern[pos] == c)	return pos;
		else 					pos --;
	}
	return -1;
}

int cal_good_move(int good_pos_in_pattern, const std::wstring & pattern)
{
	// 这里见： http://blog.jobbole.com/52830/ 有比较好的图解。
	int temp = good_pos_in_pattern;
	int result = pattern.size() - 1;
	// int find_longest = pattern.find_first_of(pattern.substr(temp));
	int find_longest = match(pattern, pattern.substr(temp));		// 递归调用 Boyeer Moore！！
	if(find_longest != -1 && find_longest != temp) {
		result = temp - find_longest;
		return result;
	}

	temp ++;
	while (temp < pattern.size()) {
		// int find_substr = pattern.find_first_of(pattern.substr(temp));
		int find_substr = match(pattern, pattern.substr(temp));		// 再次递归调用 Boyeer Moore！！
		if(find_substr == 0) 	return temp;		// 子串在起始位置，那么就中了
		
		temp ++;
	}

	return result;		// 默认返回最长长度。因为根本不匹配，直接移动整个字符串长度。
}

int match(const std::wstring & origin, const std::wstring & pattern)		// 如果 match，返回 origin string 的位置。 否则返回 -1
{
	if (origin.size() < pattern.size())		return -1;
	int origin_pos = pattern.size() - 1;	// pattern 的最后一个字符对应 origin 的位置

	while(origin_pos < origin.size()){		// 如果失败之后要通过计算的长度移动 pattern 的位置。 如果 pattern 对应 origin 的位置 origin_pos 没有被移出到 origin 之外去，就继续做。
		int i = pattern.size() - 1;
		int j = origin_pos;
		for( ; i >= 0; i --, j--) {
			if (pattern[i] == origin[j]) {
				continue;
			} else break;	// i j 没有 -- 就 break 了
		}
		// 跳出循环的时候，不是成功就是遇到了“坏字符” 而失败。
		if (i == -1)	return origin_pos - pattern.size() + 1;		// 匹配成功。返回匹配的子串在 origin 的位置
		else {		// 遇到坏字符。我们要和好后缀一起看。
			int bad_char_pos_in_pattern = i;	// i + 1 就是坏字符在 pattern 中的相对位置。
			int bad_char_pos_in_origin = j;		// j + 1 就是坏字符在 origin 的位置。	// 则，好字符的位置是 [i+1 ～ pattern.size() ) 左开右闭。 当然，如果 i+1 == pattern.size() 那么就没有好后缀。
			int bad_char_move = bad_char_pos_in_pattern - find_last_index_of(origin[bad_char_pos_in_origin], pattern, bad_char_pos_in_pattern-1);	// 后移位数 = 坏字符的位置 - 搜索词中的上一次出现位置
																			// 注意这里是 origin......	// 这里，是在 pattern 中去从右往左寻找 在 origin 中存放的 比对错误的坏字符。
#ifdef DEBUG
			std::cout << "bad move: " << bad_char_move << std::endl;
#endif
			int good_pos_in_pattern = i + 1;
			int good_pos_move = 0;
			if (i != pattern.size() - 1){		// 如果 i 在刚才的 for 循环 -- 了，即有好后缀。
				good_pos_move = pattern.size() - 1 - cal_good_move(good_pos_in_pattern, pattern);
			}

			origin_pos += (good_pos_move > bad_char_move) ? good_pos_move : bad_char_move;	// 移位。
		}
	}

	return -1;		// 跳出了循环，必然是不匹配的。
}
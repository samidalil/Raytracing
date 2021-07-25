#include "../../headers/helpers/Utility.h"

std::string Utility::escape(const std::string& s)
{
	std::string res = "";
	for (auto c : s)
	{
		if (c == '\\')
			res.push_back(c);
		res.push_back(c);
	}
	return res;
}

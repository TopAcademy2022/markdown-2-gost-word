#pragma once

#include <list>

#include "MdSection.h"
#include "MdSectionRule.h"


class MdSectionParser
{
public:
	static std::list<MdSection*> ParseText(std::string text);
};

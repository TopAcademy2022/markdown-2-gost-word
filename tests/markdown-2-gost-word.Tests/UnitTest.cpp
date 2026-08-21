#include "pch.h"
#include "CppUnitTest.h"

#include "MdSectionRule.h"
#include "MdSection.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest
{
	TEST_CLASS(MdSectionRuleTests)
	{
	public:

		TEST_METHOD(ValidHeadings_ParsedAsTitle)
		{
			MdSectionRule rule;

			const char* validHeadings[] = {
				"# Heading 1",
				"## Heading 2",
				"### Heading 3",
				"#### Heading 4",
				"##### Heading 5",
				"###### Heading 6"
			};

			for (const char* heading : validHeadings)
			{
				const MdSectionType* type = rule.GetTypeFromStartRules(heading);
				Assert::IsNotNull(type);
				Assert::IsTrue(*type == MdSectionType::title);
			}
		}

		TEST_METHOD(SingleHash_ParsedAsTitle)
		{
			MdSectionRule rule;

			const MdSectionType* type = rule.GetTypeFromStartRules("#");
			Assert::IsNotNull(type);
			Assert::IsTrue(*type == MdSectionType::title);
		}

		TEST_METHOD(InvalidHeadingsAndPlainText_ParsedAsText)
		{
			MdSectionRule rule;

			const MdSectionType* noSpaceType = rule.GetTypeFromStartRules("#NoSpace");
			Assert::IsNotNull(noSpaceType);
			Assert::IsTrue(*noSpaceType == MdSectionType::text);

			const MdSectionType* sevenHashesType = rule.GetTypeFromStartRules("####### Heading");
			Assert::IsNotNull(sevenHashesType);
			Assert::IsTrue(*sevenHashesType == MdSectionType::text);

			const MdSectionType* plainTextType = rule.GetTypeFromStartRules("Plain text with # inside");
			Assert::IsNotNull(plainTextType);
			Assert::IsTrue(*plainTextType == MdSectionType::text);
		}
	};

	TEST_CLASS(MdSectionTests)
	{
	public:

		TEST_METHOD(GetContent_RemovesHeadingMarkers)
		{
			MdSection section("# Heading", MdSectionType::title);
			Assert::AreEqual(std::string("Heading"), section.GetContent());
		}

		TEST_METHOD(GetContent_SingleHash_ReturnsEmptyString)
		{
			MdSection section("#", MdSectionType::title);
			Assert::AreEqual(std::string(""), section.GetContent());
		}

		TEST_METHOD(GetContent_PlainText_PreservesFullText)
		{
			MdSection noSpaceSec("#NoSpace", MdSectionType::text);
			Assert::AreEqual(std::string("#NoSpace"), noSpaceSec.GetContent());

			MdSection sevenHashesSec("####### Heading", MdSectionType::text);
			Assert::AreEqual(std::string("####### Heading"), sevenHashesSec.GetContent());

			MdSection plainTextSec("Plain text with # inside", MdSectionType::text);
			Assert::AreEqual(std::string("Plain text with # inside"), plainTextSec.GetContent());
		}
	};
}
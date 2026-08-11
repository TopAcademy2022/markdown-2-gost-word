#include "pch.h"
#include "CppUnitTest.h"

#include "MdSectionRule.h"
#include "MdSection.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest
{
	TEST_CLASS(UnitTest)
	{
	public:
		
		TEST_METHOD(ValidHeadings_ParsedAsTitle)
		{
			MdSectionRule rule;

			const MdSectionType* type1 = rule.GetTypeFromStartRules("# Heading");
			Assert::IsNotNull(type1);
			Assert::IsTrue(*type1 == MdSectionType::title);

			const MdSectionType* type6 = rule.GetTypeFromStartRules("###### Heading");
			Assert::IsNotNull(type6);
			Assert::IsTrue(*type6 == MdSectionType::title);
		}

		TEST_METHOD(SingleHash_ParsedAsEmptyTitle)
		{
			MdSectionRule rule;

			const MdSectionType* type = rule.GetTypeFromStartRules("#");
			Assert::IsNotNull(type);
			Assert::IsTrue(*type == MdSectionType::title);

			MdSection section("#", MdSectionType::title);
			Assert::AreEqual(std::string(""), section.GetContent());
		}

		TEST_METHOD(InvalidHeadingsAndPlainText_ParsedAsText)
		{
			MdSectionRule rule;

			const MdSectionType* noSpaceType = rule.GetTypeFromStartRules("#NoSpace");
			Assert::IsNotNull(noSpaceType);
			Assert::IsTrue(*noSpaceType == MdSectionType::text);

			MdSection noSpaceSec("#NoSpace", MdSectionType::text);
			Assert::AreEqual(std::string("#NoSpace"), noSpaceSec.GetContent());

			const MdSectionType* sevenHashesType = rule.GetTypeFromStartRules("####### Heading");
			Assert::IsNotNull(sevenHashesType);
			Assert::IsTrue(*sevenHashesType == MdSectionType::text);

			MdSection sevenHashesSec("####### Heading", MdSectionType::text);
			Assert::AreEqual(std::string("####### Heading"), sevenHashesSec.GetContent());

			const MdSectionType* plainTextType = rule.GetTypeFromStartRules("Plain text with # inside");
			Assert::IsNotNull(plainTextType);
			Assert::IsTrue(*plainTextType == MdSectionType::text);

			MdSection plainTextSec("Plain text with # inside", MdSectionType::text);
			Assert::AreEqual(std::string("Plain text with # inside"), plainTextSec.GetContent());
		}

		TEST_METHOD(HeadingLevels_ParsedCorrectly)
		{
			MdSection h1("# Level 1", MdSectionType::title);
			Assert::AreEqual(1, h1.GetHeadingLevel());

			MdSection h3("### Level 3", MdSectionType::title);
			Assert::AreEqual(3, h3.GetHeadingLevel());

			MdSection h6("###### Level 6", MdSectionType::title);
			Assert::AreEqual(6, h6.GetHeadingLevel());

			MdSection text("Plain text without hashes", MdSectionType::text);
			Assert::AreEqual(0, text.GetHeadingLevel());
		}
	};
}

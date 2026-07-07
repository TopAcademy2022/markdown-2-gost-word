#pragma once


public ref class ClrParser
{
public:
	// 1. Extract a code from text (rules)
	void GetCodeFromRule(System::String^ rule);

	// 2. Create CLR objects from the list of objects
	array<System::Object^>^ CreateObjectsFromRule(System::String^ rule);
};

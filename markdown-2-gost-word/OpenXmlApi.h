#pragma once

#define OPENXML_API_OK 0
#define OPENXML_API_INVALID_ARGUMENT 1
#define OPENXML_API_OPENXML_ERROR 2
#define OPENXML_API_UNKNOWN_ERROR 3

extern "C" __declspec(dllexport) int OpenXml_IsAvailable();
extern "C" __declspec(dllexport) int OpenXml_CreateDocument(const wchar_t* outputPath);
extern "C" __declspec(dllexport) int OpenXml_GetLastError(wchar_t* buffer, int bufferLength);

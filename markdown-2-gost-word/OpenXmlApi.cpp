#include "OpenXmlApi.h"
#include "OpenXmlService.h"

extern "C" __declspec(dllexport) int OpenXml_IsAvailable()
{
    return OpenXmlService_IsAvailable();
}

extern "C" __declspec(dllexport) int OpenXml_CreateDocument(const wchar_t* outputPath)
{
    return OpenXmlService_CreateDocument(outputPath);
}

extern "C" __declspec(dllexport) int OpenXml_GetLastError(wchar_t* buffer, int bufferLength)
{
    return OpenXmlService_GetLastError(buffer, bufferLength);
}

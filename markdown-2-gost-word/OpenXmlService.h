#pragma once

#include "FormattingProfile.h"

using namespace DocumentFormat::OpenXml::Wordprocessing;

int OpenXmlService_IsAvailable();
int OpenXmlService_CreateDocument(const wchar_t* outputPath);
int OpenXmlService_CreateDocument(const wchar_t* outputPath, Document^ body);

int OpenXmlService_CreateDocument(const wchar_t* outputPath, Document^ body,
    const FormattingProfile* profile);

int OpenXmlService_GetLastError(wchar_t* buffer, int bufferLength);
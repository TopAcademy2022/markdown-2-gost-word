#pragma once

#include "FormattingProfile.h"
#include "OpenXmlApi.h"
#include <vcclr.h>

using namespace DocumentFormat::OpenXml::Packaging;

XmlServiceStatus ApplyFormattingProfile(MainDocumentPart^ mainPart, const FormattingProfile& profile);
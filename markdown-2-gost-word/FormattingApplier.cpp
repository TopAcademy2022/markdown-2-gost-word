#include "FormattingApplier.h"
#include "UnitConversion.h"

using namespace System;
using namespace DocumentFormat::OpenXml;
using namespace DocumentFormat::OpenXml::Wordprocessing;
using namespace DocumentFormat::OpenXml::Packaging;
using namespace UnitConversion;

namespace
{
    JustificationValues ToJustificationValue(const std::string& alignment)
    {
        if (alignment == "left")    return JustificationValues::Left;
        if (alignment == "center")  return JustificationValues::Center;
        if (alignment == "right")   return JustificationValues::Right;
        if (alignment == "justify") return JustificationValues::Both;

        // LoadFormattingProfile rejects unknown values before this ever
        // runs; this fallback only guards against direct/manual callers.
        return JustificationValues::Left;
    }

    void ApplyNormalStyle(MainDocumentPart^ mainPart, const FormattingProfile& profile)
    {
        StyleDefinitionsPart^ stylesPart = mainPart->AddNewPart<StyleDefinitionsPart>();
        Styles^ styles = gcnew Styles();

        Style^ normalStyle = gcnew Style();
        normalStyle->Type = gcnew EnumValue<StyleValues>(StyleValues::Paragraph);
        normalStyle->StyleId = "Normal";
        normalStyle->Default = gcnew OnOffValue(true);

        // NOTE: Style has no writable `Name` property in the OpenXML SDK —
        // the style's display name is the child element <w:name>, added via
        // StyleName below. (Style::Name/->Name = "..." will not compile.)
        normalStyle->AppendChild(gcnew StyleName{ Val = "Normal" });

        // --- Paragraph properties: line spacing, first-line indent, alignment ---
        // pPr must come before rPr per the OOXML CT_Style schema order.
        StyleParagraphProperties^ paraProps = gcnew StyleParagraphProperties();

        SpacingBetweenLines^ spacing = gcnew SpacingBetweenLines();
        spacing->Line = LineSpacingFactorToTwips(profile.paragraph.line_spacing).ToString();
        spacing->LineRule = gcnew EnumValue<LineSpacingRuleValues>(LineSpacingRuleValues::Auto);
        paraProps->AppendChild(spacing);

        Indentation^ indent = gcnew Indentation();
        indent->FirstLine = MmToTwips(profile.paragraph.first_line_indent_mm).ToString();
        paraProps->AppendChild(indent);

        Justification^ just = gcnew Justification();
        just->Val = gcnew EnumValue<JustificationValues>(ToJustificationValue(profile.paragraph.alignment));
        paraProps->AppendChild(just);

        normalStyle->AppendChild(paraProps);

        // --- Run properties: font family, font size ---
        StyleRunProperties^ runProps = gcnew StyleRunProperties();

        RunFonts^ fonts = gcnew RunFonts();
        String^ fontFamily = gcnew String(profile.font.family.c_str());
        fonts->Ascii = fontFamily;
        fonts->HighAnsi = fontFamily;
        fonts->EastAsia = fontFamily;
        fonts->ComplexScript = fontFamily;
        runProps->AppendChild(fonts);

        runProps->AppendChild(gcnew FontSize{ Val = PtToHalfPoints(profile.font.size_pt).ToString() });
        runProps->AppendChild(gcnew FontSizeComplexScript{ Val = PtToHalfPoints(profile.font.size_pt).ToString() });

        normalStyle->AppendChild(runProps);

        styles->AppendChild(normalStyle);
        stylesPart->Styles = styles;

        // IMPORTANT: without Save() the part can end up empty/unwritten —
        // a silent bug that only shows up when you inspect styles.xml.
        stylesPart->Styles->Save();
    }

    void ApplySectionProperties(Body^ body, const FormattingProfile& profile)
    {
        // Remove any pre-existing SectionProperties so we never end up with
        // two <w:sectPr> in Body (would produce an invalid/ambiguous docx).
        for (int i = body->ChildElements->Count - 1; i >= 0; --i)
        {
            OpenXmlElement^ child = body->ChildElements[i];
            if (child->GetType() == SectionProperties::typeid)
            {
                body->RemoveChild(child);
                break;
            }
        }

        SectionProperties^ sectPr = gcnew SectionProperties();

        PageSize^ pageSize = gcnew PageSize();
        pageSize->Width = static_cast<uint32_t>(MmToTwips(profile.page.width_mm));
        pageSize->Height = static_cast<uint32_t>(MmToTwips(profile.page.height_mm));
        pageSize->Orient = gcnew EnumValue<PageOrientationValues>(
            profile.page.orientation == "landscape"
            ? PageOrientationValues::Landscape
            : PageOrientationValues::Portrait);
        sectPr->AppendChild(pageSize);

        PageMargin^ margins = gcnew PageMargin();
        margins->Top = MmToTwips(profile.page.margins.top_mm);
        margins->Bottom = MmToTwips(profile.page.margins.bottom_mm);
        margins->Left = static_cast<uint32_t>(MmToTwips(profile.page.margins.left_mm));
        margins->Right = static_cast<uint32_t>(MmToTwips(profile.page.margins.right_mm));
        margins->Gutter = 0;
        sectPr->AppendChild(margins);

        // SectionProperties must always be the LAST child of Body.
        body->AppendChild(sectPr);
    }
}

XmlServiceStatus ApplyFormattingProfile(MainDocumentPart^ mainPart, const FormattingProfile& profile)
{
    if (mainPart == nullptr || mainPart->Document == nullptr || mainPart->Document->Body == nullptr)
    {
        return XmlServiceStatus::invalid;
    }

    try
    {
        ApplyNormalStyle(mainPart, profile);
        ApplySectionProperties(mainPart->Document->Body, profile);
        return XmlServiceStatus::ok;
    }
    catch (System::Exception^)
    {
        return XmlServiceStatus::open_xml_error;
    }
}
#pragma once

#include <string>
#include <cstdint>

struct PageMargins
{
    double top_mm = 20;
    double bottom_mm = 20;
    double left_mm = 30;
    double right_mm = 15;
};

struct PageSettings
{
    double width_mm = 210;
    double height_mm = 297;
    std::string orientation = "portrait";
    PageMargins margins;
};

struct FontSettings
{
    std::string family = "Times New Roman";
    double size_pt = 14;
};

struct ParagraphSettings
{
    double line_spacing = 1.5;
    double first_line_indent_mm = 12.5;
    std::string alignment = "justify";
};

struct FormattingProfile
{
    int version = 1;
    std::string name;
    PageSettings page;
    FontSettings font;
    ParagraphSettings paragraph;
};

struct ProfileLoadResult
{
    bool ok = false;
    FormattingProfile profile;
    std::string error;
};

ProfileLoadResult LoadFormattingProfile(const std::string& json_path);

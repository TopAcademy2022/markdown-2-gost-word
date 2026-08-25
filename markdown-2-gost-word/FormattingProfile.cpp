#include "FormattingProfile.h"
#include "thirdparty/nlohmann/json.hpp"

#include <fstream>
#include <sstream>

using json = nlohmann::json;

static bool HasField(const json& j, const std::string& path)
{
    size_t pos = 0;
    std::string token;
    std::string remaining = path;
    const json* current = &j;

    while ((pos = remaining.find('.')) != std::string::npos)
    {
        token = remaining.substr(0, pos);
        remaining = remaining.substr(pos + 1);
        if (!current->contains(token))
            return false;
        current = &(*current)[token];
    }
    return current->contains(remaining);
}

static double GetDouble(const json& j, const std::string& path)
{
    size_t pos = 0;
    std::string token;
    std::string remaining = path;
    const json* current = &j;

    while ((pos = remaining.find('.')) != std::string::npos)
    {
        token = remaining.substr(0, pos);
        remaining = remaining.substr(pos + 1);
        current = &(*current)[token];
    }
    return (*current)[remaining].get<double>();
}

static std::string GetString(const json& j, const std::string& path)
{
    size_t pos = 0;
    std::string token;
    std::string remaining = path;
    const json* current = &j;

    while ((pos = remaining.find('.')) != std::string::npos)
    {
        token = remaining.substr(0, pos);
        remaining = remaining.substr(pos + 1);
        current = &(*current)[token];
    }
    return (*current)[remaining].get<std::string>();
}

static int GetInt(const json& j, const std::string& path)
{
    size_t pos = 0;
    std::string token;
    std::string remaining = path;
    const json* current = &j;

    while ((pos = remaining.find('.')) != std::string::npos)
    {
        token = remaining.substr(0, pos);
        remaining = remaining.substr(pos + 1);
        current = &(*current)[token];
    }
    return (*current)[remaining].get<int>();
}

ProfileLoadResult LoadFormattingProfile(const std::string& json_path)
{
    ProfileLoadResult result;

    std::ifstream file(json_path);
    if (!file.is_open())
    {
        result.error = "File not found: " + json_path;
        return result;
    }

    json j;
    try
    {
        j = json::parse(file);
    }
    catch (const json::parse_error& e)
    {
        result.error = std::string("Malformed JSON: ") + e.what();
        return result;
    }

    // Validate version
    if (!HasField(j, "version"))
    {
        result.error = "Missing field: version";
        return result;
    }
    int ver = GetInt(j, "version");
    if (ver != 1)
    {
        result.error = "Unsupported version: " + std::to_string(ver) + " (expected 1)";
        return result;
    }

    // Validate required fields
    const char* requiredFields[] = {
        "page.width_mm", "page.height_mm", "page.orientation",
        "page.margins.top_mm", "page.margins.bottom_mm",
        "page.margins.left_mm", "page.margins.right_mm",
        "font.family", "font.size_pt",
        "paragraph.line_spacing", "paragraph.first_line_indent_mm", "paragraph.alignment"
    };

    for (const char* field : requiredFields)
    {
        if (!HasField(j, field))
        {
            result.error = std::string("Missing field: ") + field;
            return result;
        }
    }

    // Validate numeric ranges
    auto validatePositive = [&](const std::string& field, double val) -> bool {
        if (val <= 0)
        {
            result.error = field + " must be > 0, got " + std::to_string(val);
            return false;
        }
        return true;
    };

    double w = GetDouble(j, "page.width_mm");
    double h = GetDouble(j, "page.height_mm");
    double top = GetDouble(j, "page.margins.top_mm");
    double bottom = GetDouble(j, "page.margins.bottom_mm");
    double left = GetDouble(j, "page.margins.left_mm");
    double right = GetDouble(j, "page.margins.right_mm");
    double fontSize = GetDouble(j, "font.size_pt");
    double lineSpacing = GetDouble(j, "paragraph.line_spacing");
    double indent = GetDouble(j, "paragraph.first_line_indent_mm");

    if (!validatePositive("page.width_mm", w)) return result;
    if (!validatePositive("page.height_mm", h)) return result;
    if (!validatePositive("page.margins.top_mm", top)) return result;
    if (!validatePositive("page.margins.bottom_mm", bottom)) return result;
    if (!validatePositive("page.margins.left_mm", left)) return result;
    if (!validatePositive("page.margins.right_mm", right)) return result;
    if (!validatePositive("font.size_pt", fontSize)) return result;
    if (!validatePositive("paragraph.line_spacing", lineSpacing)) return result;

    std::string orient = GetString(j, "page.orientation");
    if (orient != "portrait" && orient != "landscape")
    {
        result.error = "page.orientation must be 'portrait' or 'landscape', got '" + orient + "'";
        return result;
    }

    std::string align = GetString(j, "paragraph.alignment");
    if (align != "left" && align != "center" && align != "right" && align != "justify")
    {
        result.error = "paragraph.alignment must be 'left', 'center', 'right', or 'justify', got '" + align + "'";
        return result;
    }

    // Build profile
    FormattingProfile profile;
    profile.version = ver;
    profile.name = HasField(j, "name") ? GetString(j, "name") : "";
    profile.page.width_mm = w;
    profile.page.height_mm = h;
    profile.page.orientation = orient;
    profile.page.margins.top_mm = top;
    profile.page.margins.bottom_mm = bottom;
    profile.page.margins.left_mm = left;
    profile.page.margins.right_mm = right;
    profile.font.family = GetString(j, "font.family");
    profile.font.size_pt = fontSize;
    profile.paragraph.line_spacing = lineSpacing;
    profile.paragraph.first_line_indent_mm = indent;
    profile.paragraph.alignment = align;

    result.ok = true;
    result.profile = profile;
    return result;
}

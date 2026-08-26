#pragma once

#include <cmath>
#include <cstdint>


namespace UnitConversion
{
    constexpr double TwipsPerMm = 1440.0 / 25.4;
    constexpr int TwipsPerSingleLine = 240;

    inline int32_t MmToTwips(double mm)
    {
        return static_cast<int32_t>(std::lround(mm * TwipsPerMm));
    }

    inline int32_t PtToHalfPoints(double pt)
    {
        return static_cast<int32_t>(std::lround(pt * 2.0));
    }

    inline int32_t LineSpacingFactorToTwips(double factor)
    {
        return static_cast<int32_t>(std::lround(TwipsPerSingleLine * factor));
    }
}
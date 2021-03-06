/***************************************************************************************
* Original Author:		Gabriele Giuseppini
* Created:				2018-04-09
* Copyright:			Gabriele Giuseppini  (https://github.com/GabrieleGiuseppini)
***************************************************************************************/
#pragma once

#include <cstdint>

#pragma pack(push)
struct ImageSize
{
public:

    int Width;
    int Height;

    ImageSize(
        int width,
        int height)
        : Width(width)
        , Height(height)
    {
    }

    inline bool operator==(ImageSize const & other) const
    {
        return this->Width == other.Width
            && this->Height == other.Height;
    }
};
#pragma pack(pop)

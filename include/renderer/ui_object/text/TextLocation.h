#ifndef TEXTLOCATION_H
#define TEXTLOCATION_H

enum TextLocation : int
{
    ABSOLUTE,
    UL_RELATIVE, // relative to upper-left corner
    UC_RELATIVE, // relative to upper-center
    UR_RELATIVE, // relative to upper-right corner
    ML_RELATIVE, // relative to middle-left
    MC_RELATIVE, // relative to center of screen
    MR_RELATIVE, // relative to middle-right
    BL_RELATIVE, // relative to bottom-left corner
    BC_RELATIVE, // relative to bottom-center
    BR_RELATIVE, // relative to bottom-right corner
};

#endif //TEXTLOCATION_H

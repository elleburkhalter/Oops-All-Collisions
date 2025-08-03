#ifndef TEXTALIGNMENT_H
#define TEXTALIGNMENT_H

enum TextAlignment : int
{
    UL,  // origin of text is upper-left corner
    UC,  // origin of text is upper-center point on edge
    UR,  // origin of text is upper-right corner
    ML,  // origin of text is middle-left point on edge
    MC,  // origin of text is center of text
    MR,  // origin of text is middle-right point on edge
    BL,  // origin of text is bottom-left corner
    BC,  // origin of text is bottom-center point on edge
    BR  // origin of text is bottom-right corner
};

#endif //TEXTALIGNMENT_H

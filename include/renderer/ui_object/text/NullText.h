#ifndef NULLTEXT_H
#define NULLTEXT_H

#include <renderer/ui_object/text/TextInterface.h>

class NullText final : public TextInterface
{
public:
    NullText(): text("Default Text") {};
    NullText(std::string text, const size_t _, const Point __ = {0, 0}): text(std::move(text)) {};

    size_t get_font_size() const override { return 0; }
    std::string get_text() const override { return text; }
    Point get_relative_position() const override { return {0, 0}; }
    TextLocation get_anchor() const override { return TextLocation::UL_RELATIVE; };
    TextAlignment get_alignment() const override { return TextAlignment::UL; };
    Point get_absolute_position(const OopsBoundingBox& _) const override { return {0, 0}; };
    Point get_absolute_position() const override { return {0, 0}; };

    void draw() const override {};

private:
    std::string text;
};

#endif //NULLTEXT_H

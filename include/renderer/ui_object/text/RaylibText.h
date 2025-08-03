#ifndef TEXT_H
#define TEXT_H

#include <raylib.h>
#include <renderer/ui_object/text/TextInterface.h>

class RaylibText final : public TextInterface
{
public:
    RaylibText(): text("Default Text") {};
    RaylibText(std::string text, const size_t font_size, const Point position = {0, 0}): text(std::move(text)), font_size(font_size), position(position) {};

    [[nodiscard]] size_t get_font_size() const override { return font_size; }
    [[nodiscard]] std::string get_text() const override { return text; }
    [[nodiscard]] Point get_relative_position() const override;
    [[nodiscard]] TextLocation get_anchor() const override { return anchor; }
    [[nodiscard]] TextAlignment get_alignment() const override { return alignment; }

    [[nodiscard]] Point get_absolute_position(const OopsBoundingBox& contained_box) const override;
    [[nodiscard]] Point get_absolute_position() const override;

    void set_position(const Point point) { position = point; }
    void set_text(std::string text) { this->text = std::move(text); }
    void set_font_size(const size_t font_size) { this->font_size = font_size; }
    void set_anchor(const TextLocation anchor) { this->anchor = anchor; }
    void set_alignment(const TextAlignment alignment) { this->alignment = alignment; }

    void draw(const Color& color) const;
    void draw(const OopsBoundingBox& parent, const Color& color) const;

private:
    std::string text;
    size_t font_size{48};
    Point position;
    TextLocation anchor{ TextLocation::UL_RELATIVE };
    TextAlignment alignment{ TextAlignment::UL };
};

#endif //TEXT_H

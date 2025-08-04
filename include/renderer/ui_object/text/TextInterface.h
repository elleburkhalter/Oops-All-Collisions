#ifndef TEXTINTERFACE_H
#define TEXTINTERFACE_H

#include <string>
#include <spatial/Point.h>
#include <spatial/OopsBoundingBox.h>
#include <renderer/ui_object/text/TextLocation.h>
#include <renderer/ui_object/text/TextAlignment.h>

class TextInterface
{
public:
    virtual ~TextInterface() = default;

    [[nodiscard]] virtual size_t get_font_size() const = 0;
    [[nodiscard]] virtual std::string get_text() const = 0;
    [[nodiscard]] virtual Point get_relative_position() const = 0;
    [[nodiscard]] virtual TextLocation get_anchor() const = 0;
    [[nodiscard]] virtual TextAlignment get_alignment() const = 0;

    [[nodiscard]] virtual Point get_absolute_position(const OopsBoundingBox& contained_box) const = 0;
    [[nodiscard]] virtual Point get_absolute_position() const = 0;

    virtual void draw() const = 0;

};

#endif //TEXTINTERFACE_H

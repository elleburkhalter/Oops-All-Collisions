#include <renderer/ui_object/text/RaylibText.h>
#include <raylib.h>

Point RaylibText::get_absolute_position() const
{
    return get_absolute_position({0, 0, static_cast<double>(GetScreenWidth()), static_cast<double>(GetScreenHeight())});
}
void RaylibText::draw(const Color& color) const
{
    const Point position = get_absolute_position();
    DrawText(get_text().c_str(), static_cast<int>(position.x), static_cast<int>(position.y), get_font_size(), color);
}
void RaylibText::draw(const OopsBoundingBox& parent, const Color& color) const
{
    const Point position = get_absolute_position(parent);
    DrawText(get_text().c_str(), static_cast<int>(position.x), static_cast<int>(position.y), get_font_size(), color);
}

Point RaylibText::get_absolute_position(const OopsBoundingBox& contained_box) const
{
    const double width = contained_box.get_width();
    const double height = contained_box.get_height();

    Point origin;
    const Point rel_pos = get_relative_position();

    switch (this->anchor)
    {
    case TextLocation::UL_RELATIVE:
        origin = contained_box.get_ul();
        break;
    case TextLocation::UC_RELATIVE:
        origin = contained_box.get_ul() + Point{width / 2, 0};
        break;
    case TextLocation::UR_RELATIVE:
        origin = contained_box.get_ur();
        break;
    case TextLocation::ML_RELATIVE:
        origin = contained_box.get_ul() + Point{0, height / 2};
        break;
    case TextLocation::MC_RELATIVE:
        origin = contained_box.get_ul() + Point{width / 2, height / 2};
        break;
    case TextLocation::MR_RELATIVE:
        origin = contained_box.get_ur() + Point{0, height / 2};
        break;
    case TextLocation::BL_RELATIVE:
        origin = contained_box.get_bl();
        break;
    case TextLocation::BC_RELATIVE:
        origin = contained_box.get_bl() + Point{width / 2, 0};
        break;
    case TextLocation::BR_RELATIVE:
        origin = contained_box.get_br();
        break;
    case TextLocation::ABSOLUTE:
        origin = {0, 0};
        break;
    }

    return {origin.x + rel_pos.x, origin.y + rel_pos.y};
}

Point RaylibText::get_relative_position() const
{
    const auto font = GetFontDefault();
    const auto text_size = MeasureTextEx(font, text.c_str(), font_size, 1);

    switch (this->alignment)
    {
    case TextAlignment::UL:
        return position;
    case TextAlignment::UC:
        return {position.x - text_size.x / 2, position.y};
    case TextAlignment::UR:
        return {position.x - text_size.x, position.y};
    case TextAlignment::ML:
        return {position.x, position.y - text_size.y / 2};
    case TextAlignment::MC:
        return {position.x - text_size.x / 2, position.y - text_size.y / 2};
    case TextAlignment::MR:
        return {position.x - text_size.x, position.y - text_size.y / 2};
    case TextAlignment::BL:
        return {position.x, position.y - text_size.y};
    case TextAlignment::BC:
        return {position.x - text_size.x / 2, position.y - text_size.y};
    case TextAlignment::BR:
        return {position.x - text_size.x, position.y - text_size.y};
    }

    return {0, 0};
}

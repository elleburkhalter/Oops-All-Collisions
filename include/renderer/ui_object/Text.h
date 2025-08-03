#ifndef TEXT_H
#define TEXT_H

#include <string>
#include <spatial/Point.h>

struct Text
{
    Text(): text("Default Text") {};
    explicit Text(std::string text): text(std::move(text)) {};
    Text(std::string text, const Point position): text(std::move(text)), position(position) {};
    Text(std::string text, const double x, const double y): text(std::move(text)), position(x, y) {};
    
    std::string text;
    Point position;
};

#endif //TEXT_H

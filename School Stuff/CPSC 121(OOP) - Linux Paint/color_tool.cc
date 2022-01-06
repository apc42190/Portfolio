#include "color_tool.h"

graphics::Color ColorTool::GetColor() const { return color_; }

void ColorTool::SetColor(const graphics::Color& color) { color_ = color; }
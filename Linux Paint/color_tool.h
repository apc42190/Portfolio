#include "cpputils/graphics/image.h"

#ifndef COLOR_TOOL_H
#define COLOR_TOOL_H

class ColorTool {
 public:
  virtual graphics::Color GetColor() const;
  void SetColor(const graphics::Color&);

 protected:
  graphics::Color color_;
};

#endif  // COLOR_TOOL_H

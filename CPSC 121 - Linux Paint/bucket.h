#include "color_tool.h"
#include "cpputils/graphics/image.h"

#ifndef BUCKET_H
#define BUCKET_H

class Bucket : public ColorTool {
 public:
  void Fill(int, int, graphics::Image&);
  void RecursiveFill(int, int, graphics::Color, graphics::Color,
                     graphics::Image&);
  void IterativeFill(int, int, graphics::Color, graphics::Color,
                     graphics::Image&);
};

#endif  // BUCKET_H

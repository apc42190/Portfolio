#include "color_tool.h"
#include "cpputils/graphics/image.h"
#include "path_tool.h"

#ifndef PENCIL_H
#define PENCIL_H

class Pencil : public ColorTool, public PathTool {
 public:
  void Start(int, int, graphics::Image&) override;
  void MoveTo(int, int, graphics::Image&) override;
  void TriangleInCircleUp(int, int, int, graphics::Image&);
  void TriangleInCircleDown(int, int, int, graphics::Image&);
};

#endif  // PENCIL_H

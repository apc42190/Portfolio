#include "color_tool.h"
#include "cpputils/graphics/image.h"
#include "path_tool.h"

#ifndef BRUSH_H
#define BRUSH_H

class Brush : public ColorTool, public PathTool {
  // Your code here to define the methods in brush.
 public:
  virtual graphics::Color GetColor() const override;
  void Start(int, int, graphics::Image&) override;
  void MoveTo(int, int, graphics::Image&) override;
  void SetWidth(int);
  void TriangleInCircleUp(int, int, int, graphics::Image&);
  void TriangleInCircleDown(int, int, int, graphics::Image&);
  void DiamondInSquare(int, int, int, graphics::Image&);
  void SquareInDiamond(int, int, int, graphics::Image&);

 private:
  int width;
};

#endif  // BRUSH_H

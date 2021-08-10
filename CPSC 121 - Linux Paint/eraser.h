#include "brush.h"
#include "cpputils/graphics/image.h"

#ifndef ERASER_H
#define ERASER_H

class Eraser : public Brush {
  // Your code here
 public:
  Eraser() : Brush() {}
  graphics::Color GetColor() const override;
};

#endif  // ERASER_H

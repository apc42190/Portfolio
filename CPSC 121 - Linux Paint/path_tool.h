#include "cpputils/graphics/image.h"

#ifndef PATH_TOOL_H
#define PATH_TOOL_H

class PathTool {
  // Your code here to define the methods in path_tool.h
 public:
  virtual void Start(int, int, graphics::Image&);
  virtual void MoveTo(int, int, graphics::Image&);

 protected:
  int GetX();
  int GetY();

 private:
  int x_;
  int y_;
};

#endif  // PATH_TOOL_H

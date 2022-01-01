#include "path_tool.h"

void PathTool::Start(int x, int y, graphics::Image& image) {
  x_ = x;
  y_ = y;
};
void PathTool::MoveTo(int x, int y, graphics::Image& image) {
  x_ = x;
  y_ = y;
};
int PathTool::GetX() { return x_; };
int PathTool::GetY() { return y_; };

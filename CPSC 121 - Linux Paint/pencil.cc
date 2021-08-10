#include "pencil.h"

#include <cmath>
// Your code here to implement the functions in pencil.h
void Pencil::Start(int x, int y, graphics::Image& image) {
  image.SetColor(x, y, ColorTool::GetColor());
  PathTool::Start(x, y, image);
}
void Pencil::MoveTo(int x, int y, graphics::Image& image) {
  image.DrawLine(PathTool::GetX(), PathTool::GetY(), x, y,
                 ColorTool::GetColor(), 1);
  PathTool::MoveTo(x, y, image);
}
void Pencil::TriangleInCircleUp(int x, int y, int radius,
                                graphics::Image& image) {
  Start(x, y, image);
  int x_bottom_left = (x - (sqrt(.75 * (radius * radius))));
  int y_bottom_left = (y + (1.5 * (float)radius));
  MoveTo(x_bottom_left, y_bottom_left, image);
  int x_bottom_right = (x + (sqrt(.75 * (radius * radius))));
  int y_bottom_right = y_bottom_left;
  MoveTo(x_bottom_right, y_bottom_right, image);
  MoveTo(x, y, image);
};
void Pencil::TriangleInCircleDown(int x, int y, int radius,
                                  graphics::Image& image) {
  Start(x, y, image);
  int x_top_left = (x - (sqrt(.75 * (radius * radius))));
  int y_top_left = (y - (1.5 * (float)radius));
  MoveTo(x_top_left, y_top_left, image);
  int x_top_right = (x + (sqrt(.75 * (radius * radius))));
  int y_top_right = y_top_left;
  MoveTo(x_top_right, y_top_right, image);
  MoveTo(x, y, image);
}

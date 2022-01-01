#include "brush.h"
#include <cmath>


graphics::Color Brush::GetColor() const { return ColorTool::GetColor(); }
void Brush::Start(int x, int y, graphics::Image& image) {
  image.DrawCircle(x, y, width / 2, GetColor());
  PathTool::Start(x, y, image);
};

void Brush::MoveTo(int x, int y, graphics::Image& image) {
  image.DrawCircle(PathTool::GetX(), PathTool::GetY(), width / 2, GetColor());
  image.DrawCircle(x, y, width / 2, GetColor());
  image.DrawLine(PathTool::GetX(), PathTool::GetY(), x, y, GetColor(), width);
  PathTool::MoveTo(x, y, image);
};

void Brush::SetWidth(int x) { width = x; };

// Accepts coordinates for top of triangle and the radius of the circle as
// arguments, then inscribes a tip-up triangle in that circle.
void Brush::TriangleInCircleUp(int x, int y, int radius,
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

// Accepts coordinates for vertex of triangle and the radius of the circle and
// inscribes a tip-down triangle in that circle.
void Brush::TriangleInCircleDown(int x, int y, int radius,
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

void Brush::DiamondInSquare(int x, int y, int size, graphics::Image& image) {
  Start(x + (size / 2), y, image);
  MoveTo(x, y + (size / 2), image);
  MoveTo(x + (size / 2), y + size, image);
  MoveTo(x + size, y + (size / 2), image);
  MoveTo(x + (size / 2), y, image);
};

void Brush::SquareInDiamond(int x, int y, int height, graphics::Image& image) {
  Start(x - (height / 4), y + (height / 4), image);
  MoveTo(x - (height / 4), y + (3 * (height / 4)), image);
  MoveTo(x + (height / 4), y + (3 * (height / 4)), image);
  MoveTo(x + (height / 4), y + (height / 4), image);
  MoveTo(x - (height / 4), y + (height / 4), image);
};

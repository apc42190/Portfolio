#include "bucket.h"

#include <queue>

// Point is a class for use with IterativeFill.
class Point {
  // Your code here to create a helper class, Point, for use in your queue.
 public:
  void SetX(int x) { x_ = x; };
  void SetY(int y) { y_ = y; };
  int GetX() { return x_; };
  int GetY() { return y_; };

 private:
  int x_;
  int y_;
};

// Your code here to implement the functions in bucket.h
void Bucket::Fill(int x, int y, graphics::Image& image) {
  graphics::Color start = image.GetColor(x, y);
  IterativeFill(x, y, start, ColorTool::GetColor(), image);
};
void Bucket::RecursiveFill(int x, int y, graphics::Color start,
                           graphics::Color fill, graphics::Image& image) {
  if (x < 0 || y < 0 || x >= image.GetWidth() || y >= image.GetHeight()) {
    return;
  } else if (image.GetColor(x, y) != start) {
    return;
  } else if (image.GetColor(x, y) == fill) {
    return;
  } else {
    image.SetColor(x, y, fill);
    RecursiveFill(x, y + 1, start, fill, image);
    RecursiveFill(x, y - 1, start, fill, image);
    RecursiveFill(x + 1, y, start, fill, image);
    RecursiveFill(x - 1, y, start, fill, image);
  }
};
void Bucket::IterativeFill(int x, int y, graphics::Color start,
                           graphics::Color fill, graphics::Image& image) {
  std::queue<Point> points_to_check;
  Point origin;
  origin.SetX(x);
  origin.SetY(y);
  points_to_check.push(origin);
  while (points_to_check.size() > 0) {
    Point current = points_to_check.front();
    if (image.GetColor(current.GetX(), current.GetY()) == fill) {
      points_to_check.pop();
      continue;
    }
    if (image.GetColor(current.GetX(), current.GetY()) == start) {
      image.SetColor(current.GetX(), current.GetY(), fill);
      Point top;
      top.SetX(current.GetX());
      top.SetY(current.GetY() - 1);
      Point bottom;
      bottom.SetX(current.GetX());
      bottom.SetY(current.GetY() + 1);
      Point left;
      left.SetX(current.GetX() - 1);
      left.SetY(current.GetY());
      Point right;
      right.SetX(current.GetX() + 1);
      right.SetY(current.GetY());
      if (top.GetX() >= 0 && top.GetY() >= 0 && top.GetX() < image.GetWidth() &&
          top.GetY() < image.GetHeight()) {
        points_to_check.push(top);
      }
      if (bottom.GetX() >= 0 && bottom.GetY() >= 0 &&
          bottom.GetX() < image.GetWidth() &&
          bottom.GetY() < image.GetHeight()) {
        points_to_check.push(bottom);
      }
      if (left.GetX() >= 0 && left.GetY() >= 0 &&
          left.GetX() < image.GetWidth() && left.GetY() < image.GetHeight()) {
        points_to_check.push(left);
      }
      if (right.GetX() >= 0 && right.GetY() >= 0 &&
          right.GetX() < image.GetWidth() && right.GetY() < image.GetHeight()) {
        points_to_check.push(right);
      }
    }
    points_to_check.pop();
  }
};

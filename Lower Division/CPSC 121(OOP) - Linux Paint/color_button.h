#include "button.h"

#ifndef COLOR_BUTTON_H
#define COLOR_BUTTON_H

class ColorButton : public Button {
 public:
  ColorButton(int x, int y, int width, int height, ButtonListener* listener_ptr,
              graphics::Color color)
      : Button(x, y, width, height, listener_ptr) {
    color_ = color;
  }
  graphics::Color GetColor();
  void Draw(graphics::Image&) override;
  void DoAction() override;

 private:
  graphics::Color color_;
};

#endif  // COLOR_BUTTON_H

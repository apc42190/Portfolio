#include "color_button.h"

// TODO: Implement your ColorButton class methods here.
graphics::Color ColorButton::GetColor() { return color_; }
void ColorButton::Draw(graphics::Image& image) {
  Button::Draw(image);
  image.DrawRectangle(GetX() + 1, GetY() + 1, GetWidth() - 2, GetHeight() - 2,
                      color_);
}
void ColorButton::DoAction() {
  ButtonListener* button_listener = GetButtonListener();
  button_listener->SetActiveColor(color_, this);
}

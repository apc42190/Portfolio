#include "button.h"

int Button::GetX() const { return x_; }

int Button::GetY() const { return y_; }

int Button::GetWidth() const { return width_; }

int Button::GetHeight() const { return height_; }

void Button::Draw(graphics::Image& image) {
  image.DrawRectangle(x_, y_, width_, height_, 30, 30, 30);
}

bool Button::DidHandleEvent(const graphics::MouseEvent& event) {
  if (event.GetX() >= x_ && event.GetX() < x_ + width_ && event.GetY() >= y_ &&
      event.GetY() < y_ + height_ &&
      event.GetMouseAction() == graphics::MouseAction::kPressed) {
    last_action_ = event.GetMouseAction();
    return true;
  } else if (event.GetX() >= x_ && event.GetX() < x_ + width_ &&
             event.GetY() >= y_ && event.GetY() < y_ + height_ &&
             event.GetMouseAction() == graphics::MouseAction::kReleased &&
             last_action_ == graphics::MouseAction::kPressed) {
    DoAction();
    last_action_ = graphics::MouseAction::kReleased;
    return true;
  } else if (event.GetMouseAction() == graphics::MouseAction::kDragged &&
             last_action_ == graphics::MouseAction::kPressed) {
    return true;
  } else {
    last_action_ = graphics::MouseAction::kReleased;
    return false;
  }
}

ButtonListener* Button::GetButtonListener() { return listener_ptr_; }
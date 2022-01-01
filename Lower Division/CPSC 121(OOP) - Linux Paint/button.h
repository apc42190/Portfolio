#include "button_listener.h"

#ifndef BUTTON_H
#define BUTTON_H

class Button {
 public:
  Button(int x, int y, int width, int height, ButtonListener* listener_ptr)
      : x_(x),
        y_(y),
        width_(width),
        height_(height),
        listener_ptr_(listener_ptr) {}
  virtual ~Button() = default;
  int GetX() const;
  int GetY() const;
  int GetWidth() const;
  int GetHeight() const;
  virtual void DoAction() = 0;
  virtual void Draw(graphics::Image&);
  bool DidHandleEvent(const graphics::MouseEvent&);

 protected:
  ButtonListener* GetButtonListener();

 private:
  int x_;
  int y_;
  int width_;
  int height_;
  ButtonListener* listener_ptr_;
  graphics::MouseAction last_action_;
};

#endif  // BUTTON_H

#include "tool_button.h"

// TODO: Implement your ToolButton class methods here.
ToolType ToolButton::GetToolType() const { return type_; }
void ToolButton::Draw(graphics::Image& image) {
  Button::Draw(image);
  if (type_ == kBrush) {
    image.DrawText(GetX(), GetY(), "Brush", 16, graphics::Color(255, 255, 255));
  } else if (type_ == kPencil) {
    image.DrawText(GetX(), GetY(), "Pencil", 16,
                   graphics::Color(255, 255, 255));
  } else if (type_ == kBucket) {
    image.DrawText(GetX(), GetY(), "Bucket", 16,
                   graphics::Color(255, 255, 255));
  } else if (type_ == kEraser) {
    image.DrawText(GetX(), GetY(), "Eraser", 16,
                   graphics::Color(255, 255, 255));
  }
}
void ToolButton::DoAction() {
  ButtonListener* listener_ptr = GetButtonListener();
  listener_ptr->SetActiveTool(type_, this);
}

#include "button.h"
#include "tool_type.h"

#ifndef TOOL_BUTTON_H
#define TOOL_BUTTON_H

class ToolButton : public Button {
 public:
  ToolButton(int x, int y, int width, int height, ButtonListener* listener_ptr,
             ToolType type)
      : Button(x, y, width, height, listener_ptr) {
    type_ = type;
  }
  ToolType GetToolType() const;
  void Draw(graphics::Image&) override;
  void DoAction() override;

 private:
  ToolType type_;
};

#endif  // TOOL_BUTTON_H

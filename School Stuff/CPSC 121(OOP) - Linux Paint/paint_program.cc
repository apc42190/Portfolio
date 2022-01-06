#include "paint_program.h"
#include <iostream>
#include "color_button.h"
#include "tool_button.h"
void PaintProgram::Initialize() {
  brush_.SetWidth(20);
  eraser_.SetWidth(20);
  image_.AddMouseEventListener(*this);
  buttons_.push_back(
      std::make_unique<ToolButton>(10, 10, 50, 20, this, ToolType::kBrush));
  buttons_.push_back(
      std::make_unique<ToolButton>(10, 40, 50, 20, this, ToolType::kPencil));
  buttons_.push_back(
      std::make_unique<ToolButton>(10, 70, 50, 20, this, ToolType::kBucket));
  buttons_.push_back(std::make_unique<ColorButton>(10, 100, 50, 20, this,
                                                   graphics::Color(255, 0, 0)));
  buttons_.push_back(std::make_unique<ColorButton>(10, 130, 50, 20, this,
                                                   graphics::Color(0, 0, 255)));
  buttons_.push_back(std::make_unique<ColorButton>(10, 160, 50, 20, this,
                                                   graphics::Color(0, 128, 0)));
  buttons_.push_back(std::make_unique<ColorButton>(10, 190, 50, 20, this,
                                                   graphics::Color(255, 255, 0)));
  buttons_.push_back(std::make_unique<ColorButton>(10, 220, 50, 20, this,
                                                   graphics::Color(128, 0, 128)));
  buttons_.push_back(std::make_unique<ColorButton>(10, 250, 50, 20, this,
                                                   graphics::Color(0, 0, 0)));
  buttons_.push_back(
      std::make_unique<ToolButton>(10, 280, 50, 20, this, ToolType::kEraser));
  SetActiveTool(ToolType::kPencil, buttons_.at(1).get());
  SetActiveColor(graphics::Color(0, 0, 0), buttons_.at(8).get());
  for (int i = 0; i < buttons_.size(); i++) {
    buttons_.at(i)->Draw(image_);
  }
}

void PaintProgram::Start() { image_.ShowUntilClosed("MFPaint"); }

void PaintProgram::SetActiveTool(ToolType tool, Button* tool_button) {
  tool_ = tool;
}

void PaintProgram::SetActiveColor(const graphics::Color& color,
                                  Button* color_button) {
  brush_.SetColor(color);
  bucket_.SetColor(color);
  pencil_.SetColor(color);
}

void PaintProgram::OnMouseEvent(const graphics::MouseEvent& event) {
  std::cout << "Mouse event at " << event.GetX() << ", " << event.GetY()
            << std::endl;
  bool draw = true;
  for (int i = 0; i < buttons_.size(); i++) {
    if (buttons_.at(i)->DidHandleEvent(event)) {
      draw = false;
      break;
    }
  }
  if (draw) {
    if (tool_ == kBucket &&
        event.GetMouseAction() == graphics::MouseAction::kPressed) {
      bucket_.Fill(event.GetX(), event.GetY(), image_);
    } else if (tool_ == kBrush &&
               event.GetMouseAction() == graphics::MouseAction::kPressed) {
      brush_.Start(event.GetX(), event.GetY(), image_);
    } else if (tool_ == kPencil &&
               event.GetMouseAction() == graphics::MouseAction::kPressed) {
      pencil_.Start(event.GetX(), event.GetY(), image_);
    } else if (tool_ == kEraser &&
               event.GetMouseAction() == graphics::MouseAction::kPressed) {
      eraser_.Start(event.GetX(), event.GetY(), image_);
    }
    if (tool_ == kBrush &&
        event.GetMouseAction() == graphics::MouseAction::kDragged) {
      brush_.MoveTo(event.GetX(), event.GetY(), image_);
    } else if (tool_ == kPencil &&
               event.GetMouseAction() == graphics::MouseAction::kDragged) {
      pencil_.MoveTo(event.GetX(), event.GetY(), image_);
    } else if (tool_ == kEraser &&
               event.GetMouseAction() == graphics::MouseAction::kDragged) {
      eraser_.MoveTo(event.GetX(), event.GetY(), image_);
    }
  }
  for (int i = 0; i < buttons_.size(); i++) {
    buttons_.at(i)->Draw(image_);
  }
  image_.Flush();
}

void PaintProgram::SaveAfterClosing(std::string name) {
  image_.SaveImageBmp(name);
}
#include <string>
#include <vector>
#include "brush.h"
#include "bucket.h"
#include "button.h"
#include "button_listener.h"
#include "cpputils/graphics/image.h"
#include "eraser.h"
#include "pencil.h"
#include "tool_type.h"

#ifndef PAINT_PROGRAM_H
#define PAINT_PROGRAM_H

class PaintProgram : public graphics::MouseEventListener,
                     public ButtonListener {
 public:

  PaintProgram() : PaintProgram(500, 500) {}
  PaintProgram(int height, int width) { image_.Initialize(height, width); }
  ~PaintProgram() { image_.RemoveMouseEventListener(*this); }
  // Used by unit tests. Do not modify.
  graphics::Image* GetImageForTesting() { return &image_; }
  void Initialize();
  void Start();
  void SetActiveTool(ToolType, Button*) override;
  void SetActiveColor(const graphics::Color&, Button*) override;
  void OnMouseEvent(const graphics::MouseEvent&) override;
  void SaveAfterClosing(std::string);
  std::vector<std::unique_ptr<Button>>* GetButtonsForTesting() {
    return &buttons_;
  }

 private:
  // The image_ which will be the canvas for the PaintProgram.
  graphics::Image image_;
  Brush brush_;
  Pencil pencil_;
  Bucket bucket_;
  ToolType tool_;
  Eraser eraser_;
  std::vector<std::unique_ptr<Button>> buttons_;
};

#endif  // PAINT_PROGRAM_H

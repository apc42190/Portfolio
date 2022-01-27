#include "../include/paddle.h"

    void Paddle::drawPaddle() {
        DrawRectangleRec(paddle_, WHITE);
    }

    Rectangle Paddle::getPaddle() {
        return paddle_;
    }

    void Paddle::movePaddle(KeyboardKey key) {
        if (key == KeyboardKey::KEY_UP) {
            paddle_.y -= 15;
        } else if (key == KeyboardKey::KEY_DOWN) {
            paddle_.y += 15;
        }  else if (key == KeyboardKey::KEY_S) {
            paddle_.y += 15;
        } else if (key == KeyboardKey::KEY_W) {
            paddle_.y -= 15;
        }
    }

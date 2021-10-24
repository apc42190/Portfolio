#ifndef PADDLE_H
#define PADDLE_H

#include "raylib.h"
#include "ball.h"

class Paddle {
    public:
    Paddle(int player, int window_width, int window_height) {
        int paddle_width = window_width / 100;
        int paddle_height = window_height / 10;
        int paddle_start_x = 0;
        int paddle_start_y = (window_height / 2) - (paddle_height / 2);
        if (player == 1) {
            paddle_ = {float(paddle_start_x), float(paddle_start_y), float(paddle_width), float(paddle_height)};
        } else {
            paddle_ = {float(paddle_start_x + window_width - paddle_width), float(paddle_start_y), float(paddle_width), float(paddle_height)}; 
        }
        
        player_ = player;

    }
    void drawPaddle();
    Rectangle getPaddle();
    void movePaddle(KeyboardKey);
    
    public:
    int player_;
    Rectangle paddle_;
};

#endif
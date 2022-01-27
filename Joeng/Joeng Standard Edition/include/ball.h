#ifndef BALL_H
#define BALL_H

#include "raylib.h"
#include "paddle.h"
#include <cmath>

class Ball {
    public:
    Ball(int window_width, int window_height) {
        position_.x = window_width / 2;
        position_.y = window_height / 2;
        speed_mod_.x = float(GetRandomValue(-1000, 1000)) / 1000;
        speed_mod_.y = float(GetRandomValue(-1000, 1000)) / 1000;
    }

    void drawBall();
    Vector2 getPosition();
    Vector2 getSpeed();
    void setSpeed(Vector2);
    float getRadius();
    void moveBall(int);
    int checkCollision(Rectangle, Rectangle, int, int, Sound&, Sound&);

    private:
    float radius_ = 5.0;
    Vector2 position_;
    Vector2 speed_mod_;
};

#endif
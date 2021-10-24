#include "../include/ball.h"

    void Ball::drawBall() {
        DrawCircle(position_.x, position_.y, float(radius_), WHITE);
    }

    Vector2 Ball::getPosition() {
        return position_;
    }

    Vector2 Ball::getSpeed() {
        return speed_mod_;
    }

    float Ball::getRadius() {
        return radius_;
    }

    void Ball::setSpeed(Vector2 new_speeds) {
        speed_mod_ = new_speeds; 
    }


    void Ball::moveBall(int ball_speed) {
        position_.x += speed_mod_.x * ball_speed;
        position_.y += speed_mod_.y * ball_speed;
    }

    int Ball::checkCollision(Rectangle paddle_1, Rectangle paddle_2, int window_width, int window_height, Sound& collision, Sound& death) {
        if (position_.y + radius_ >= window_height) {
            speed_mod_.y = -speed_mod_.y;
            speed_mod_.x += (float(GetRandomValue(-1000, 1000)) / 1000);
            PlaySound(collision);
        } else if (position_.y - radius_ <= 0) {
            speed_mod_.y = -speed_mod_.y;
            speed_mod_.x += (float(GetRandomValue(-1000, 1000)) / 1000);
            PlaySound(collision);
        } else if (position_.x - radius_ <= paddle_1.x + paddle_1.width - 10) {
            speed_mod_.x *= 1.2;
            if (position_.y + radius_ < paddle_1.y || position_.y - radius_ > paddle_1.y + paddle_1.height) {
                PlaySound(death);
                return 2;
            } else if (position_.y > paddle_1.y && position_.y < paddle_1.y + window_height) {
                speed_mod_.x = -speed_mod_.x;
                PlaySound(collision);
                int new_ball = GetRandomValue(2, 2);
                if (new_ball == 2) {
                    return 100;
                }
            } else {
                speed_mod_.x = -speed_mod_.x;
                speed_mod_.y = -speed_mod_.y;
                PlaySound(collision);
            }
        } else if (position_.x + radius_ >= paddle_2.x + 10) {
            speed_mod_.x *= 1.2;
            if (position_.y + radius_ < paddle_2.y || position_.y - radius_ > paddle_2.y + paddle_2.height) {
                PlaySound(death);
                return 1;
            } else if (position_.y > paddle_2.y && position_.y < paddle_2.y + window_height) {
                speed_mod_.x = -speed_mod_.x;
                PlaySound(collision);
                int new_ball = GetRandomValue(1, 3);
                if (new_ball == 2) {
                    return 100;
                }
            } else {
                speed_mod_.x = -speed_mod_.x;
                speed_mod_.y = -speed_mod_.y;
                PlaySound(collision);
            }
        }
        return 0;
    }

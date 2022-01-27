#include "../include/raylib.h"
#include "../include/paddle.h"
#include "../include/ball.h"
#include <string>
#include <vector>
#include <cstring>
#include <chrono>
#include <thread>


int main () {

    const int window_width = 1600;
    const int window_height = 900;
    int ball_speed = 8;
    int p1_wins = 0;
    int p2_wins = 0;

    InitWindow(window_width, window_height, "Joeng");
    SetTargetFPS(60);

    InitAudioDevice();
    Sound joe_sound = LoadSound("../sounds/Joe_Sound.wav");
    Sound death = LoadSound("../sounds/death.wav");

    std::vector<Ball> balls;
    Ball ball_1(window_width, window_height);
    balls.push_back(ball_1);
    Paddle player_1(1, window_width, window_height);
    Paddle player_2(2, window_width, window_height);

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(BLACK);

        DrawText(std::to_string(p1_wins).c_str(), window_width / 4, 15, 50, WHITE);
        DrawText(std::to_string(p2_wins).c_str(), 3 * (window_width / 4), 15, 50, WHITE);

        
        player_1.drawPaddle();
        player_2.drawPaddle();

        for (size_t i = 0; i < balls.size(); ++i) {
            balls[i].moveBall(ball_speed);
            balls[i].drawBall();
            int newbie = balls[i].checkCollision(player_1.getPaddle(), player_2.getPaddle(), window_width, window_height, joe_sound, death);
            if (newbie == 100) {
                balls.push_back(Ball(window_width, window_height, balls[i].getPosition(), balls[i].getSpeed()));
            } else if (newbie == 1 || newbie == 2) {
                balls.erase(balls.begin() + i);
                i--;
                if (newbie == 1) {
                    p1_wins++;
                } else if (newbie == 2) {
                    p2_wins++;
                }
            }
        }

        if (IsKeyPressed(KeyboardKey::KEY_R)) {
                    balls.clear();
                    balls.push_back(Ball(window_width, window_height));
                    player_1 = Paddle(1, window_width, window_height);
                    player_2 = Paddle(2, window_width, window_height);
        }


        if (player_2.getPaddle().y >= 0 && IsKeyDown(KeyboardKey::KEY_UP)) {
            player_2.movePaddle(KeyboardKey::KEY_UP);
        } else if (player_2.getPaddle().y + player_2.getPaddle().height <= window_height && IsKeyDown(KeyboardKey::KEY_DOWN)) {
            player_2.movePaddle(KeyboardKey::KEY_DOWN);
        }


        if (IsKeyDown(KeyboardKey::KEY_W)) {
            player_1.movePaddle(KeyboardKey::KEY_W);
        } else if (IsKeyDown(KeyboardKey::KEY_S)) {
            player_1.movePaddle(KeyboardKey::KEY_S);
        }

        if (balls.empty()) {
            std::string new_game = "Press space to start new game.";
            if (p1_wins > p2_wins) {
                std::string win_text = "Player 1 Wins";
                DrawText(win_text.c_str(), window_width / 10 - 30, window_height / 3, 200, WHITE);
                DrawText(new_game.c_str(), window_width / 10 + 200, window_height / 3 + 250, 50, WHITE);
            } else if (p2_wins > p1_wins) {
                std::string win_text = "Player 2 Wins";
                DrawText(win_text.c_str(), window_width / 10 - 30, window_height / 3, 200, WHITE);
                DrawText(new_game.c_str(), window_width / 10 + 200, window_height / 3 + 250, 50, WHITE);
            } else {
                std::string win_text = "Winner to be decided by \n           combat.";
                DrawText(win_text.c_str(), window_width / 10 + 10, window_height / 3, 100, WHITE);
                new_game = "\nPress space to start new game.";
                DrawText(new_game.c_str(), window_width / 10 + 200, window_height / 3 + 250, 50, WHITE);
            }

            if (IsKeyPressed(KeyboardKey::KEY_SPACE)) {
                p1_wins = 0;
                p2_wins = 0;
                player_1 = Paddle(1, window_width, window_height);
                player_2 = Paddle(2, window_width, window_height);
                balls.push_back(Ball(window_width, window_height));
            }
        }

        EndDrawing();
    }

    UnloadSound(death);
    UnloadSound(joe_sound);

    CloseAudioDevice();
    

    CloseWindow();

    return 0;
}
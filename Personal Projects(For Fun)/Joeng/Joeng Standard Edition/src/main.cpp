#include "../include/raylib.h"
#include "../include/paddle.h"
#include "../include/ball.h"
#include <string>
#include <cstring>
#include <chrono>
#include <thread>


int main () {

    const int window_width = 1600;
    const int window_height = 900;
    int ball_speed = 8;
    int winner = 0;
    int p1_wins = 0;
    int p2_wins = 0;

    InitWindow(window_width, window_height, "Joeng");
    SetTargetFPS(60);

    InitAudioDevice();
    Sound joe_sound = LoadSound("../sounds/Joe_Sound.wav");
    Sound death = LoadSound("../sounds/death.wav");

    Ball ball(window_width, window_height);
    Paddle player_1(1, window_width, window_height);
    Paddle player_2(2, window_width, window_height);

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(BLACK);

        DrawText(std::to_string(p1_wins).c_str(), window_width / 4, 15, 50, WHITE);
        DrawText(std::to_string(p2_wins).c_str(), 3 * (window_width / 4), 15, 50, WHITE);

        
        player_1.drawPaddle();
        player_2.drawPaddle();

        ball.drawBall();

        if (IsKeyPressed(KeyboardKey::KEY_R)) {
                    ball = Ball(window_width, window_height);
                    player_1 = Paddle(1, window_width, window_height);
                    player_2 = Paddle(2, window_width, window_height);
                }

        ball.moveBall(ball_speed);
        winner = ball.checkCollision(player_1.getPaddle(), player_2.getPaddle(), window_width, window_height, joe_sound, death);

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


        EndDrawing();

        if (winner != 0) {
            if (winner == 1) {
                p1_wins++;
            } else if (winner == 2) {
                p2_wins++;
            }
            while(!WindowShouldClose()) {
                
                ClearBackground(BLACK);
                std::string win_text = "Player " + std::to_string(winner) + " Wins";
                DrawText(win_text.c_str(), window_width / 10, window_height / 3, 200, WHITE);
                EndDrawing();
                std::this_thread::sleep_for(std::chrono::milliseconds(1000));
                ball = Ball(window_width, window_height);

                if (IsKeyPressed(KeyboardKey::KEY_R)) {
                    player_1 = Paddle(1, window_width, window_height);
                    player_2 = Paddle(2, window_width, window_height);
                    winner = 0;
                    break;
                }
                break;
            }
        }
    }

    UnloadSound(death);
    UnloadSound(joe_sound);

    CloseAudioDevice();
    

    CloseWindow();

    return 0;
}
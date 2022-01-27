#include "raylib.h"
#include <ctime>
#include <cmath>

int main() {

    const int screen_width = 800;
    const int screen_height = 800;
    const int clock_center = 400;
    Vector2 center{clock_center, clock_center};
    int font_size = 80;

    InitWindow(screen_width, screen_height, "Clock 2: Clockman's Revenge");
    SetTargetFPS(60);

    while(!WindowShouldClose()) {
        std::time_t t = std::time(0);
        std::tm* now = std::localtime(&t);

        float x_hour_hand = -cos((3 + now->tm_hour) * (M_PI / 6));
        float y_hour_hand = -sin((3 + now->tm_hour) * (M_PI / 6));
        float x_min_hand = -cos((15 + now->tm_min) * (M_PI / 30));
        float y_min_hand = -sin((15 + now->tm_min) * (M_PI / 30));
        float x_second_hand = -cos((15 + now->tm_sec) * (M_PI / 30));
        float y_second_hand = -sin((15 + now->tm_sec) * (M_PI / 30));


        BeginDrawing();

        ClearBackground(BLACK);
        

        //Draw clock outer circle
        DrawCircle(clock_center, clock_center, 399, BLUE);
        DrawCircle(clock_center, clock_center, 397, BLACK);

        DrawText("12", 370, 15, font_size, BLUE);
        //DrawText("1", 600, 69, font_size, BLUE);
        //DrawText("2", 746, 215, font_size, BLUE);
        DrawText("3", 740, 360, font_size, BLUE);
        DrawText("6", 375, 720, font_size, BLUE);
        DrawText("9", 15, 365, font_size, BLUE);
        

        //Draw clock hour hand
        x_hour_hand *= 195;
        y_hour_hand *= 195;
        x_hour_hand += clock_center;
        y_hour_hand += clock_center;
        Vector2 hour_hand{x_hour_hand, y_hour_hand};
        DrawLineEx(center, hour_hand, 5, GREEN);

        //Draw minute hand
        x_min_hand *= 395;
        y_min_hand *= 395;
        x_min_hand += clock_center;
        y_min_hand += clock_center;
        Vector2 min_hand{x_min_hand, y_min_hand};
        DrawLineEx(center, min_hand, 5, ORANGE);

        //Draw second hand
        x_second_hand *= 395;
        y_second_hand *= 395;
        x_second_hand += clock_center;
        y_second_hand += clock_center;
        DrawLine(clock_center, clock_center, int(x_second_hand), int(y_second_hand), PINK);


        
        EndDrawing();
    }

    CloseWindow();

    return 0;
}
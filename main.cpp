#include "raylib.h"
int main()
{
    const int screenwidth = 800;
    const int screenHeight = 600;
    InitWindow(screenwidth, screenHeight, "Ping Pong Game");
    SetTargetFPS(60);


    int ball_x = 400;
    int ball_y = 300;
    int ball_radius = 14;
    float ball_speed_x = 5.0f;
    float ball_speed_y = 5.0f;

    // Paddle Variables
    int paddle_x = 30;
    int paddle_y = 30;
    int paddle_height = 75;
    int paddle_width = 10;
    float paddle_speed = 6.0f;

    // AI Variables
    int ai_x = 760;
    int ai_y = 495;
    int ai_height = 75;
    int ai_width = 10;
    float ai_speed = 6.0f;

    // score
    int player_score = 0;
    int ai_score = 0;
    while (!WindowShouldClose())
    {
        // ball
        ball_x += ball_speed_x;
        ball_y += ball_speed_y;

        // Logic part
        if (ball_x - ball_radius <= 0)
        {
            ball_speed_x = -ball_speed_x;
            ai_score++;
            ball_x = screenwidth / 2;
            ball_y = screenHeight / 2;
        }
        if (ball_x + ball_radius >= screenwidth)
        {
            ball_speed_x = -ball_speed_x;
            player_score++;
            ball_x = screenwidth / 2;
            ball_y = screenHeight / 2;
        }
        if (ball_y - ball_radius <= 0)
        {
            ball_speed_y = -ball_speed_y;
        }
        if (ball_y + ball_radius >= screenHeight)
        {
            ball_speed_y = -ball_speed_y;
        }
        // paddle

        if (IsKeyDown(KEY_W))
        {
            paddle_y -= paddle_speed;
        }
        if (IsKeyDown(KEY_S))
        {
            paddle_y += paddle_speed;
        }
        if (paddle_y < 0)
        {
            paddle_y = 0;
        }
        if (paddle_y + paddle_height > screenHeight)
        {
            paddle_y = screenHeight - paddle_height;
        }

        // Collision
        if (CheckCollisionCircleRec(Vector2{(float)ball_x, (float)ball_y}, ball_radius,
                                    Rectangle{(float)paddle_x, (float)paddle_y, (float)paddle_width, (float)paddle_height}) &&
            ball_speed_x < 0)
        {
            ball_speed_x = -ball_speed_x;
        }

        // AI
        if (ball_y > ai_y + (ai_height / 2))
        {
            ai_y += ai_speed;
        }
        if (ball_y < ai_y + (ai_height / 2))
        {
            ai_y -= ai_speed;
        }

        if (CheckCollisionCircleRec(Vector2{(float)ball_x, (float)ball_y}, ball_radius,
                                    Rectangle{(float)ai_x, (float)ai_y, (float)ai_width, (float)ai_height}) &&
            ball_speed_x > 0)
        {
            ball_speed_x = -ball_speed_x;
        }

      
        BeginDrawing();
        ClearBackground(BLUE);
        DrawCircle(ball_x, ball_y, ball_radius, YELLOW);
        DrawRectangle(paddle_x, paddle_y, paddle_width, paddle_height, WHITE);
        DrawRectangle(ai_x, ai_y, ai_width, ai_height, WHITE);

        // Player score(Left Side)
        DrawText(TextFormat("%d", player_score), screenwidth / 4, 20, 40, WHITE);

        // AI score(Right Side)
        DrawText(TextFormat("%d", ai_score), 3 * screenwidth / 4, 20, 40, WHITE);

        // Divider Line
        DrawLine(screenwidth / 2, 0, screenwidth / 2, screenHeight, WHITE);
        EndDrawing();
    }
    CloseWindow();
    return 0;
}